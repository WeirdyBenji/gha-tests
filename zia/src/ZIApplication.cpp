#include "ZIApplication.hpp"
#include <QDebug>
#include <QSettings>
#include <csignal>
#include "ModuleLoader.hpp"

WApplication::WApplication(int &argc, char **argv) :
    QCoreApplication(argc, argv)
{
    qDebug() << "creating a" << metaObject()->className();
}
WApplication::~WApplication()
{
    qDebug() << "Deleting" << metaObject()->className();
}

bool WApplication::init()
{
    QSettings settings("ServerZIA.ini", QSettings::IniFormat);

    /// Get Available Module List
    settings.beginGroup("module");
    QStringList keys = settings.childKeys();
    foreach (QString key, keys) {
        _moduleMap[key] = settings.value(key).toBool();
    }
    settings.endGroup();

    _serverName = settings.value("owner/name").toString();

    settings.beginGroup("connection");
    _serverPort = settings.value("port").toString();
    settings.endGroup();

    /// QSetting Debug
    debugDisplay();

    Mediator *mediator = new Mediator();
    _server.start(_serverName, _serverPort.toInt(), mediator);
    ModuleLoader mLoader(mediator);
    return true;
}

void WApplication::debugDisplay()
{
    qDebug() << "--ServerInformation--";
    //qDebug() << "  -QSettings Path :" << settings.fileName();
    qDebug() << "  -Server Name:" << _serverName;
    qDebug() << "  -Server Port:" << _serverPort;
    qDebug() << "  -Module Available:" << _moduleMap;
    qDebug() << "---------------------";
}

bool WApplication::notify(QObject *receiver, QEvent *event)
{
    bool myDone = true;

    try
    {
        myDone = QCoreApplication::notify(receiver, event);
        //qDebug() << "  New Notify -->" << receiver->metaObject()->className() << "| Event Type -->" << event->registerEventType();
    }
    catch (const std::exception& aEx)
    {
        qCritical() << "Generic C++ exception" << aEx.what();
    }
    catch (...)
    {
        qCritical() << "C'est la merde...";
    }
    return myDone;
}

void WApplication::setCleanExit()
{
    signal(SIGINT, &exitQT);
    signal(SIGTERM, &exitQT);
#ifdef _WIN32
    signal(SIGBREAK, &exitQT);
#endif // WIN32
    qDebug() << "Exit";
}
void WApplication::exitQT(int sig)
{
    (void) sig;
    exit(0);
}