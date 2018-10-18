#ifndef BTACTIONIDLE_H
#define BTACTIONIDLE_H

#include "btaction.h"
#include <QTime>

class BTActionIdle : public BTAction
{
public:
    BTActionIdle(float idleTimeSec, BTAction **loopback, BTNode *parent);
    void tick() override;

private:
    float m_idleTimeSec = 0.0f;
    bool m_running = false;
    QTime m_timer;
};

#endif // BTACTIONIDLE_H
