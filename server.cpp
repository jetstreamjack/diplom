#include "server.h"

namespace server {

Server::Server(std::shared_ptr<connection_controller::ConnectionController> connectionController,
        std::shared_ptr<connection::IConnectionObserver> connectionObserver, QObject *parent) :
    m_connectionController(std::move(connectionController)), 
    m_connectionObserver(std::move(connectionObserver)),
    QObject(parent)
{
    m_server = new QTcpServer(this);
    //qDebug() << "server listen = " << server->listen(QHostAddress::Any, 6666);
    //connect(server, SIGNAL(newConnection()), this, SLOT(incommingConnection()));
}

void Server::Run(std::string listeningOn)
{
    qDebug() << "server listen = " << m_server->listen(QHostAddress::Any, 6666);
    connect(m_server, SIGNAL(newConnection()), this, SLOT(incommingConnection()));
}

void Server::incommingConnection() // обработчик подключений
{
    QTcpSocket * socket = m_server->nextPendingConnection(); // получаем сокет нового входящего подключения
    m_connectionObserver->ObserveConnection(std::move(std::make_unique<connection::QtConnection>(socket, m_connectionController)));
}

void Server::Stop()
{
    //todo(odnorob)
}

}
