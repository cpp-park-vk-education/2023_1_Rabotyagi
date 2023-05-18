#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include "windows/channel_widget/channelsidebar.h"
#include <memory>

namespace Ui {
class Sidebar;
}

class Sidebar : public QWidget
{
    Q_OBJECT

public:
    explicit Sidebar(QWidget *parent = nullptr);
    ~Sidebar();

private:
    Ui::Sidebar *ui;

    std::shared_ptr<ChannelSidebar> channel_sidebar;
};

#endif // SIDEBAR_H
