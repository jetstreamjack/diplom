#pragma once

#include "i_balancer.h"
#include "gpu_controller.h"
#include "gpu_controller.h"

#include <vector>
#include <string>
#include <memory>
#include <map>

namespace balancer {

    struct Task
    {
    public:
        explicit Task(PathVec path);
        ~Task();
        double GetResult();

        Task( const Task& );
        Task& operator=( const Task& );

        Task( const Task&& ) = delete;
        Task& operator=( const Task&& ) = delete;

        double* m_cudaMem;
        double* m_resutlMem;
        size_t m_vecSize;
    };
class Balancer : public IBalancer
{
public:
    explicit Balancer(std::unique_ptr<controller::GpuController> gpuController);

    TaskId AddTask(int numFunc, PathVec path) override;
    double GetTaskResult(TaskId taskId) override;
private:
    TaskId GenerateTaskId();

private:
    std::unique_ptr<controller::GpuController> m_gpuController;
    controller::GpuController* c_gpuController;
    std::map<TaskId, Task> m_taskMap;
    std::vector<Task> m_vec;
    //todo(odnorob): add map of stream and double buf
    cudaStream_t stream0;
    double* m_cudaMem;
    double* m_resutlMem;
};

} // balancer
