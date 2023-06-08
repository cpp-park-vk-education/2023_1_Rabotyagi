#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QWidget>

namespace Ui {
class UserSettings;
}

class UserSettings : public QWidget
{
    Q_OBJECT

public:
    explicit UserSettings(QWidget *parent = nullptr);
    ~UserSettings();


public slots:
    void update_user();

private slots:
    void on_pushButton_clicked();

private:
    Ui::UserSettings *ui;
};

#endif // USERSETTINGS_H
