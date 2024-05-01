#pragma once

#include <vector>
//#include <cstdin.h>
#include <string>

namespace balancer {

using PathVec = std::vector<double>;
using TaskId = unsigned int;

class IBalancer
{
public:
    virtual ~IBalancer() = default;

    // add commentary
    virtual TaskId AddTask(int numFunc, PathVec path) = 0;

    virtual double GetTaskResult(TaskId taskId) = 0;

};

} // balancer
