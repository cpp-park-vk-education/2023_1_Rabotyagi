#ifndef CHANNELSIDEBAR_H
#define CHANNELSIDEBAR_H
#include <QWidget>
#include <QVector>
#include "data_types.hpp"
#include "controls/channel_control/channelcontrol.h"
#include "contentwindow.h"

/*namespace Ui {
    class ChannelSidebar;
}

class ChannelSidebar : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelSidebar(std::shared_ptr<ContentWindow> content_window, QWidget *parent = nullptr);
    void ChangeActiveChannel(std::shared_ptr<Channel> channel);
    //void ConnectToChannelControl();
    ~ChannelSidebar();

public slots:
    void on_textChannelButton_1_clicked();

    void on_textChannelButton_2_clicked();

    void on_textChannelButton_3_clicked();

private:

    Ui::ChannelSidebar *ui;

    QVector<std::shared_ptr<Channel>> channels;
    std::shared_ptr<Channel> active_channel;
    std::shared_ptr<ChannelControl> channel_control;
    std::shared_ptr<ContentWindow> content_window;
};*/

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

class ChannelButton: public QPushButton
{
Q_OBJECT

public:
    ChannelButton(const QString& text, QWidget* parent = nullptr):
        QPushButton(text, parent)
    {
    }

    int channel_id;
};


class ChannelSidebar : public QScrollArea
{
Q_OBJECT

public:
    explicit ChannelSidebar(std::shared_ptr<ContentWindow> content_window, QWidget *parent = nullptr);
    void ChangeActiveChannel(int id);
    //void ConnectToChannelControl();
    //~ChannelSidebar();

private slots:
//    void on_textChannelButton_1_clicked();

//    void on_textChannelButton_2_clicked();

//    void on_textChannelButton_3_clicked();
    void onButtonClicked();
    void onActiveChannelChangeValue(int);

private:

    //Ui::ChannelSidebar *ui;

    QVector<std::shared_ptr<Channel>> channels;
    //std::shared_ptr<Channel> active_channel;
    std::shared_ptr<ChannelControl> channel_control;
    std::shared_ptr<ContentWindow> content_window;
    QWidget* widget;
    QVBoxLayout* layout;
    QList<ChannelButton*> buttons;

    int active_channel;
};


#endif // CHANNELSIDEBAR_H
