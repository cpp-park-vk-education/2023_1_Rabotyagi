#include "main_window.h"
#include "ui_main_window.h"
#include "settingswindow.h"
#include "gitconnection.h"
#include <memory>
#include <QtWidgets>
#include <QPixmap>
#include <QIcon>
#include <QFont>
#include "sidebar.h"

MainWindow::MainWindow(int* flag, QWidget *parent)
    :QMainWindow(parent),
    ui(new Ui::MainWindow),
    _flag(flag)
{
    ui->setupUi(this);
    QMainWindow::setWindowTitle("ITSwarm");
    ui->gitButton->setIcon(QIcon(":/img/images/icons8-git-50.png"));
    ui->settingsButton->setIcon(QIcon(":/img/images/icons8-settings-50.png"));

    client = std::make_shared<Client>();

    content_window = std::make_shared<ContentWindow>(client, this);
    content_window->move(130, 60);

    userbar = std::make_shared<Userbar>(this);
    userbar->move(970, 110);

    sidebar = std::make_shared<Sidebar>(this);
    sidebar->move(10, 60);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_settingsButton_clicked()
{
    settings = std::make_shared<SettingsWindow>(this);
    settings->setModal(true);
    settings->exec();
}

void MainWindow::on_gitButton_clicked()
{
    git = std::make_shared<GitConnection>(this);
    git->show();
}

