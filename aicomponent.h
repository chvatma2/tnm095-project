#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "component.h"

#include "positioncomponent.h"
#include "agentcomponent.h"
#include "btroot.h"
#include "btnode.h"

class AIComponent : public Component
{
public:
    AIComponent(AgentComponent *agentComponent);

    void update(PositionComponent *positionComponent);

private:
    AgentComponent *m_agentComponent = nullptr;
    BTRoot *m_treeRoot = nullptr;
    BTNode *m_currentNode = nullptr;
};

#endif // AICOMPONENT_H
