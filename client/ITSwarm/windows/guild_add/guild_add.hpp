#ifndef GUILD_ADD_HPP
#define GUILD_ADD_HPP

#include <QDialog>
#include "guildbar.h"

namespace Ui {
class Guild_Add;
}

class Guild_Add : public QDialog
{
    Q_OBJECT

public:
    explicit Guild_Add(Guildbar *parent = nullptr);
    ~Guild_Add();

private slots:
    void on_create_btn_clicked();

    void on_close_btn_clicked();

signals:
    void guild_created();

private:
    Ui::Guild_Add *ui;

    int CreateGuild();
};

#endif // GUILD_ADD_HPP
