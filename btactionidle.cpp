#include "btactionidle.h"

#include <QDebug>

BTActionIdle::BTActionIdle(float idleTimeSec, BTAction **loopback, BTNode *parent)
    : BTAction (loopback, parent), m_idleTimeSec(idleTimeSec)
{

}

void BTActionIdle::tick()
{
    qDebug() << "IDLE";
    if(!m_running)
    {
        m_timer.restart();
        m_running = true;
    }
    else
    {
        if(m_timer.elapsed() >= m_idleTimeSec * 1000)
        {
            m_running = false;
            *m_componentReportLoopback = nullptr;
            m_parent->childFinished(true);
        }
    }
}
