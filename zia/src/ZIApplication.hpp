#pragma once

#include <QtCore/QCoreApplication>
#include "ZServer.hpp"

class WApplication : public QCoreApplication
{
    Q_OBJECT

    private:
        ZServer _server;
        QString _serverName;
        QString _serverPort;
        QMap<QString, bool> _moduleMap;

        void debugDisplay();
    public:
        WApplication(int &argc, char **argv);
        ~WApplication();

        bool init();
        bool notify(QObject *receiver, QEvent *event) override;
        void setCleanExit();
        
        static void exitQT(int sig);
};