#include "connection_observer.h"

#include <chrono>
#include <random>
#include <string>
#include <vector>

namespace connection {

namespace {
SockId GenerateTaskId() {
  std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> distr(0, 1000000);
  return distr(gen);
}

} // namespace

ConnectionObserver::ConnectionObserver() {}

void ConnectionObserver::ObserveConnection(
    std::unique_ptr<IConnection> connection) {
  connection->StartObserving();
  m_connectionMap.insert(
      std::make_pair(GenerateTaskId(), std::move(connection)));
}

} // namespace connection
