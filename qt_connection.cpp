#include "qt_connection.h"

#include <vector>
#include <string>

namespace connection {

    QtConnection::QtConnection(QTcpSocket *socket,
    std::shared_ptr<connection_controller::ConnectionController> connectionController) 
    : m_socket(socket), m_connectionController(std::move(connectionController))
    {
        m_clientHandle = m_connectionController->RegisterClient();
    }

    // add commentary
    void QtConnection::StopConnection()
    {
        m_stopConnection = true;
    }

    void QtConnection::StartObserving()
    {
        m_mainThread = std::thread(&QtConnection::MainThread, this);
    }

    void QtConnection::MainThread()
    {
        while(m_stopConnection && m_socket->state() == QTcpSocket::ConnectedState)
        {
            m_socket->waitForReadyRead();
            m_currentState = ConnectionState::Connected;
            QByteArray arr =  m_socket->readAll();
            auto request = arr.toStdString();
            m_connectionController->ProcessNewTask(m_clientHandle, request);
            auto res = m_connectionController->GetTaskResult(m_clientHandle);
            m_socket->write(QByteArray(res.c_str(), res.length()));
        }
        m_currentState = ConnectionState::Disconnected;
        m_connectionController->UnregisterClient(m_clientHandle);
    }

    ConnectionState QtConnection::GetConnectionState()
    {
        return m_currentState;
    }

} // connection
