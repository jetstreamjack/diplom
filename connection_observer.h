#pragma once

#include "i_connection.h"
#include "i_connection_observer.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace connection {

using SockId = int;
using ConnectionMap = std::unordered_map<SockId, std::unique_ptr<IConnection>>;

class ConnectionObserver : public IConnectionObserver {
public:
  explicit ConnectionObserver();

  void ObserveConnection(std::unique_ptr<IConnection> connection) override;

private:
  ConnectionMap m_connectionMap;
};

} // namespace connection
