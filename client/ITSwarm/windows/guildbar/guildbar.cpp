#include "guildbar.h"
#include <QDebug>
#include <Qt>

Guildbar::Guildbar(QWidget *parent) : QScrollArea(parent), active_guild(0)
{
    this->resize(600, 50);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    widget = new QWidget(this);
    layout = new QHBoxLayout(widget);
    layout->setSpacing(10);
    layout->setDirection(QBoxLayout::RightToLeft);

    QPushButton *button = new QPushButton("+ сервер", widget);
    button->setFixedSize(QSize(70, 20));
    layout->addWidget(button);
    layout->setAlignment(button, Qt::AlignRight);

    setWidgetResizable(true);
    setWidget(widget);

    connect(button, &QPushButton::clicked, this, &Guildbar::onButtonClicked);
}

void Guildbar::onButtonClicked()
{
    qDebug() << "clicked";
    GuildButton* NewButton = new GuildButton("Сервер " + QString::number(buttons.count() + 1), widget);
    NewButton->guild_id = (int)(buttons.count() + 1);
    qDebug() << "Created guild " << NewButton->guild_id;
    NewButton->setFixedSize(QSize(70, 20));

    buttons.append(NewButton);
    layout->insertWidget(buttons.count() - 1, NewButton);


    connect(NewButton, &QPushButton::clicked, this, [this, NewButton]{ onActiveGuildChangeValue(NewButton->guild_id); });
}

void Guildbar::onActiveGuildChangeValue(int guild_id){
    active_guild = guild_id;
    qDebug() << "Changed guild to " << active_guild;
}

