/*
** EPITECH PROJECT, 2021
** Zia
** File description:
** Response
*/

#include "Response.hpp"

Response::Response()
{
    _httpversion = "HTTP/1.1";
    _body = nullptr;
}

Response::~Response()
{}

void Response::setHTTPVersion(QString httpversion)
{
    _httpversion = httpversion;
}

void Response::setCode(qint16 code)
{
    _code = code;
}

void Response::setParameters(QMap<QString, QStringList> parameters)
{
    _parameters = parameters;
}

void Response::setBody(QByteArray body)
{
    _body = body;
}

const QString Response::getHTTPVersion()
{
    return(_httpversion);
}

const qint16 Response::getCode()
{
    return(_code);
}

const QMap<QString, QStringList> Response::getParameters()
{
    return(_parameters);
}

const QByteArray Response::getBody()
{
    return(_body);
}
