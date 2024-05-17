#pragma once

#include <vector>

namespace connection {

/**
 * @brief listing the states of the current connection
 */
enum ConnectionState { Disconnected, Connected };

/**
 * @brief the interface describing the connection session with the server
 * @details describes the logic of interaction with the current connection
 */
class IConnection {
public:
  virtual ~IConnection() = default;

  /**
   * @brief stops the current connection
   */
  virtual void StopConnection() = 0;

  /**
   * @brief processes the current connection
   */
  virtual void StartObserving() = 0;

  /**
   * @brief Get the current Connection State
   *
   * @return ConnectionState - cureent connection state
   */
  virtual ConnectionState GetConnectionState() = 0;
};

} // namespace connection
