#include "server.h"

MyServer::MyServer(QObject *parent) :
    QObject(parent),
    firstSocket(NULL)
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
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState))); // делаем обработчик изменения статуса сокета
    if (!firstSocket) { // если у нас нет "вещающего", то данное подключение становится вещающим
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead())); // подключаем входящие сообщения от вещающего на наш обработчик
        socket->write("server"); // говорим ему что он "вещает"
        firstSocket = socket; // сохраняем себе"
        qDebug() << "this one is server";
    }
    else { // иначе говорим подключенному что он "получатель"
        socket->write("client");
        sockets << socket;
    }
}