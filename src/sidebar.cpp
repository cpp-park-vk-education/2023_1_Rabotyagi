#include "sidebar.h"
#include "ui_sidebar.h"

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sidebar)
{
    ui->setupUi(this);

    channel_sidebar = std::make_shared<ChannelSidebar>(this);
    channel_sidebar->move(0, 0);
}

Sidebar::~Sidebar()
{
    delete ui;
}
