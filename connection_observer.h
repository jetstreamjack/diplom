#pragma once

#include <vector>
#include <string>

namespace connection {

using SockId = int;
//using SockPair = std::pair<SockId, std::unique_ptr>
using ConnectionMap = std::unordored_map<SockId, std::unique_ptr<IConnection>>;

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
