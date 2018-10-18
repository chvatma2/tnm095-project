#include "agentcomponent.h"

AgentComponent::AgentComponent(const AgentData &data)
    : Component (ComponentType::AgentComponent), m_data(data)
{

}

AgentComponent::~AgentComponent()
{

}

AgentData &AgentComponent::data()
{
    return m_data;
}
