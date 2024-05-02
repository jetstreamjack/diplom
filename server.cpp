#include "server.h"

MyServer::MyServer(std::shared_ptr<IConnectionController> connectionController,
std::shared_ptr<IConnectionObserver> connectionObserver, QObject *parent) :
    m_connectionController(std::move(connectionController)), 
    m_connectionObserver(std::move(connectionObserver))
    QObject(parent)
{
    m_server = new QTcpServer(this);
    //qDebug() << "server listen = " << server->listen(QHostAddress::Any, 6666);
    //connect(server, SIGNAL(newConnection()), this, SLOT(incommingConnection()));
}

void Run(std::string listeningOn)
{
    qDebug() << "server listen = " << m_server->listen(QHostAddress::Any, 6666);
    connect(m_server, SIGNAL(newConnection()), this, SLOT(incommingConnection()));
}

void MyServer::incommingConnection() // обработчик подключений
{
    QTcpSocket * socket = server->nextPendingConnection(); // получаем сокет нового входящего подключения
    m_connectionObserver->ObserveConnection(std::make_unique<QtConnection>(socket, m_connectionController));
}