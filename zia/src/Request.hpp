/*
** EPITECH PROJECT, 2021
** Zia
** File description:
** Request
*/

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <QMap>
#include <QString>
#include <QList>
#include <QByteArray>

class Request
{
    public:
        Request();
        ~Request();

        void setMethod(QString);
        void setPath(QString);
        void setHTTPVersion(QString);
        void setParameters(QMap<QString, QStringList>);
        void setBody(QByteArray);
        void setErrorCode(int);

        const QString getMethod();
        const QString getPath();
        const QString getHTTPVersion();
        const QMap<QString, QStringList> getParameters();
        const QByteArray getBody();
        const int getErrorCode();
    private:
        QString _method;
        QString _path;
        QString _httpversion;
        QMap<QString, QStringList> _parameters;
        QByteArray _body;
        int _errorCode;
};

#endif /* !REQUEST_HPP_ */
