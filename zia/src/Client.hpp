/*
** EPITECH PROJECT, 2021
** B-YEP-500-TLS-5-1-zia-remi.deschamps
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <QObject>
#include <QTcpSocket>
#include "Mediator.hpp"

class Mediator;

class Client : public QObject {
    Q_OBJECT
    public:
        Client(QTcpSocket *clientSocket, Mediator *mediator);
        bool sendResponse(QByteArray &message);
        ~Client();
    public slots:
        void socketReadyRead();
    signals:
        void doNewConnection();
        void doDeconnection();
        void doNewRequest(QByteArray message, Client *client);
    protected:
    private:
        QTcpSocket *_socket;
};

#endif /* !CLIENT_HPP_ */