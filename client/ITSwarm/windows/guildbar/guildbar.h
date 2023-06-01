#ifndef GUILDBAR_H
#define GUILDBAR_H

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <string>

class GuildButton: public QPushButton
{
Q_OBJECT

public:
    GuildButton(const QString& text, QWidget* parent = nullptr):
        QPushButton(text, parent)
    {
        this->setStyleSheet("background-image: url(:/icons/server_idle);"
                            "background-origin: content; "
                            "background-position: center;"
                            "background-repeat: no-repeat;");
//        auto icon = QIcon();
//        icon.addFile(":/icons/server_idle", QSize(54, 58), QIcon::Mode::Normal, QIcon::State::Off);
//        icon.addFile(":/icons/server_hover", QSize(54, 58), QIcon::Mode::Active, QIcon::State::Off);
//        icon.addFile(":/icons/server_selected", QSize(54, 58), QIcon::Mode::Selected, QIcon::State::Off);
        this->setFlat(true);
//        this->setIcon(icon);
    }

    QString guild_name;
    int guild_id;
};


class Guildbar : public QScrollArea
{
Q_OBJECT

public:
    explicit Guildbar(QWidget *parent = nullptr);
    void ChangeGuild(int id);
    void createGuild(int, std::string);
    int GetActiveGuild() {return active_guild;}

private:
    QWidget* widget;
    QHBoxLayout* layout;
    QList<GuildButton*> buttons;
    int active_guild;

private slots:
    void onButtonClicked();
    void onActiveGuildChangeValue(int);

signals:
    void ActiveGuildChanged();

};



#endif // GUILDBAR_H
