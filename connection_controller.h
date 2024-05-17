#pragma once

#include "i_balancer.h"
#include "i_connection_controller.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace connection_controller {

class ConnectionController : public IConnectionController {
public:
  explicit ConnectionController(std::unique_ptr<balancer::IBalancer> balancer);

  ClientHandle RegisterClient() override;

  void UnregisterClient(ClientHandle clientHandle) override;

  void ProcessNewTask(ClientHandle clientHandle,
                      std::string taskRequest) override;

  std::string GetTaskResult(ClientHandle clientHandle) override;

private:
  bool CheckClient(ClientHandle clientHandle);

  const std::string СalculationPacket{"WAYAG"};

private:
  std::unique_ptr<balancer::IBalancer> m_balancer;
  std::unordered_map<ClientHandle, balancer::TaskId> m_clientMap;
};

} // namespace connection_controller
