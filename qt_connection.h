#pragma once

#include "i_connection.h"

#include <vector>
#include <string>

namespace socket {

class QtConnection : public IConnection
{
public:
    explicit QtConnection(QTcpSocket *socket, 
    std::shared_ptr<connection_controller::ConnectionController> connectionController);
    //todo(odnorob): add destructor
    // add commentary
    void StopConnection() override;

    void StartObserving() override;

    ConnectionState GetConnectionState() override;

private:
    void MainThread();

private:
    QTcpSocket *m_socket;
    std::shared_ptr<connection_controller::ConnectionController> m_connectionController;
    bool m_stopConnection{false};
    ConnectionState m_currentState{ConnectionState::Disconnected};
    std::thread m_mainThread;
    ClientHandle m_clientHandle;
};

} // socket
