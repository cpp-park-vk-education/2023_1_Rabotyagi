#ifndef CHANNELSIDEBAR_H
#define CHANNELSIDEBAR_H

#include <QWidget>
#include <QVector>
#include "controls/data_types/channel/channel.h"
#include "controls/channel_control/channelcontrol.h"

namespace Ui {
class ChannelSidebar;
}

class ChannelSidebar : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelSidebar(QWidget *parent = nullptr);

    void ConnectToChannelControl();
    ~ChannelSidebar();

private slots:
    void on_textChannelButton_1_clicked();

    void on_textChannelButton_2_clicked();

    void on_textChannelButton_3_clicked();

private:

    Ui::ChannelSidebar *ui;

    QVector<std::shared_ptr<Channel>> channels;
    std::shared_ptr<Channel> active_channel;
    std::shared_ptr<ChannelControl> channel_control;
};

#endif // CHANNELSIDEBAR_H
