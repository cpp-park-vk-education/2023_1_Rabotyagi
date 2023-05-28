//#ifndef GUILDBAR_H
//#define GUILDBAR_H

//#include <QWidget>

//namespace Ui {
//class Guildbar;
//}

//class Guildbar : public QWidget
//{
//    Q_OBJECT

//public:
//    explicit Guildbar(QWidget *parent = nullptr);
//    ~Guildbar();

//private slots:
//    void on_pushButton_clicked();

//private:
//    Ui::Guildbar *ui;
//};

//#endif // GUILDBAR_H

#ifndef GUILDBAR_H
#define GUILDBAR_H

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>

class GuildButton: public QPushButton
{
Q_OBJECT

public:
    GuildButton(const QString& text, QWidget* parent = nullptr):
        QPushButton(text, parent)
    {
        //connect(this, &QPushButton::clicked, this, &GuildButton::Selected);
    }

    int guild_id;
    //Guildbar* parent;

signals:
    void NewActiveGuild();

private slots:
    void Selected() { qDebug() << "Activated guild " << guild_id; }

};

class Guildbar : public QScrollArea
{
    Q_OBJECT
public:
    explicit Guildbar(QWidget *parent = nullptr);
    void ChangeGuild(int id);

private:
    QWidget *m_widget;
    QHBoxLayout *m_layout;
    QList<GuildButton*> m_buttons;
    int active_guild;


private slots:
    void onButtonClicked();

};



#endif // GUILDBAR_H
