#ifndef BTSEEKINGFOODACTION_H
#define BTSEEKINGFOODACTION_H

#include <QList>
#include <QPoint>

#include "btaction.h"
#include "map.h"
#include "positioncomponent.h"
#include "agentcomponent.h"


class BTSeekingFoodAction : public BTAction
{
public:
    BTSeekingFoodAction(AgentComponent *agentComponent, PositionComponent *pos, Map *gameMap, BTAction **componentReportLoopback, BTNode* parent);

    void tick();
private:
    AgentComponent *m_agentComponent;
    PositionComponent *m_positionComponent;
    Map *m_gameMap = nullptr;
    bool m_running = false;
    QList<QPoint> m_path;
};

#endif // BTSEEKINGFOODACTION_H
