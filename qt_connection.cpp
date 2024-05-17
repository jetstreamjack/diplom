#include "qt_connection.h"

#include <string>
#include <vector>

#include <QThread>

namespace connection {

QtConnection::QtConnection(
    QTcpSocket *socket,
    std::shared_ptr<connection_controller::IConnectionController>
        connectionController)
    : m_socket(socket),
      m_connectionController(std::move(connectionController)) {
}

void QtConnection::StopConnection() { 
  m_socket->close();
}

void QtConnection::StartObserving() {
  m_socket->setParent(nullptr);
  m_mainThread = std::thread(&QtConnection::MainThread, this);
}

void QtConnection::MainThread() {
  m_clientHandle = m_connectionController->RegisterClient();
  while (m_socket->state() == QTcpSocket::ConnectedState) {
    m_currentState = ConnectionState::Connected;
    if (m_socket->state() == QTcpSocket::ConnectedState)
      m_socket->waitForReadyRead();
    if (!m_socket || m_socket->state() != QTcpSocket::ConnectedState) {
      break;
    }
    QByteArray arr = m_socket->readAll();
    qDebug() << "SocketData" << arr;
    auto request = QString::fromUtf8(arr).toStdString();
    m_connectionController->ProcessNewTask(m_clientHandle, request);
    auto res = m_connectionController->GetTaskResult(m_clientHandle);
    if (m_socket->state() == QTcpSocket::ConnectedState)
      m_socket->write(QByteArray(res.c_str(), res.length()));
  }
  m_currentState = ConnectionState::Disconnected;
  m_connectionController->UnregisterClient(m_clientHandle);
  qDebug() << "Stop thread";
}

ConnectionState QtConnection::GetConnectionState() { return m_currentState; }

QtConnection::~QtConnection() {
  if (m_socket->state() == QTcpSocket::ConnectedState)
  {
    m_socket->close();
  }
  m_socket->deleteLater();
  m_mainThread.join();
}

} // namespace connection
