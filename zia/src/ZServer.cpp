#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "ZServer.hpp"

ZServer::ZServer(QObject *aParent) :
    QObject(aParent),
    m_server(new QTcpServer(this))
{
    qDebug() << "Constructing TCP server" << metaObject()->className();
    connect(m_server, &QTcpServer::newConnection, this, &ZServer::newConnection);
}

ZServer::~ZServer()
{
    stop();
    qDebug() << "Destructing TCP server" << metaObject()->className();
}

void ZServer::start(QString aName, const int& aPort, Mediator *mediator)
{
    m_serverName = aName;
    if (!m_server->listen(QHostAddress::Any, aPort)) {
        qDebug() << "Unable to start the server";
        stop();
        exit(1);
    }
    _mediator = mediator;
    qDebug() << "Starting" << aName << "on port" << aPort;
}

void ZServer::stop()
{
    qDebug() << "Closing the TCP server" << m_serverName;
    m_server->close();
}

void ZServer::newConnection()
{
    QTcpSocket* myConnection = m_server->nextPendingConnection();

    connect(myConnection, &QAbstractSocket::disconnected, myConnection, &QObject::deleteLater);
    qDebug() << "Incoming connection" << myConnection->localAddress() << myConnection->localPort();
    _clientList.append(new Client(myConnection, _mediator));
}