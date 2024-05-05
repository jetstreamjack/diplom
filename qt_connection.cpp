#include "qt_connection.h"

#include <vector>
#include <string>

#include <QThread>

namespace connection {

    QtConnection::QtConnection(QTcpSocket *socket,
    std::shared_ptr<connection_controller::ConnectionController> connectionController) 
    : m_socket(socket), m_connectionController(std::move(connectionController))
    {
        m_clientHandle = m_connectionController->RegisterClient();
    }

    void QtConnection::StopConnection()
    {
        m_stopConnection = true;
    }

    void QtConnection::StartObserving()
    {
        m_socket->setParent(nullptr);
        //m_socket->moveToThread(m_thread);
        m_mainThread = std::thread(&QtConnection::MainThread, this);
    }

    void QtConnection::MainThread()
    {
        while(m_socket && !m_stopConnection && m_socket->state() == QTcpSocket::ConnectedState)
        {
            if(m_socket->state() == QTcpSocket::ConnectedState)
                m_socket->waitForReadyRead();
            m_currentState = ConnectionState::Connected;
            if (!m_socket || m_socket->state() != QTcpSocket::ConnectedState)
            {
                break;
            }
            QByteArray arr =  m_socket->readAll();
            qDebug() << "SocketData" << arr;
            auto request = QString::fromUtf8(arr).toStdString();
            m_connectionController->ProcessNewTask(m_clientHandle, request);
            auto res = m_connectionController->GetTaskResult(m_clientHandle);
            if(m_socket)
                m_socket->write(QByteArray(res.c_str(), res.length()));
        }
        m_currentState = ConnectionState::Disconnected;
        m_connectionController->UnregisterClient(m_clientHandle);
        qDebug() << "Stop thread";
        m_socket->close();
        m_socket->deleteLater();
        m_socket = 0;
    }

    ConnectionState QtConnection::GetConnectionState()
    {
        return m_currentState;
    }

    QtConnection::~QtConnection()
    {
        m_stopConnection = true;
        m_mainThread.detach();
    }

} // connection
