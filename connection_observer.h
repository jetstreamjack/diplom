#pragma once

#include "i_connection_observer.h"

#include "i_connection.h"

#include <vector>
#include <string>
#include <unordered_map>

namespace connection {

using SockId = int;
//using SockPair = std::pair<SockId, std::unique_ptr>
using ConnectionMap = std::unordered_map<SockId, std::unique_ptr<IConnection>>;

class ConnectionObserver : public IConnectionObserver
{
public:
    explicit ConnectionObserver();
    //virtual ~IConnectionObserver() = default;

    // add commentary
    void ObserveConnection(std::unique_ptr<IConnection> connection) override;
// public slots: 
//     void readyRead();

private:
    ConnectionMap m_connectionMap;
};

} // connection
