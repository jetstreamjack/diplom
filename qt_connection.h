#pragma once

#include "connection_controller.h"
#include "i_connection.h"

#include <string>
#include <vector>

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <thread>

namespace connection {

class QtConnection : public IConnection {
public:
  explicit QtConnection(
      QTcpSocket *socket,
      std::shared_ptr<connection_controller::IConnectionController>
          connectionController);

  ~QtConnection() override;

  void StopConnection() override;

  void StartObserving() override;

  ConnectionState GetConnectionState() override;

private:
  void MainThread();

private:
  QTcpSocket *m_socket;
  std::shared_ptr<connection_controller::IConnectionController> m_connectionController;
  ConnectionState m_currentState{ConnectionState::Disconnected};
  std::thread m_mainThread;
  connection_controller::ClientHandle m_clientHandle;
};

} // namespace connection
