/*
** EPITECH PROJECT, 2018
** ModuleHTTP.cpp
** File description:
** function
*/

#include "ModuleHTTP.hpp"
#include <QDebug>
#include <QTextCodec>
#include <QSettings>

ModuleHTTP::ModuleHTTP()
{
    _request = new Request();
    _code.insert(100, "Continue");
    _code.insert(101, "Switching Protocols");
    _code.insert(200, "OK");
    _code.insert(201, "Create");
    _code.insert(202, "Accepted");
    _code.insert(203, "Non-Authoritative Information");
    _code.insert(204, "No Content");
    _code.insert(205, "Reset Content");
    _code.insert(206, "Partial Content");
    _code.insert(300, "Multiple Choices");
    _code.insert(301, "Moved Permanently");
    _code.insert(302, "Found");
    _code.insert(303, "See Other");
    _code.insert(304, "Not Modified");
    _code.insert(305, "Use Proxy");
    _code.insert(306, "(Unused)");
    _code.insert(307, "Temporary Redirect");
    _code.insert(400, "Bad Request");
    _code.insert(401, "Unauthorized");
    _code.insert(402, "Payment Required");
    _code.insert(403, "Forbidden");
    _code.insert(404, "Not Found");
    _code.insert(405, "Method Not Allowed");
    _code.insert(406, "Not Acceptable");
    _code.insert(407, "Proxy Authentication Required");
    _code.insert(408, "Request Timeout");
    _code.insert(409, "Conflict");
    _code.insert(410, "Gone");
    _code.insert(411, "Length Required");
    _code.insert(412, "Precondition Failed");
    _code.insert(413, "Request Entity Too Large");
    _code.insert(414, "Request-URI Too Long");
    _code.insert(415, "Unsupported Media Type");
    _code.insert(416, "Requested Range Not Satisfiable");
    _code.insert(417, "Expectation Failed");
    _code.insert(500, "Internal Server Error");
    _code.insert(501, "Not Implemented");
    _code.insert(502, "Bad Gateway");
    _code.insert(503, "Service Unavailable");
    _code.insert(504, "Requested Range Not Satisfiable");
    _code.insert(505, "HTTP Version Not Supported");

    _functionPointer["GET"] = std::bind(&ModuleHTTP::get, this);
    _functionPointer["HEAD"] = std::bind(&ModuleHTTP::head, this);
    _functionPointer["POST"] = std::bind(&ModuleHTTP::post, this);
    _functionPointer["PUT"] = std::bind(&ModuleHTTP::put, this);
    _functionPointer["DELETE"] = std::bind(&ModuleHTTP::commandDelete, this);
    _functionPointer["CONNECT"] = std::bind(&ModuleHTTP::connect, this);
    _functionPointer["OPTIONS"] = std::bind(&ModuleHTTP::options, this);
    _functionPointer["TRACE"] = std::bind(&ModuleHTTP::trace, this);
    _functionPointer["PATCH"] = std::bind(&ModuleHTTP::patch, this);

    QSettings settings("ServerZIA.ini", QSettings::IniFormat);
    _serverPath = settings.value("connection/path").toString();
}

void ModuleHTTP::newConnection(Client *client)
{

}

void ModuleHTTP::newRequest(QByteArray request, Client *client)
{
    QString s(request);
    QStringList tokens = s.split("\r\n");
    if (tokens[1].size() == 0) {
        _request->setErrorCode(400);
        return;
    }

    qDebug() << s;
    qDebug() << "-----Commands-----";

    if (tokens.size() == 1 || tokens.at(0).size() == 0 || tokens.at(1).size() == 0) {
        _request->setErrorCode(400);
        return;
    }

    if (tokens.at(0).size() == 0) {
        _request->setErrorCode(400);
        return;
    }
    QStringList command = tokens.at(0).split(" ");
    qDebug() << command;
    tokens.removeAt(0);
    qDebug() << command;
    if (command.size() != 3) {
        _request->setErrorCode(400);
        return;
    }
    _request->setMethod(command.at(0));
    _request->setPath(command.at(1));
    _request->setHTTPVersion(command.at(2));

    qDebug() <<"Method:" << _request->getMethod();
    qDebug() <<"Path:" << _request->getPath();
    qDebug() <<"HTTPVersion:" << _request->getHTTPVersion();
    qDebug() << "-----Parameters-----";

    QStringList key;
    QStringList values;
    QMap<QString, QStringList> parameters;
    qDebug() << tokens;
    if (!tokens.contains("")) {
        _request->setErrorCode(400);
        return;
    }
    while (tokens.at(0) != "") {
        if (!tokens.at(0).contains(": ")) {
            _request->setErrorCode(400);
            return;
        }
        key = tokens.at(0).split(": ");
        tokens.removeAt(0);
        values = key.at(1).split(",");
        parameters.insert(key.at(0), values);
    }
    _request->setParameters(parameters);

    if (parameters.size() == 0) {
        _request->setErrorCode(400);
        return;
    }

    for (auto e : _request->getParameters().keys()) {
        qDebug() <<"Key:" << e << ", value:" << _request->getParameters().value(e);
    }
    tokens.removeAll("");

    qDebug() << "-----Body-----";

    _request->setBody(tokens.at(0).toLocal8Bit());

    qDebug() << "Body:" << _request->getBody();

    tokens.removeAt(0);

    qDebug() << "-----Rest-----\n" << tokens;
}

void ModuleHTTP::newResponse(QByteArray str, Client *client)
{
    Response *response = new Response;
    if (_request->getErrorCode() == 400)
        response->setCode(400);
    else {
        if (_functionPointer.find(_request->getMethod()) != _functionPointer.end())
            response = _functionPointer[_request->getMethod()](*this);
        else
            response->setCode(400);
    }
    QString formatedResponse = "";

    formatedResponse += response->getHTTPVersion();
    formatedResponse += " ";
    qDebug() << formatedResponse;
    formatedResponse += QString::number(response->getCode());
    formatedResponse += " ";
    qDebug() << formatedResponse;
    formatedResponse += _code.find(response->getCode()).value();
    formatedResponse += "\r\n";
    qDebug() << formatedResponse;
    if (!response->getParameters().isEmpty()) {
        for (auto mapIt = response->getParameters().begin(); mapIt != response->getParameters().end(); mapIt ++) {
            formatedResponse += mapIt.key();
            formatedResponse += ": ";
            for (quint16 listIt = 0; listIt < mapIt.value().size(); listIt ++) {
                formatedResponse += mapIt.value()[listIt];
                if (listIt + 1 < mapIt.value().size()) {
                    formatedResponse += ",";
                }
            }
            formatedResponse += "\r\n";
        }
    }
    formatedResponse += "\r\n";

    // Debug print (to delete)
    _response = formatedResponse.toUtf8();
    _response += response->getBody();
//    qDebug() << "-----Response-----\n" << _response;
}

void ModuleHTTP::sendResponse(QByteArray str, Client *client)
{
    qDebug() << "SendResponse";
    client->sendResponse(_response);
}

Response *ModuleHTTP::get()
{
    qDebug() << "Get Function";
    Response *response = new Response();
    QMap<QString, QStringList> parameters;
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QStringList date;
    QStringList contentLength;
    QStringList contentType;

    response->setCode(200);
    date.append(cd.toString());
    date.append(ct.toString());
    parameters.insert("Date", date);
    if (_request->getPath() == "/") {
        _request->setPath("index.html");
    }
    if (_request->getPath().contains(".", Qt::CaseInsensitive)) {
        QString path = _request->getPath();
        QStringList tmp = path.split('.');
        if (tmp[1] == "html" || tmp[1] == "css" || tmp[1] == "txt" || tmp[1] == "js") {
            contentType.append("text/" + tmp[1]);
            if (tmp[1] == "js")
                contentType.append("text/javascript");
            parameters.insert("Content-Type", contentType);
            path = _serverPath + path;
            QFile file(path);
            if (!QFileInfo::exists(path)) {
                response->setCode(404);
                qDebug() << "ERROR: No file or directory";
            } else {
                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    response->setCode(403);
                    qDebug() << "ERROR: Unauthorized acces";
                } else {
                    QString tmpFile = QTextCodec::codecForMib(106)->toUnicode(file.readAll());
                    contentLength.append(QString::number(tmpFile.size()));
                    parameters.insert("Content-Length", contentLength);
                    response->setBody(tmpFile.toUtf8());
                    qDebug() << "OK: bon fichier send";
                }
            }
        } else if (tmp[1] == "jpeg" || tmp[1] == "png" || tmp[1] =="jpg" || tmp[1] == "gif") {
            QFile file("www" + path);
            if (!file.exists()) {
                response->setCode(404);
                qDebug() << "ERROR: File doesn't exist";  
            }
            else {
                if (!file.open(QIODevice::ReadOnly)) {
                    response->setCode(403);
                    qDebug() << "ERROR: Unauthorized access";                
                } else {
                    response->setBody(file.readAll());
                    QString tmptype = "image/" + tmp[1];
                    contentType.append(tmptype);
                    parameters.insert("Content-Type", contentType);
                    contentLength.append(QString::number(file.size()));
                    parameters.insert("Content-Length", contentLength);
                }
            }
        }
        else {
            QFile file("www" + path);
            if (!file.exists()) {
                response->setCode(404);
                qDebug() << "ERROR: File doesn't exist";  
            }
            else {
                response->setCode(501);
                qDebug() << "ERROR: File type not handled";  
            }
        }
    } else {
        QString path = _request->getPath();
        contentType.append("text/html");
        parameters.insert("Content-Type", contentType);
        path = "www/" + path;
        QFile file(path);
        if (!file.exists()) {
            response->setCode(404);
            qDebug() << "ERROR: File doesn't exist";  
        }
        else {
            QFileInfo infoFile(file);
            qDebug() << infoFile.permissions();
            if (infoFile.isDir()) {
                QString tmpFile = getDirectoryBrowsing(path);
                contentLength.append(QString::number(tmpFile.size()));
                parameters.insert("Content-Length", contentLength);
                response->setBody(tmpFile.toUtf8());
                qDebug() << "OK: bon fichier send";
            } else {
                response->setCode(501);
                qDebug() << "ERROR: File type not handled";
            }
        }
    }
    response->setParameters(parameters);
    return (response);
}

Response *ModuleHTTP::head()
{
    Response *tmp = get();
    tmp->setBody(nullptr);
    return(tmp);
}

Response *ModuleHTTP::post()
{
    Response *response = new Response();
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QStringList date;
    QStringList contentLocation;
    QString path = _serverPath + _request->getPath();
    QFileInfo info(path);
    QDir dir;

    QMap<QString, QStringList> parameters;
    response->setCode(201);

    date.append(cd.toString());
    date.append(ct.toString());
    parameters.insert("Date", date);

    if (path.contains(".", Qt::CaseInsensitive)) {
        int index = path.lastIndexOf("/");
        QString pathdirectory = path.left(index);
        if (!dir.exists(pathdirectory))
            dir.mkpath(pathdirectory);
        QFile file(path);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << _request->getBody();
            file.close();
            contentLocation.append(_request->getPath());
            parameters.insert("Content-Location", contentLocation);
        } else
            response->setCode(500);
    }
    return (response);
}

Response *ModuleHTTP::put()
{
    Response *response = new Response();
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QStringList date;
    QStringList contentLocation;
    QString path = _serverPath + _request->getPath();
    QFileInfo info(path);
    QDir dir;

    QMap<QString, QStringList> parameters;
    response->setCode(201);

    date.append(cd.toString());
    date.append(ct.toString());
    parameters.insert("Date", date);

    if (path.contains(".", Qt::CaseInsensitive)) {
        int index = path.lastIndexOf("/");
        QString pathdirectory = path.left(index);
        if (!dir.exists(pathdirectory))
            dir.mkpath(pathdirectory);
        QFile file(path);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << _request->getBody();
            file.close();
            contentLocation.append(_request->getPath());
            parameters.insert("Content-Location", contentLocation);
        } else
            response->setCode(500);
    }
    return (response);
}

Response *ModuleHTTP::commandDelete()
{
    Response *response = new Response();
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QStringList date;
    QStringList contentLength;
    QMap<QString, QStringList> parameters;
    response->setCode(200);

    date.append(cd.toString());
    date.append(ct.toString());
    parameters.insert("Date", date);
    QString rootFile = _serverPath; //TMP Value QDir::currentPath() +
    QFile file(rootFile + _request->getPath());
    if (!file.exists()) {
        qDebug() << "Error File";
        response->setCode(404);
        return (response);
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        file.remove();
        response->setCode(204);
        return (response);
    }
    QString tmpFile = QTextCodec::codecForMib(106)->toUnicode(file.readAll());
    contentLength.append(QString::number(tmpFile.size()));
    parameters.insert("Content-Length", contentLength);
    response->setBody(tmpFile.toUtf8());
    file.remove();
    response->setParameters(parameters);
    return (response);
}

Response *ModuleHTTP::connect()
{
    Response *response = new Response();

    response->setCode(501);
    response->setBody(nullptr);
    return (response);
}

Response *ModuleHTTP::options() const
{
    Response *response = new Response();
    QMap<QString, QStringList> parameters;
    QStringList allow;
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QStringList date;

    response->setCode(204);

    allow.append("GET");
    allow.append("HEAD");
    allow.append("POST");
    allow.append("PUT");
    allow.append("DELETE");
    allow.append("CONNECT");
    allow.append("OPTIONS");
    allow.append("TRACE");
    allow.append("PATCH");
    parameters.insert("Allow", allow);
    date.append(cd.toString());
    date.append(ct.toString());
    parameters.insert("Date", date);
    response->setParameters(parameters);
    response->setBody(nullptr);

    return response;
}

Response *ModuleHTTP::trace() const
{
    Response *response = new Response();

    response->setCode(200);
    QString tmp = "TRACE" + _request->getPath();
    response->setBody(tmp.toUtf8());

    return response;
}

Response *ModuleHTTP::patch()
{
    Response *response = new Response();

    response->setCode(501);
    response->setBody(nullptr);
    return (response);
}

QFileInfo ModuleHTTP::getInfoFile(QString path)
{
    QFile file(path);
    QFileInfo fileinfo(file);
    return fileinfo;
}

QString ModuleHTTP::getDirectoryBrowsing(QString path)
{
    //Get Files
    QDir ad(path);
    QString directoryName = ad.dirName();
    QFileInfoList files = ad.entryInfoList();
    qDebug() << files;
    //Get href path
    QString href = "http://localhost:8080/";
    QString tree = "";
    while (ad.dirName() != "www") {
        tree = ad.dirName() + "/" + tree;
        ad.cdUp();
    }
    href += tree;
    //Make body
    QString body = "<html>\n    <body>\n        <h1>Index of " + directoryName + "/</h1>\n        <table>\n            <thead>\n                <th>Name</th><th>Size</th><th>Modification Date</th>\n            </thead>\n            <tbody>";
    for (int i = 0; i < files.size(); ++i) {
        if (files[i].fileName() != ".") {
            body += "\n                <tr><td><a href=\"" + href + files[i].fileName() + "\">" + files[i].fileName();
            if (files[i].isDir())
                body += "/</td><td></td><td>" + files[i].fileTime(QFileDevice::FileModificationTime).toString("dd.MM.yyyy hh:mm:ss") +"</td></tr>";
            else
                body += "</td><td>" + QString::number(files[i].size()) + " B</td><td>" + files[i].fileTime(QFileDevice::FileModificationTime).toString("dd.MM.yyyy hh:mm:ss") +"</td></tr>";
        }
    }
    body += "\n            </tbody>\n        </table>\n    </body>\n</html>";
    //Return
    return (body);
}
