#include "guild.h"

Guild::Guild(QString name): name(name)
{
    created_at = QTime::currentTime();
}
