#ifndef SERVERBUTTON_H
#define SERVERBUTTON_H

#include <QWidget>

namespace Ui {
class ServerButton;
}

class ServerButton : public QWidget
{
    Q_OBJECT

public:
    explicit ServerButton(QWidget *parent = nullptr);
    ~ServerButton();

private:
    Ui::ServerButton *ui;
};

#endif // SERVERBUTTON_H
