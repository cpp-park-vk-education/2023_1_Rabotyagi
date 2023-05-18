#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "windows/settings_window/settingswindow.h"
#include "windows/gitconnection/gitconnection.h"
#include <memory>
#include "windows/userbar/userbar.h"
#include "windows/content_widget/contentwindow.h"
#include "windows/sidebar/sidebar.h"
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
    void on_settingsButton_clicked();
    void on_gitButton_clicked();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<SettingsWindow> settings;
    std::shared_ptr<GitConnection> git;

    QString nickname;

    std::shared_ptr<Userbar> userbar;
    std::shared_ptr<ContentWindow> content_window;
    std::shared_ptr<Sidebar> sidebar;

};
#endif // MAINWINDOW_H
