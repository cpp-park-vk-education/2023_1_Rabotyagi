#ifndef USERBAR_H
#define USERBAR_H

#include <QWidget>

namespace Ui {
class Userbar;
}

class Userbar : public QWidget
{
    Q_OBJECT

public:
    explicit Userbar(QWidget *parent = nullptr);
    ~Userbar();

private:
    Ui::Userbar *ui;
};

#endif // USERBAR_H
