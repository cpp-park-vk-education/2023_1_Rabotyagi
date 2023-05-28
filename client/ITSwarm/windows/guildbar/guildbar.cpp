//#include "guildbar.h"
//#include "ui_guildbar.h"
//#include "QHBoxLayout"

//Guildbar::Guildbar(QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::Guildbar)
//{
//    ui->setupUi(this);
//    QHBoxLayout* hlayout = new QHBoxLayout;
//    ui->scrollArea->setLayout(hlayout);
//    ui->scrollArea->setWidgetResizable(true);
//    //hlayout->addWidget(ui->pushButton)
//}

//Guildbar::~Guildbar()
//{
//    delete ui;
//}

//void Guildbar::on_pushButton_clicked()
//{
//    qDebug() << "clicked";
//    QPushButton* newButton = new QPushButton;
//    //ui->scrollAreaWidgetContents->layout()->addWidget(newButton);
//    ui->scrollAreaWidgetContents
//    ui->scrollArea->update();
//}

#include "guildbar.h"
#include <QDebug>
#include <Qt>

Guildbar::Guildbar(QWidget *parent) : QScrollArea(parent), active_guild(0)
{
    this->resize(600, 50);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_widget = new QWidget(this);
    m_layout = new QHBoxLayout(m_widget);
    m_layout->setSpacing(10);
    m_layout->setDirection(QBoxLayout::RightToLeft);

    QPushButton *button = new QPushButton("+ канал", m_widget);
    button->setFixedSize(QSize(60, 20));
    m_layout->addWidget(button);
    m_layout->setAlignment(button, Qt::AlignRight);

    setWidgetResizable(true);
    setWidget(m_widget);

    connect(button, &QPushButton::clicked, this, &Guildbar::onButtonClicked);
}

void Guildbar::onButtonClicked()
{
    qDebug() << "clicked";
    GuildButton *NewButton = new GuildButton("Канал " + QString::number(m_buttons.count() + 1), m_widget);
    NewButton->guild_id = (int)(m_buttons.count() + 1);
    qDebug() << "Created channel " << NewButton->guild_id;
    NewButton->setFixedSize(QSize(60, 20));

    m_buttons.append(NewButton);
    m_layout->insertWidget(m_buttons.count() - 1, NewButton);


    //connect(NewButton, &GuildButton::NewActiveGuild, this, &Guildbar::ChangeGuild(int));
}

void Guildbar::ChangeGuild(int id)
{
    active_guild = id;
    qDebug() << "Changed guild to " << active_guild;
}

