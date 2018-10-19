#ifndef BTRESTINGACTION_H
#define BTRESTINGACTION_H

#include <QList>
#include <QPoint>

#include "btaction.h"
#include "map.h"
#include "positioncomponent.h"
#include "agentcomponent.h"

class BTRestingAction : public BTAction
{
public:
    BTRestingAction(AgentComponent *agentComponent, PositionComponent *pos, Map *gameMap, BTAction **componentReportLoopback, BTNode* parent);

    void tick();
private:
    AgentComponent *m_agentComponent;
    PositionComponent *m_positionComponent;
    Map *m_gameMap = nullptr;
    bool m_running = false;
    QList<QPoint> m_path;
};

#endif // BTRESTINGACTION_H
