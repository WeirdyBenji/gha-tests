#pragma once
#include <QObject>
#include "Mediator.hpp"
#include "Client.hpp"

class QTcpServer;

class ZServer : public QObject
{
    Q_OBJECT
public:
    explicit ZServer(QObject *aParent = nullptr);
    ~ZServer();

    void start(QString aName = "ZIA Server", const int& aPort = 8080, Mediator *mediator = nullptr);
    void stop();

private slots:
    void newConnection();
    
private:
    QString         m_serverName;
    QTcpServer *    m_server;
    QList<Client *> _clientList;
    Mediator *_mediator;
};