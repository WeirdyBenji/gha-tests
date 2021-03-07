/*
** EPITECH PROJECT, 2021
** Zia
** File description:
** Mediator
*/

#ifndef MEDIATOR_HPP_
#define MEDIATOR_HPP_

#include "Client.hpp"
#include <QObject>

class Client;

class Mediator : public QObject
{
    Q_OBJECT

    public:
        Mediator();
        ~Mediator();

    protected:
    private:

    public slots:
        void newConnection(Client*);
        void newRequest(QByteArray, Client*);

    signals:
        void doNewConnection(Client*);
        void doNewRequest(QByteArray, Client*);
        void doNewResponse(QByteArray, Client*);
        void doSendResponse(QByteArray, Client*);
};

#endif /* !MEDIATOR_HPP_ */
