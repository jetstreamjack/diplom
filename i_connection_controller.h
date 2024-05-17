#pragma once

#include <string>
#include <vector>

namespace connection_controller {

using ClientHandle = uint32_t;

/**
 * @brief provides the necessary functions for processing messages for
 * connection
 */
class IConnectionController {
public:
  virtual ~IConnectionController() = default;

  /**
   * @brief registers a client
   * @details each connection must be registered in order to use other interface
   * functions
   * @return ClientHandle - client handle - it is a necessary token for using
   * various interface functions
   */
  virtual ClientHandle RegisterClient() = 0;

  /**
   * @brief unregister a client
   * @param clientHandle - client handle
   */
  virtual void UnregisterClient(ClientHandle clientHandle) = 0;

  /**
   * @brief accepts a request from an incoming connection
   *
   * @param clientHandle - registered client handle
   * @param taskRequest - request from an incoming connection
   */
  virtual void ProcessNewTask(ClientHandle clientHandle,
                              std::string taskRequest) = 0;

  /**
   * @brief returns the result of the processed request
   *
   * @param clientHandle - registered client handle
   * @return std::string - result of the processed request
   */
  virtual std::string GetTaskResult(ClientHandle clientHandle) = 0;
};

} // namespace connection_controller
