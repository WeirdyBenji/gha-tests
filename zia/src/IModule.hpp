/*
** EPITECH PROJECT, 2021
** Zia
** File description:
** IModule
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_

#include "Client.hpp"
#include <QtPlugin>
#include <QByteArray>
#include <QString>

class IModule {
    public:
        virtual ~IModule() {}
        virtual QObject *getObject() = 0;

    protected:
    private:
    public slots:
        virtual void newConnection(Client*) = 0;
        virtual void newRequest(QByteArray, Client*) = 0;
        virtual void newResponse(QByteArray, Client*) = 0;
        virtual void sendResponse(QByteArray, Client*) = 0;
};

Q_DECLARE_INTERFACE(IModule, "zia.IModule")

#endif /* !IMODULE_HPP_ */
