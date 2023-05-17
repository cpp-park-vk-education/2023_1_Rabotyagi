#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class MainWindow;

class Client: public QObject
{
Q_OBJECT

public:
    Client();
    void SendToServer(QString text);
    QString GetMessage() { return message; }
    void ClearMessage() { message.clear(); }
    QString GetName() { return QString::number(socket->socketDescriptor()); }

private:
    //std::shared_ptr<QTcpSocket> socket;
    QTcpSocket* socket;
    QByteArray data;
    QString message;
    qint16 next_block_size;

public slots:
    void slotReadyRead();

signals:
    void newMessages();
};

#endif // CLIENT_H
