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
    void SetName(QString str) { name = str; }
    QString GetName() { return name; }

private:
    //std::shared_ptr<QTcpSocket> socket;
    QString name;
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
