#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    QDialog::setWindowTitle("Настройки");
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
