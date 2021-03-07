/*
** EPITECH PROJECT, 2021
** Zia
** File description:
** Request
*/

#include "Request.hpp"

Request::Request()
{
    _method = "";
    _path = "";
    _httpversion = "";
    _body = nullptr;
    _errorCode = 0;
}

Request::~Request()
{}

void Request::setMethod(QString method)
{
    _method = method;
}

void Request::setPath(QString path)
{
    _path = path;
}

void Request::setHTTPVersion(QString httpversion)
{
    _httpversion = httpversion;
}

void Request::setParameters(QMap<QString, QStringList> parameters)
{
    _parameters = parameters;
}

void Request::setBody(QByteArray body)
{
    _body = body;
}

void Request::setErrorCode(int code)
{
    _errorCode = code;
}

const QString Request::getMethod()
{
    return(_method);
}

const QString Request::getPath()
{
    return(_path);
}

const QString Request::getHTTPVersion()
{
    return(_httpversion);
}

const QMap<QString, QStringList> Request::getParameters()
{
    return(_parameters);
}

const QByteArray Request::getBody()
{
    return(_body);
}

const int Request::getErrorCode()
{
    return (_errorCode);
}