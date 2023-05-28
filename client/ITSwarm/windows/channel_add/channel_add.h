#ifndef CHANNEL_ADD_H
#define CHANNEL_ADD_H

#include <QDialog>

namespace Ui {
class Channel_Add;
}

class Channel_Add : public QDialog
{
    Q_OBJECT

public:
    explicit Channel_Add(QWidget *parent = nullptr);
    ~Channel_Add();

private:
    Ui::Channel_Add *ui;
};

#endif // CHANNEL_ADD_H
