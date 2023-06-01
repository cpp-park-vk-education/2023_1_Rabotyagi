#ifndef GUILDCONNECTOR_H
#define GUILDCONNECTOR_H

#include <QDialog>

namespace Ui {
class GuildConnector;
}

class GuildConnector : public QDialog
{
    Q_OBJECT

public:
    explicit GuildConnector(QWidget *parent = nullptr);
    ~GuildConnector();
    int ConnectToGuild();

private slots:
    void on_create_btn_clicked();

    void on_close_btn_clicked();

    void on_name_edit_returnPressed();

signals:
    void guild_connected();

private:
    Ui::GuildConnector *ui;
};

#endif // GUILDCONNECTOR_H
