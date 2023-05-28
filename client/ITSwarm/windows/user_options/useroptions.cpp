#include "useroptions.h"
#include "ui_useroptions.h"

UserOptions::UserOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserOptions)
{
    ui->setupUi(this);
}

UserOptions::~UserOptions()
{
    delete ui;
}
