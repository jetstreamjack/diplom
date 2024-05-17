#include "server.h"

namespace server {

Server::Server(
    std::shared_ptr<connection_controller::IConnectionController>
        connectionController,
    std::shared_ptr<connection::IConnectionObserver> connectionObserver,
    QObject *parent)
    : m_connectionController(std::move(connectionController)),
      m_connectionObserver(std::move(connectionObserver)), QObject(parent) {
  m_server = new QTcpServer(this);
}

void Server::Run(std::string listeningOn) {
  qDebug() << "server listen = " << m_server->listen(QHostAddress::Any, 6666);
  connect(m_server, SIGNAL(newConnection()), this, SLOT(incommingConnection()));
}

void Server::incommingConnection() {
  qDebug() << "incomming connection ready";
  QTcpSocket *socket = m_server->nextPendingConnection();
  m_connectionObserver->ObserveConnection(
      std::move(std::make_unique<connection::QtConnection>(
          socket, m_connectionController)));
}

void Server::Stop() { m_server->close(); }

} // namespace server
