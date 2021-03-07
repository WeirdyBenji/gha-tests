/*
** EPITECH PROJECT, 2021
** Zia
** File description:
** Response
*/

#ifndef RESPONSE_HPP_
#define RESPONSE_HPP_

#include <QMap>
#include <QString>
#include <QtGlobal>
#include <QList>
#include <QByteArray>

class Response
{
    public:
        Response();
        ~Response();

        void setHTTPVersion(QString);
        void setCode(qint16);
        void setParameters(QMap<QString, QStringList>);
        void setBody(QByteArray);

        const QString getHTTPVersion();
        const qint16 getCode();
        const QMap<QString, QStringList> getParameters();
        const QByteArray getBody();
    private:
        QString _httpversion;
        qint16 _code;
        QMap<QString, QStringList> _parameters;
        QByteArray _body;
};

#endif /* !REQUEST_HPP_ */
