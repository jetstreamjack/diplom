#pragma once

#include "i_server.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>

#include <vector>
#include <cstdin.h>
#include <string>

namespace server {

class Server : public IServer
{
public:
    //virtual ~IServer() = default;
    explicit Server(std::shared_ptr<IConnectionController> connectionController,
        std::shared_ptr<IConnectionObserver> connectionObserver,  
        QObject *parent = 0);

    // add commentary
    int Run(std::string listenOn) override;

    void Stop() override;

public slots:
    void incommingConnection(); // обработчик входящего подключения

private:
    std::shared_ptr<IConnectionController> m_connectionController;
    std::shared_ptr<IConnectionObserver> m_connectionObserver;
    QTcpServer *m_server; // указатель на сервер
};

} // server
