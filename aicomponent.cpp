#include "aicomponent.h"

#include "btselector.h"

AIComponent::AIComponent(AgentComponent *agentComponent)
    : Component (ComponentType::AIComponent), m_agentComponent(agentComponent)
{
    generateBehaviorTree();
}

void AIComponent::update(PositionComponent *positionComponent)
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
}
