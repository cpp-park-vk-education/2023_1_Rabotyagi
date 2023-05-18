#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settingswindow.h"
#include "gitconnection.h"
#include <memory>
#include "userbar.h"
#include "contentwindow.h"
#include "sidebar.h"
#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

public slots:
    //void new_client(const QString& nickname);
    //void client_quit(const QString& nickname);
    //void append_message(const QString& from, const QString& msg);
    void on_settingsButton_clicked();
    void on_gitButton_clicked();
    //void on_pushButton_clicked();
    //void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;

    SettingsWindow* settings;
    GitConnection* git;

    QString nickname;

    std::shared_ptr<Userbar> userbar;
    std::shared_ptr<ContentWindow> content_window;
    std::shared_ptr<Sidebar> sidebar;

};
#endif // MAINWINDOW_H
