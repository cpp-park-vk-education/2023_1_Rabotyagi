#include "tcpclient.h"
#include <QtNetwork>
#include <QIODevice>

TCPClient::TCPClient()
{
    /*socket = std::make_shared<QTcpSocket>();

    connect(socket.get(), &QTcpSocket::readyRead, this, &TCPClient::slotReadyRead);
    connect(socket.get(), &QTcpSocket::disconnected, this, &TCPClient::deleteLater);*/
}

bool TCPClient::ConnectToServer(QString url, qint16 port)
{
    socket = std::make_shared<QTcpSocket>();
    //socket = new QTcpSocket;

    if (socket->state() == QAbstractSocket::UnconnectedState)
        socket->connectToHost(url, port);
    if(!socket->waitForConnected(1000))
    {
        qDebug() << "Can't connect to server";
        return false;
    }

    connect(socket.get(), &QTcpSocket::readyRead, this, &TCPClient::slotReadyRead);
    connect(socket.get(), &QTcpSocket::disconnected, this, &TCPClient::deleteLater);

    qDebug() << "Client successfully created: " << socket->socketDescriptor();
    return true;
}

bool TCPClient::Post(QString url, const QJsonObject &data, const QJsonObject &config)
{
    QUrl requestUrl(url);
    QNetworkRequest request(requestUrl);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("User-Agent", "ITSwarm/1.0");

    QJsonDocument jsonDoc(data);
    QByteArray postData = jsonDoc.toJson();

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(request, postData);

    bool success = false;
    connect(reply, &QNetworkReply::finished, [=, &success]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
            qDebug() << "Response:" << responseDoc.toJson();
            success = true;
        } else {
            qDebug() << "Error:" << reply->errorString();
            success = false;
        }
        reply->deleteLater();
    });

    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    return success;
}

bool TCPClient::Get(QString url, const QJsonObject &config)
{
    QUrl requestUrl(url);
    QNetworkRequest request(requestUrl);

    // Устанавливаем заголовки запроса
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("User-Agent", "ITSwarm/1.0");

    // Создаем объект QNetworkAccessManager для отправки запроса
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(request);

    // Обрабатываем ответ от сервера
    bool success = false;
    connect(reply, &QNetworkReply::finished, [=, &success]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Обработка успешного ответа от сервера
            QByteArray responseData = reply->readAll();
            QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
            qDebug() << "Response:" << responseDoc.toJson();
            success = true;
        } else {
            // Обработка ошибки при отправке запроса
            qDebug() << "Error:" << reply->errorString();
            success = false;
        }
        reply->deleteLater();
    });

    // Ждем, пока запрос выполнится
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    return success;
}

QVector<QString> TCPClient::GetChannels(QString url, const QJsonObject& config) const
{
    QVector<QString> channels;

    QUrl requestUrl(url);
    QNetworkRequest request(requestUrl);

    // Устанавливаем заголовки запроса
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("User", "ITSwarm/1.0");

    // Создаем объект QNetworkAccessManager для отправки запроса
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (!doc.isNull() && doc.isArray()) {
            QJsonArray channelsArray = doc.array();
            for (const auto& channel : channelsArray) {
                if (channel.isString()) {
                    channels.append(channel.toString());
                }
            }
        }
    }

    reply->deleteLater();
    return channels;
}

QVector<QString> TCPClient::GetUsers(QString url, const QJsonObject &config) const
{
    QVector<QString> users;

    QUrl requestUrl(url);
    QNetworkRequest request(requestUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument doc(config);
    QByteArray data = doc.toJson();

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(request, data);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonArray array = doc.array();

        for (int i = 0; i < array.size(); i++) {
            QString user = array[i].toString();
            users.append(user);
        }
    } else {
        qDebug() << "Error: " << reply->errorString();
    }

    reply->deleteLater();
    return users;
}

void TCPClient::slotReadyRead()
{
    /*QDataStream in(socket);

    if (in.status() == QDataStream::Ok)
    {
        while (true)
        {
            if (next_block_size == 0)
            {
                if (socket->bytesAvailable() < 2)
                    break;

                in >> next_block_size;
            }

            if (socket->bytesAvailable() < next_block_size)
            {
                break;
            }

            in >> message;
            next_block_size = 0;
        }
        emit newMessages();
    }
    else
    {
        message = "read error";
    }*/
}





