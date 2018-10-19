#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "component.h"

#include "positioncomponent.h"
#include "agentcomponent.h"
#include "btroot.h"
#include "btnode.h"
#include "btaction.h"
#include "map.h"

class AIComponent : public Component
{
public:
    AIComponent(PositionComponent *positionComponent, Map* gameMap, AgentComponent *agentComponent);

    void update();

private:
    void generateBehaviorTree();
    BTNode* createWoodCuttingTree(BTNode* parent);
    BTNode* createRestingTree(BTNode* parent);
    BTNode* createEatingTree(BTNode* parent);
    BTNode* createLazyTree(BTNode* parent);

    PositionComponent *m_positionComponent = nullptr;
    AgentComponent *m_agentComponent = nullptr;
    BTRoot *m_treeRoot = nullptr;
    BTAction *m_currentAction = nullptr;
    Map* m_gameMap = nullptr;
};

#endif // AICOMPONENT_H
