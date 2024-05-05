#pragma once

#include "i_server.h"

#include "qt_connection.h"

#include "connection_controller.h"
#include "connection_observer.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>

#include <vector>
#include <string>

namespace server {

class Server : public QObject, public IServer 
{
    Q_OBJECT
public:
    explicit Server(std::shared_ptr<connection_controller::ConnectionController> connectionController,
        std::shared_ptr<connection::IConnectionObserver> connectionObserver,  
        QObject *parent = 0);

    void Run(std::string listenOn) override;

    void Stop() override;

public slots:
    void incommingConnection();

private:
    std::shared_ptr<connection_controller::ConnectionController> m_connectionController;
    std::shared_ptr<connection::IConnectionObserver> m_connectionObserver;
    QTcpServer *m_server;
};

} // server
