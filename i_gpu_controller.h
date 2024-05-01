#pragma once

#include <vector>
//#include <cstdin.h>

namespace controller {

//using ClasterFunc = std::function<double(PathVec)>;
//using ClasterFuncIntent = std::pair<int64_t, ClasterFunc>;

class IGpuController
{
public:
    virtual ~IGpuController() = default;
    
    // /**
    //  * @brief Register function
    //  * @details Need to register function, which should be counted on the GPU
    //  * @param clasterFunc - pair of number of function and function
    //  * @return result code(change on enum) 
    //  */
    // int64_t RegisterFunction(ClasterFuncIntent clasterFunc);

    /**
     * @brief Invoker Claster function
     * @details invoke ONLY register funtion
     * @param funcNumber - number of func
     * @return double - result of function
     */
    __host__ __device__ virtual void InvokeClasterFunction(int funcNumber, double* pathVec, double* res) = 0;

};

} // controller
