#include "aicomponent.h"

#include "btselector.h"

AIComponent::AIComponent(AgentComponent *agentComponent)
    : Component (ComponentType::AIComponent), m_agentComponent(agentComponent)
{
    generateBehaviorTree();
}

void AIComponent::update(PositionComponent *positionComponent)
{
}

void AIComponent::generateBehaviorTree()
{
    m_treeRoot = new BTRoot;

}
