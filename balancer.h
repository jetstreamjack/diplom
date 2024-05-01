#pragma once

#include "i_balancer.h"
#include "i_gpu_controller.h"
#include "gpu_controller.h"

#include <vector>
//#include <cstdin.h>
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

        Task( const Task& ); // non construction-copyable
        Task& operator=( const Task& ); // non copyable

        Task( const Task&& ) = delete; // non construction-copyable
        Task& operator=( const Task&& ) = delete; // non copyable

        double* m_cudaMem;
        double* m_resutlMem;
        size_t m_vecSize;
    };
class Balancer : public IBalancer
{
public:
    explicit Balancer(std::unique_ptr<controller::IGpuController> gpuController);

    // add commentary
    TaskId AddTask(int numFunc, PathVec path) override;
    double GetTaskResult(TaskId taskId) override;
private:
    TaskId GenerateTaskId();
    //__global__ void ProcessTask(int numFunc, double * path, double* res, controller::IGpuController* gpuController);


private:
    std::unique_ptr<controller::IGpuController> m_gpuController;
    controller::GpuController* gpuController;
    std::map<TaskId, Task> m_taskMap;
    std::vector<Task> m_vec;
    //todo(odnorob): add map of stream and double buf
    cudaStream_t stream0;
    //Task m_tsk;
    double* m_cudaMem;
    double* m_resutlMem;
};

} // balancer
