#include <QMessageBox>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include "mainwindow.h"
#include "../ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply) {
    qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute ).toString();
    if (reply->error()) {
    qDebug() << reply->errorString();
    return;
    }

    QString answer = reply->readAll();
    qDebug() << answer;
}

void MainWindow::on_signinSubmit_clicked() {
    QString email = ui->emailInput->text();
    QString password = ui->passwordInput->text();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, [=](QNetworkReply *reply){


            qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute ).toString();
            if (reply->error()) {
            qDebug() << reply->errorString();
            ui->loginErrorLabel->setText(reply->errorString());

            return;
        }

        QString answer = reply->readAll();
        QByteArray br = answer.toUtf8();

        QJsonDocument doc = QJsonDocument::fromJson(br);
        QJsonObject obj = doc.object();

        QJsonValue val(answer);
        QJsonObject lol = val.toObject();

         QMessageBox::information(this, "Login", obj["name"].toString());
        qDebug() << answer;
    });

    QNetworkRequest req = QNetworkRequest(QUrl("http://localhost:8000/api/auth/login"));
    req.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=UTF-8");

    QString pute = QString("{\"email\":\"") + email + QString("\",\"password\":\"") + password + QString("\"}");
    manager->post(req, pute.toStdString());

    if(email == "test" && password == "test") {
        ui->loginErrorLabel->setText("Error");
    } else {
        QMessageBox::warning(this, "Login", "Bad email or password");
    }
}


