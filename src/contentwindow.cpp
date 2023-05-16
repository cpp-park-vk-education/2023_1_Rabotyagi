#include "contentwindow.h"
#include "messagecontrol.h"
#include "ui_contentwindow.h"
#include <QString>

ContentWindow::ContentWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContentWindow)
{
    ui->setupUi(this);
    ui->searchButton->setIcon(QIcon(":/img/images/icons8-search-30.png"));
    ui->moreButton->setIcon(QIcon(":/img/images/icons8-more-24.png"));

    connect_to_message_control();
}

ContentWindow::~ContentWindow()
{
    delete ui;
}


void ContentWindow::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    if (text.isEmpty())
        return;

    QString nickname = "Ilya";
    Message msg(nickname, text);
    message_control->AppendMessage(this, msg);

    ui->lineEdit->clear();
}


void ContentWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

void ContentWindow::connect_to_message_control()
{
    message_control = std::make_shared<MessageControl>();
}


