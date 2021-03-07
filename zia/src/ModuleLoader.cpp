/*
** EPITECH PROJECT, 2021
** Zia
** File description:
** ModuleLoader
*/

#include "ModuleLoader.hpp"
#include <QDebug>
#include <QDir>

ModuleLoader::ModuleLoader(Mediator *mediator)
{
    QString moduleName = "HTTPModule.dll";
    bool windows = false;
    QDir dir(QDir::currentPath());
    if (dir.dirName() != "bin") {
        if (dir.dirName() != "build")
            dir.cd("build");
        dir.cd("bin");
    }

    auto docList = dir.entryInfoList();
    for (auto file : docList) {
        if (file.fileName() == moduleName)
            windows = true;
    }

    if (!windows) {
        dir.cdUp();
        dir.cd("lib");
        moduleName = "libHTTPModule.so";
    }

    QString path = dir.absolutePath() + "/" + moduleName;
    assert(QLibrary::isLibrary(path));
    QPluginLoader loader(path);

    if (loader.instance()) {
        _plugin = qobject_cast<IModule*>(loader.instance());
        if (_plugin)
            qDebug() << "Module" << moduleName << "loaded.";
        else
            qDebug() << "qobject_cast<> returned nullptr";
    }
    else
        qDebug() << loader.errorString();

    QObject::connect(mediator, SIGNAL(doNewConnection(Client*)), _plugin->getObject(), SLOT(newConnection(Client*)));
    QObject::connect(mediator, SIGNAL(doNewRequest(QByteArray, Client*)), _plugin->getObject(), SLOT(newRequest(QByteArray, Client*)));
    QObject::connect(mediator, SIGNAL(doNewResponse(QByteArray, Client*)), _plugin->getObject(), SLOT(newResponse(QByteArray, Client*)));
    QObject::connect(mediator, SIGNAL(doSendResponse(QByteArray, Client*)), _plugin->getObject(), SLOT(sendResponse(QByteArray, Client*)));
}

ModuleLoader::~ModuleLoader()
{
}
