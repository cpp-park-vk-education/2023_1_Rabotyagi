#ifndef USEROPTIONS_H
#define USEROPTIONS_H

#include <QDialog>

namespace Ui {
class UserOptions;
}

class UserOptions : public QDialog
{
    Q_OBJECT

public:
    explicit UserOptions(QWidget *parent = nullptr);
    ~UserOptions();

private slots:
    void on_create_btn_clicked();

private:
    Ui::UserOptions *ui;
};

#endif // USEROPTIONS_H
