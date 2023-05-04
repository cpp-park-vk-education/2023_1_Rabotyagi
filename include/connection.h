#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QCborStreamReader>
#include <QCborStreamWriter>
#include <QElapsedTimer>
#include <QHostAddress>
#include <QString>
#include <QTimer>

const int BUFSIZE = 1024;

class Connection : public QTcpSocket
{
Q_OBJECT

public:
    enum class ConnectionState
    {
        WaitingForGreeting,
        ReadingGreeting,
        ReadyForUse
    };

    enum class DataType
    {
        PlainText,
        Ping,
        Pong,
        Greeting,
        Undefined
    };

    Connection(QObject* parent = nullptr);
    Connection(qintptr socketDescriptor, QObject* parent = nullptr);
    ~Connection();

    QString Name() const;
    void SetGreetingMessage(const QString& message);
    bool SendMessage(const QString& message);

signals:
    void ready_for_use();
    void new_message(const QString& from, const QString& message);

protected:
    void timerEvent(QTimerEvent* timerEvent) override;

private slots:
    void process_ready_read();
    void send_ping();
    void send_greeting_message();

private:
    bool has_enough_data();
    void process_greeting();
    void process_data();

    QCborStreamReader reader;
    QCborStreamWriter writer;
    QString greeting_message;
    QString username;
    QTimer ping_timer;
    QElapsedTimer pong_time;
    QString buffer;
    ConnectionState state;
    DataType current_data_type;
    int transfer_timer_id;
    bool is_greeting_message_sent;

};

#endif // CONNECTION_H
