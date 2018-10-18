#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "component.h"

#include "positioncomponent.h"
#include "agentcomponent.h"
#include "btroot.h"
#include "btnode.h"
#include "btaction.h"

class AIComponent : public Component
{
public:
    AIComponent(AgentComponent *agentComponent);

    void update(PositionComponent *positionComponent);

private:
    void generateBehaviorTree();

    AgentComponent *m_agentComponent = nullptr;
    BTRoot *m_treeRoot = nullptr;
    BTAction *m_currentAction = nullptr;
};

#endif // AICOMPONENT_H
