#include "aicomponent.h"

AIComponent::AIComponent(AgentComponent *agentComponent)
    : Component (ComponentType::AIComponent), m_agentComponent(agentComponent)
{

}

void AIComponent::update(PositionComponent *positionComponent)
{
}
