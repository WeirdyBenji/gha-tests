/*
** EPITECH PROJECT, 2018
** ModuleHTTP.hpp
** File description:
** header
*/

#ifndef MODULEHTTP_HPP_
#define MODULEHTTP_HPP_

#include <QObject>
#include <QMap>
#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QByteArray>
#include <functional>
#include <QBuffer>
#include <QImage>

#include "IModule.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include "Client.hpp"

class ModuleHTTP : public QObject, public IModule
{

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "zia.IModule")
    Q_INTERFACES(IModule)

public:
    ModuleHTTP();
    ~ModuleHTTP() = default;
    inline QObject *getObject() override {return this;}

public slots:
    void newConnection(Client *client) override;
    void newRequest(QByteArray request, Client *client) override;
    void newResponse(QByteArray, Client *client) override;
    void sendResponse(QByteArray, Client *client) override;

private:
    Response *get();
    Response *head();
    Response *post();
    Response *put();
    Response *commandDelete();
    Response *connect();
    Response *options() const;
    Response *trace() const;
    Response *patch();

    QFileInfo getInfoFile(QString path);
    QString getDirectoryBrowsing(QString path);

    Request *_request;
    QByteArray _response;
    QMap<qint16, QString> _code;
    QMap<QString, std::function<Response *(const ModuleHTTP &)>> _functionPointer;
    QString _serverPath;
};

#endif /* end of include guard: MODULEHTTP_HPP_ */
