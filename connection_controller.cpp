#include "connection_controller.h"

#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <sstream>

namespace connection_controller {

namespace {
ClientHandle GenerateUniqId() {
  std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> distr(0, 1000000);
  // TODO(odnorob): add check on unique
  return distr(gen);
}

std::vector<std::string> SplitString(std::string currentString,
                                     char delimeter) {
  std::vector<std::string> result;
  std::stringstream stringStream{currentString};
  std::string str;
  while (getline(stringStream, str, delimeter)) {
    result.push_back(str);
  }
  return result;
}

} // namespace

ConnectionController::ConnectionController(
    std::unique_ptr<balancer::IBalancer> balancer)
    : m_balancer(std::move(balancer)) {
  if (!m_balancer) {
    printf("Balancer is null!");
  }
}

ClientHandle ConnectionController::RegisterClient() {
  auto id = GenerateUniqId();
  m_clientMap.insert(std::make_pair(id, 0));
  return id;
}

void ConnectionController::ProcessNewTask(ClientHandle clientHandle,
                                          std::string taskRequest) {
  if (!CheckClient(clientHandle)) {
    printf("Client with handle: %i not found!", clientHandle);
    return ;
  }

  auto request = taskRequest.substr(0, 5);

  if (request == СalculationPacket) {
    auto requestBody = taskRequest.substr(5);
    auto splitedVec = SplitString(requestBody, '*');
    auto funcNum = std::stoi(splitedVec[0]);

    auto pathVec = SplitString(splitedVec[2], '|');

    std::vector<double> pathDoubleVec;
    pathDoubleVec.resize(pathVec.size());
    std::transform(pathVec.begin(), pathVec.end(), pathDoubleVec.begin(),
                [](std::string str){
    return std::stod(str);} );
    
    m_clientMap[clientHandle] = m_balancer->AddTask(funcNum, pathDoubleVec);
  }
}

bool ConnectionController::CheckClient(ClientHandle clientHandle) {
  return std::find_if(m_clientMap.begin(), m_clientMap.end(),
                      [&](std::pair<ClientHandle, balancer::TaskId> client) {
                        return client.first == clientHandle;
                      }) != m_clientMap.end();
}

std::string ConnectionController::GetTaskResult(ClientHandle clientHandle) {
  if (!CheckClient(clientHandle)) {
    printf("Client with handle: %i not found!", clientHandle);
    return {};
  }
  auto result =
      std::to_string(m_balancer->GetTaskResult(m_clientMap[clientHandle]));
  m_clientMap.erase(clientHandle);
  return result;
}
void ConnectionController::UnregisterClient(ClientHandle clientHandle)
{
  m_clientMap.erase(clientHandle);
}

} // namespace connection_controller
