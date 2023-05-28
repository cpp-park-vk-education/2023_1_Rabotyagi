/*#include "channelsidebar.h"
#include "ui_channelsidebar.h"
#include "ui_contentwindow.h"

ChannelSidebar::ChannelSidebar(std::shared_ptr<ContentWindow> content_window, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelSidebar),
    content_window(content_window)
{
    ui->setupUi(this);

    ui->textChannelButton_1->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    ui->textChannelButton_2->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    ui->textChannelButton_3->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    ui->voiceChannelButton_1->setIcon(QIcon(":/img/images/Channels-Iconvoice hovered.png"));
    ui->voiceChannelButton_2->setIcon(QIcon(":/img/images/Channels-Iconvoice hovered.png"));
    ui->voiceChannelButton_3->setIcon(QIcon(":/img/images/Channels-Iconvoice hovered.png"));

    //ConnectToChannelControl();
//    channels.push_back(std::make_shared<Channel>(Channel("1", ChannelType::Message)));
//    channels.push_back(std::make_shared<Channel>(Channel("2", ChannelType::Message)));
//    channels.push_back(std::make_shared<Channel>(Channel("3", ChannelType::Message)));

//    active_channel = channels[0];
}

void ChannelSidebar::ChangeActiveChannel(std::shared_ptr<Channel> channel)
{
    active_channel = channel;
    content_window->ui->textBrowser->clear();
    qDebug() << "switched to anoter channel";
}


ChannelSidebar::~ChannelSidebar()
{
    delete ui;
}

void ChannelSidebar::ConnectToChannelControl()
{
    channel_control = std::make_shared<ChannelControl>();
}

void ChannelSidebar::on_textChannelButton_1_clicked()
{
    ChangeActiveChannel(channels[0]);
    content_window->ChangeActiveChannel(active_channel);
}


void ChannelSidebar::on_textChannelButton_2_clicked()
{
    ChangeActiveChannel(channels[1]);
    content_window->ChangeActiveChannel(active_channel);
}


void ChannelSidebar::on_textChannelButton_3_clicked()
{
    ChangeActiveChannel(channels[2]);
    content_window->ChangeActiveChannel(active_channel);
}
*/

#include "channelsidebar.h"
#include <Qt>

ChannelSidebar::ChannelSidebar(std::shared_ptr<ContentWindow> content_window, QWidget *parent) :
    QScrollArea(parent),
    content_window(content_window),
    active_channel(0)
{
    this->resize(120, 400);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    widget = new QWidget(this);
    layout = new QVBoxLayout(widget);
    layout->setSpacing(10);
    layout->setDirection(QBoxLayout::TopToBottom);

    QPushButton *button = new QPushButton("+ канал", widget);
    button->setFixedSize(QSize(90, 25));
    layout->addWidget(button);
    layout->setAlignment(button, Qt::AlignTop);

    setWidgetResizable(true);
    setWidget(widget);

    connect(button, &QPushButton::clicked, this, &ChannelSidebar::onButtonClicked);
}

void ChannelSidebar::onButtonClicked()
{
    qDebug() << "clicked";
    ChannelButton* NewButton = new ChannelButton("Канал " + QString::number(buttons.count() + 1), widget);
    NewButton->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    NewButton->channel_id = (int)(buttons.count() + 1);
    qDebug() << "Created channel " << NewButton->channel_id;
    NewButton->setFixedSize(QSize(90, 25));

    buttons.append(NewButton);
    layout->insertWidget(buttons.count() - 1, NewButton);


    connect(NewButton, &QPushButton::clicked, this, [this, NewButton]{ onActiveChannelChangeValue(NewButton->channel_id); });
}

void ChannelSidebar::onActiveChannelChangeValue(int channel_id){
    active_channel = channel_id;
    qDebug() << "Changed guild to " << active_channel;
}
