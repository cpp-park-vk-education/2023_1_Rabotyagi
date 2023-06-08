#include "serverbutton.h"
#include "ui_serverbutton.h"

ServerButton::ServerButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerButton)
{
    ui->setupUi(this);
}

ServerButton::~ServerButton()
{
    delete ui;
}
