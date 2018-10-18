#include "btactionidle.h"

#include <QDebug>

BTActionIdle::BTActionIdle(BTAction **loopback, BTNode *parent)
    : BTAction (loopback, parent)
{

}

void BTActionIdle::tick()
{
    qDebug() << "tick";
}
