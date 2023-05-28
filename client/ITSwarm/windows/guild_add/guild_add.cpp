#include "guild_add.hpp"
#include "ui_guild_add.h"

Guild_Add::Guild_Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Guild_Add)
{
    ui->setupUi(this);
}

Guild_Add::~Guild_Add()
{
    delete ui;
}
