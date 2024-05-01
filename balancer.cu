
#include "balancer.h"
#include "gpu_controller.h"
#include "i_balancer.h"
#include "i_gpu_controller.h"

#include <vector>
// #include <cstdin.h>
#include <exception>
#include <string>

#include <algorithm>
#include <chrono>
#include <iterator>
#include <random>
#include <unordered_map>

namespace balancer {

__global__ void ProcessTask(int numFunc, double *path, double *res,
                            controller::GpuController *gpuController) {
  path = path;
  res = res;
  numFunc = numFunc;
  // gpuController->InvokeClasterFunction(numFunc, path, res);
  gpuController->Dude(numFunc, path, res);

  //*res = resW;
}

Balancer::Balancer(std::unique_ptr<controller::IGpuController> gpuController)
    : m_gpuController(std::move(gpuController)) {
  // if(!m_gpuController)
  // {
  //     throw std::exception("GpuController is null!");
  // }
  // HANDLE_ERROR(cudaStreamCreate(&stream0));
}

// add commentary
TaskId Balancer::AddTask(int numFunc, PathVec path) {
  TaskId taskId = GenerateTaskId();

  m_taskMap.insert(std::pair<TaskId, Task>(taskId, Task(path)));

  auto error = cudaGetLastError();
  if (error != cudaSuccess) {
    printf("113 %s\n", cudaGetErrorString(error));
    exit(1);
  }

  // todo(odnorob): in ctor
  cudaMalloc((void **)&gpuController, sizeof(controller::GpuController));
  controller::GpuController *gpu = new controller::GpuController();
  cudaMemcpy(gpuController, gpu, sizeof(controller::GpuController),
             cudaMemcpyHostToDevice);

  cudaDeviceSynchronize();

  error = cudaGetLastError();
  if (error != cudaSuccess) {
    printf("16 %s\n", cudaGetErrorString(error));
    exit(1);
  }

  ProcessTask<<<1, 1>>>(numFunc, m_taskMap.find(taskId)->second.m_cudaMem,
                        m_taskMap.find(taskId)->second.m_resutlMem,
                        gpuController);

  return taskId;
}
double Balancer::GetTaskResult(TaskId taskId) {
  cudaDeviceSynchronize();
  auto res = m_taskMap.find(taskId)->second.GetResult();
  m_taskMap.erase(taskId);
  return res;
}

TaskId Balancer::GenerateTaskId() {
  std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> distr(0, 1000000);
  // TODO(odnorob): add check on unique
  return distr(gen);
}

Task::Task(const Task &task) {
  this->m_vecSize = task.m_vecSize;
  cudaMalloc(&m_cudaMem, m_vecSize * sizeof(double));
  cudaMemcpy(m_cudaMem, task.m_cudaMem, m_vecSize * sizeof(double),
             cudaMemcpyDeviceToDevice);
  cudaMalloc(&m_resutlMem, sizeof(double));
  cudaDeviceSynchronize();

  auto error = cudaGetLastError();
  if (error != cudaSuccess) {
    printf("1123 %s\n", cudaGetErrorString(error));
    exit(1);
  }
}

Task &Task::operator=(const Task &task) {
  m_vecSize = task.m_vecSize;
  cudaMalloc(&m_cudaMem, m_vecSize * sizeof(double));
  cudaMemcpy(m_cudaMem, task.m_cudaMem, m_vecSize * sizeof(double),
             cudaMemcpyDeviceToDevice);
  cudaMalloc(&m_resutlMem, sizeof(double));
  cudaDeviceSynchronize();

  auto error = cudaGetLastError();
  if (error != cudaSuccess) {
    printf("1123 %s\n", cudaGetErrorString(error));
    exit(1);
  }
}

Task::Task(PathVec path) : m_vecSize(path.size()) {
  cudaMalloc(&m_cudaMem, path.size() * sizeof(double));
  cudaMemcpy(m_cudaMem, path.data(), path.size() * sizeof(double),
             cudaMemcpyHostToDevice);
  cudaMalloc(&m_resutlMem, sizeof(double));
  cudaDeviceSynchronize();

  auto error = cudaGetLastError();
  if (error != cudaSuccess) {
    printf("17 %s\n", cudaGetErrorString(error));
    exit(1);
  }
}

Task::~Task() {
  cudaDeviceSynchronize();
  cudaFree(m_cudaMem);
  cudaFree(m_resutlMem);
  cudaDeviceSynchronize();
}

double Task::GetResult() {
  cudaDeviceSynchronize();
  auto error = cudaGetLastError();
  if (error != cudaSuccess) {
    printf("2 %s\n", cudaGetErrorString(error));
    exit(1);
  }
  double *result = (double *)malloc(sizeof(double));
  cudaMemcpy(result, m_resutlMem, sizeof(double), cudaMemcpyDeviceToHost);
  cudaDeviceSynchronize();
  double res = *result;
  printf("res2:%f", *result);
  free(result);
  return res;
}

} // namespace balancer
