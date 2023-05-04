#include "connection.h"
#include <QtNetwork>

const int TRANSFER_TIMEOUT = 30 * 1000;
const int PONG_TIMEOUT = 60 * 1000;
const int PING_INTERVAL = 5 * 1000;

Connection::Connection(QObject* parent): QTcpSocket(parent), writer(this)
{
    greeting_message = "Добро пожаловать на сервер!";
    username = "Неизвестный пользователь";
    state = ConnectionState::WaitingForGreeting;
    current_data_type = DataType::Undefined;
    transfer_timer_id = -1;
    is_greeting_message_sent = false;
    ping_timer.setInterval(PING_INTERVAL);

    connect(this, &QTcpSocket::readyRead, this, &Connection::process_ready_read);
    connect(this, &QTcpSocket::disconnected, &ping_timer, &QTimer::stop);
    connect(&ping_timer, &QTimer::timeout, this, &Connection::send_ping);
    connect(this, &QTcpSocket::connected, this, &Connection::send_greeting_message);
}

Connection::Connection(qintptr socketDescriptor, QObject* parent)
    : Connection(parent)
{
    setSocketDescriptor(socketDescriptor);
    reader.setDevice(this);
}

Connection::~Connection()
{
    if (is_greeting_message_sent) {
        writer.endArray();
        waitForBytesWritten(2000);
    }
}

QString Connection::Name() const
{
    return username;
}

void Connection::SetGreetingMessage(const QString &message)
{
    greeting_message = message;
}

bool Connection::SendMessage(const QString &message)
{
    if (message.isEmpty())
        return false;

    writer.startMap(1);
        writer.append(int(DataType::PlainText));
        writer.append(message);
        writer.endMap();
        return true;
}

void Connection::timerEvent(QTimerEvent *timerEvent)
{
    if (timerEvent->timerId() == transfer_timer_id) {
        abort();
        killTimer(transfer_timer_id);
        transfer_timer_id = -1;
    }
}

void Connection::process_ready_read()
{
    reader.reparse();
        while (reader.lastError() == QCborError::NoError)
        {
            if (state == ConnectionState::WaitingForGreeting)
            {
                if (!reader.isArray())
                    break;

                reader.enterContainer();
                state = ConnectionState::ReadingGreeting;
            }
            else if (reader.containerDepth() == 1)
            {
                if (!reader.hasNext())
                {
                    reader.leaveContainer();
                    disconnectFromHost();
                    return;
                }

                if (!reader.isMap() || !reader.isLengthKnown() || reader.length() != 1)
                    break;
                reader.enterContainer();
            }
            else if (current_data_type == DataType::Undefined)
            {
                if (!reader.isInteger())
                    break;
                current_data_type = DataType(reader.toInteger());
                reader.next();
            }
            else
            {
                if (reader.isString())
                {
                    auto r = reader.readString();
                    buffer += r.data;
                    if (r.status != QCborStreamReader::EndOfString)
                        continue;
                } else if (reader.isNull())
                {
                    reader.next();
                } else {
                    break;
                }

                reader.leaveContainer();
                if (transfer_timer_id != -1)
                {
                    killTimer(transfer_timer_id);
                    transfer_timer_id = -1;
                }

                if (state == ConnectionState::ReadingGreeting)
                {
                    if (current_data_type != DataType::Greeting)
                        break;
                    process_greeting();
                } else {
                    process_data();
                }
            }
        }

        if (reader.lastError() != QCborError::EndOfFile)
            abort();

        if (transfer_timer_id!= -1 && reader.containerDepth() > 1)
            transfer_timer_id = startTimer(TRANSFER_TIMEOUT);
}

void Connection::send_ping()
{
    if (pong_time.elapsed() > PONG_TIMEOUT)
    {
        abort();
        return;
    }

    writer.startMap(1);
    writer.append(int(DataType::Ping));
    writer.append(nullptr);     // no payload
    writer.endMap();
}

void Connection::send_greeting_message()
{
    writer.startArray();        // this array never ends

    writer.startMap(1);
    writer.append(int(DataType::Greeting));
    writer.append(greeting_message);
    writer.endMap();
    is_greeting_message_sent = true;

    if (!reader.device())
        reader.setDevice(this);
}

void Connection::process_greeting()
{
    username = buffer + "@" + peerAddress().toString() + ":" + QString::number(peerPort());
    current_data_type = DataType::Undefined;
    buffer.clear();

    if (!isValid())
    {
        abort();
        return;
    }

    if (!is_greeting_message_sent)
        send_greeting_message();

    ping_timer.start();
    pong_time.start();
    state = ConnectionState::ReadyForUse;
    emit ready_for_use();
}

void Connection::process_data()
{
    switch (current_data_type)
    {
        case DataType::PlainText:
            emit new_message(username, buffer);
            break;

    case DataType::Ping:
        writer.startMap(1);
        writer.append(int(DataType::Pong));
        writer.append(nullptr);
        writer.endMap();
        break;

    case DataType::Pong:
        pong_time.restart();
        break;

    default:
        break;
    }

    current_data_type = DataType::Undefined;
    buffer.clear();
}
