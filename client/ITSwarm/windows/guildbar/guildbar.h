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

private:
    QWidget* widget;
    QHBoxLayout* layout;
    QList<GuildButton*> buttons;
    int active_guild;

private slots:
    void onButtonClicked();
    void onActiveGuildChangeValue(int);

};



#endif // GUILDBAR_H
