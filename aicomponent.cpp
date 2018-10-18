#include "aicomponent.h"

#include "btselector.h"
#include "btcondition.h"
#include "btactionidle.h"

AIComponent::AIComponent(PositionComponent *positionComponent, Map *gameMap, AgentComponent *agentComponent)
    : Component (ComponentType::AIComponent), m_positionComponent(positionComponent), m_agentComponent(agentComponent), m_gameMap(gameMap)
{
    generateBehaviorTree();
}

void AIComponent::update()
{
    if(m_currentAction == nullptr)
    {
        m_treeRoot->execute();
    }
    else
    {
        m_currentAction->tick();
    }
}

void AIComponent::generateBehaviorTree()
{
    m_treeRoot = new BTRoot;
    auto topSelector = new BTSelector(m_treeRoot);
    m_treeRoot->setChild(topSelector);
    auto idleCondition = new BTCondition(m_agentComponent, []() { return true; } , topSelector);
    topSelector->addChild(idleCondition);
    auto idleAction = new BTActionIdle(1.0f, &m_currentAction, idleCondition);
    idleCondition->setChild(idleAction);
}
