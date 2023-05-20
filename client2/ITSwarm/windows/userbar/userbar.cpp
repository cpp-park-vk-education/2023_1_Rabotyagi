#include "userbar.h"
#include "ui_userbar.h"

Userbar::Userbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Userbar)
{
    ui->setupUi(this);
    ui->partisipants->addItem("Участники");
}

Userbar::~Userbar()
{
    delete ui;
}
