/*
** EPITECH PROJECT, 2021
** Zia
** File description:
** Mediator
*/

#include "Mediator.hpp"

Mediator::Mediator()
{
}

Mediator::~Mediator()
{
}

void Mediator::newConnection(Client* client)
{
    emit doNewConnection(client);
}

void Mediator::newRequest(QByteArray string, Client *client)
{
    emit doNewRequest(string, client);
    emit doNewResponse(string, client);
    emit doSendResponse(string, client);
}