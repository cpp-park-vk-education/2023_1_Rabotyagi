#include "channel_add.h"
#include "ui_channel_add.h"

Channel_Add::Channel_Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Channel_Add)
{
    ui->setupUi(this);
}

Channel_Add::~Channel_Add()
{
    delete ui;
}
