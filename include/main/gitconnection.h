#ifndef GITCONNECTION_H
#define GITCONNECTION_H

#include <QDialog>

namespace Ui {
class GitConnection;
}

class GitConnection : public QDialog
{
    Q_OBJECT

public:
    explicit GitConnection(QWidget *parent = nullptr);
    ~GitConnection();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GitConnection *ui;
    bool authorization(QString login, QString password);
};

#endif // GITCONNECTION_H
