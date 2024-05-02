#pragma once

#include "qt_connection.h"

#include <vector>
#include <string>

namespace socket {

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
            waitForReadyRead();
            m_currentState = ConnectionState::Connected;
            QByteArray arr =  m_socket->readAll();
            auto request = arr.toStdString();
            m_connectionController->ProcessNewTask(m_clientHandle, request);
            auto res = m_connectionController->GetTaskResult(m_clientHandle);
            m_socket->write(fromStdString(res));
        }
        m_currentState = ConnectionState::Disconnected;
        m_connectionController->UnregisterClient();
    }

    ConnectionState QtConnection::GetConnectionState()
    {
        return m_currentState;
    }

} // socket
