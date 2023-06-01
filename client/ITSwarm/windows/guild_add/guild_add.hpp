#ifndef GUILD_ADD_HPP
#define GUILD_ADD_HPP

#include <QDialog>
#include "guildbar.h"
#include <QWidget>

namespace Ui {
class Guild_Add;
}

class Guild_Add : public QDialog
{
    Q_OBJECT

public:
    explicit Guild_Add(QWidget *parent = nullptr);
    ~Guild_Add();
    int CreateGuild();

private slots:
    void on_create_btn_clicked();

    void on_close_btn_clicked();

    void on_name_edit_returnPressed();

signals:
    void guild_created();

private:
    Ui::Guild_Add *ui;


};

#endif // GUILD_ADD_HPP
