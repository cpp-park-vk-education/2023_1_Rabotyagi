#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingswindow.h"
#include "gitconnection.h"
#include <memory>
#include <QtWidgets>
#include <QPixmap>
#include <QIcon>
#include <QFont>
#include "sidebar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::setWindowTitle("ITSwarm");
    ui->gitButton->setIcon(QIcon(":/img/images/icons8-git-50.png"));
    ui->settingsButton->setIcon(QIcon(":/img/images/icons8-settings-50.png"));

    content_window = std::make_shared<ContentWindow>(this);
    content_window->move(130, 60);

    userbar = std::make_shared<Userbar>(this);
    userbar->move(970, 110);

    sidebar = std::make_shared<Sidebar>(this);
    sidebar->move(10, 60);

    /*connect(&client, &Client::new_message, this, &MainWindow::append_message);
    connect(&client, &Client::new_client, this, &MainWindow::new_client);
    connect(&client, &Client::client_quit, this, &MainWindow::client_quit);

    nickname = client.NickName();*/
    //new_client("User");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::new_client(const QString &nickname)
{
    if (nickname.isEmpty())
        return;
    QColor color = ui->textBrowser->textColor();
    ui->textBrowser->setTextColor(Qt::green);
    QString text = tr("%1 присоединился(-ась) к чату.").arg(nickname);
    ui->textBrowser->append(text);
    ui->textBrowser->setTextColor(color);
    //ui->partisipants->addItem(nickname);
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
}*/


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

