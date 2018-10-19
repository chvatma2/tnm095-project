#ifndef BTSEEKTREEACTION_H
#define BTSEEKTREEACTION_H


#include <QList>
#include <QPoint>

#include "btaction.h"
#include "map.h"
#include "positioncomponent.h"
#include "agentcomponent.h"

class BTSeekTreeAction : public BTAction
{
public:
    BTSeekTreeAction(AgentComponent *agentComponent, PositionComponent *pos, Map *gameMap, BTAction **componentReportLoopback, BTNode* parent);

    void tick();
private:
    AgentComponent *m_agentComponent;
    PositionComponent *m_positionComponent;
    Map *m_gameMap = nullptr;
    bool m_running = false;
    QList<QPoint> m_path;
    GameObject* m_targetTree = nullptr;
};
#endif // BTSEEKTREEACTION_H
