#include "connection_controller.h"

#include <algorithm>
#include <chrono>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include <QCoreApplication>

namespace connection_controller {

namespace {
ClientHandle GenerateUniqId() {
  std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> distr(0, 1000000);
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
  qDebug() << "Id is = " << id;
  m_clientMap.insert(std::make_pair(id, 0));
  return id;
}

void ConnectionController::ProcessNewTask(ClientHandle clientHandle,
                                          std::string taskRequest) {

  if (!CheckClient(clientHandle)) {
    qDebug() << "Client with handle:" << clientHandle << "not found!";
    return;
  }

  auto request = taskRequest.substr(0, 5);

  qDebug() << "General request " << QString::fromStdString(request);

  if (request == СalculationPacket) {

    auto requestBody = taskRequest.substr(5);
    qDebug() << "Request body:" << QString::fromStdString(requestBody);
    auto splitedVec = SplitString(requestBody, '*');

    auto funcNum = std::stoi(splitedVec[1]);

    auto pathVec = SplitString(splitedVec[3], '|');

    std::vector<double> pathDoubleVec;
    pathDoubleVec.resize(pathVec.size());
    std::transform(pathVec.begin(), pathVec.end(), pathDoubleVec.begin(),
                   [](std::string str) { return std::stod(str); });

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
    qDebug() << "Client with handle:" << clientHandle << "not found!";
    return {};
  }
  std::string result;
  if (m_clientMap[clientHandle]) {
    result =
        std::to_string(m_balancer->GetTaskResult(m_clientMap[clientHandle]));
  }
  return result;
}
void ConnectionController::UnregisterClient(ClientHandle clientHandle) {
  m_clientMap.erase(clientHandle);
}

} // namespace connection_controller
