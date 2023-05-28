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

private slots:
    void on_create_btn_clicked();

    void on_close_btn_clicked();

signals:
    void channel_created();

private:
    Ui::Channel_Add *ui;

    int CreateChannel();
};

#endif // CHANNEL_ADD_H
