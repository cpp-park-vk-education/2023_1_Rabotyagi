#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingswindow.h"
#include "gitconnection.h"
#include <QtWidgets>
#include <QPixmap>
#include <QIcon>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::setWindowTitle("ITSwarm");
    ui->gitButton->setIcon(QIcon(":/img/images/icons8-git-50.png"));
    ui->settingsButton->setIcon(QIcon(":/img/images/icons8-settings-50.png"));
    ui->searchButton->setIcon(QIcon(":/img/images/icons8-search-30.png"));
    ui->moreButton->setIcon(QIcon(":/img/images/icons8-more-24.png"));
    ui->textChannelButton_1->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    ui->textChannelButton_2->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    ui->textChannelButton_3->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    ui->voiceChannelButton_1->setIcon(QIcon(":/img/images/Channels-Iconvoice hovered.png"));
    ui->voiceChannelButton_2->setIcon(QIcon(":/img/images/Channels-Iconvoice hovered.png"));
    ui->voiceChannelButton_3->setIcon(QIcon(":/img/images/Channels-Iconvoice hovered.png"));
    ui->partisipants->addItem("Участники");

    connect(&client, &Client::new_message, this, &MainWindow::append_message);
    connect(&client, &Client::new_client, this, &MainWindow::new_client);
    connect(&client, &Client::client_quit, this, &MainWindow::client_quit);

    nickname = client.NickName();
    new_client(nickname);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::new_client(const QString &nickname)
{
    if (nickname.isEmpty())
        return;
    QColor color = ui->textBrowser->textColor();
    ui->textBrowser->setTextColor(Qt::green);
    QString text = tr("%1 присоединился(-ась) к чату.").arg(nickname);
    ui->textBrowser->append(text);
    ui->textBrowser->setTextColor(color);
    ui->partisipants->addItem(nickname);
}

void MainWindow::client_quit(const QString &nickname)
{
    if (nickname.isEmpty())
        return;

    QList<QListWidgetItem*> items = ui->partisipants->findItems(nickname, Qt::MatchExactly);

    if (items.isEmpty())
        return;

    delete items.at(0);

    QColor color = ui->textBrowser->textColor();
    ui->textBrowser->setTextColor(Qt::red);
    QString text = tr("%1 покинул(-а) чат.").arg(nickname);
    ui->textBrowser->append(text);
    ui->textBrowser->setTextColor(color);
    ui->partisipants->addItem(nickname);
}


void MainWindow::on_settingsButton_clicked()
{
    settings = new SettingsWindow(this);
    settings->setModal(true);
    settings->exec();
}

void MainWindow::on_gitButton_clicked()
{
    git = new GitConnection(this);
    git->show();
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    if (text.isEmpty())
        return;

    client.SendMessage(text);
    append_message(nickname, text);

    ui->lineEdit->clear();
}


void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

void MainWindow::append_message(const QString &from, const QString &msg)
{
    if (from.isEmpty() || msg.isEmpty())
        return;
    //QFont bold_font("bold");
    //ui->textBrowser->setFont(QFont::bold());
    QString text = from + ": " + msg;
    ui->textBrowser->append(text);
}

