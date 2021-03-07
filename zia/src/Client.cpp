/*
** EPITECH PROJECT, 2021
** B-YEP-500-TLS-5-1-zia-remi.deschamps
** File description:
** Client
*/

#include <QObject>
#include "Client.hpp"

Client::Client(QTcpSocket *clientSocket, Mediator *mediator) : _socket(clientSocket)
{
    connect(_socket, &QIODevice::readyRead, this, &Client::socketReadyRead);
    connect(this, &Client::doNewRequest, mediator, &Mediator::newRequest);
    //connect(_socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
    //connect(_socket, &QTcpSocket::readyRead, _socket, &QObject::deleteLater);
    qDebug() << "Create new client";
}

Client::~Client()
{
    _socket->close();
    qDebug() << "Client destroy";
}

void Client::socketReadyRead() 
{
    QByteArray byteMessage;

    byteMessage = _socket->readAll();

    emit doNewRequest(byteMessage, this);
}

bool Client::sendResponse(QByteArray &message) 
{
    qDebug() << "Send Message";
    if (_socket->write(message) == -1)
        return (false);
    return (true);
}