#ifndef GUILD_ADD_HPP
#define GUILD_ADD_HPP

#include <QDialog>

namespace Ui {
class Guild_Add;
}

class Guild_Add : public QDialog
{
    Q_OBJECT

public:
    explicit Guild_Add(QWidget *parent = nullptr);
    ~Guild_Add();

private:
    Ui::Guild_Add *ui;
};

#endif // GUILD_ADD_HPP
