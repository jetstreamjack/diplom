#pragma once

#include <string>
#include <vector>

namespace balancer {

using PathVec = std::vector<double>;
using TaskId = unsigned int;

/**
 * @brief balancer for GPU calculated function
 * @details it is necessary to provide an api for interacting
 * with functions that will be calculated in the GPU
 */
class IBalancer {
public:
  virtual ~IBalancer() = default;

  /**
   * @brief add a task to calculate a function on the GPU
   *
   * @param numFunc - number of function
   * @param path - data for calculated function
   * @return TaskId - the ID that can be used to request the results of
   * calculations
   */
  virtual TaskId AddTask(int numFunc, PathVec path) = 0;

  /**
   * @brief Get the Task Result
   *
   * @param taskId - the IDs that were returned by the addTask function
   * @return double - calculation result
   */
  virtual double GetTaskResult(TaskId taskId) = 0;
};

} // namespace balancer
