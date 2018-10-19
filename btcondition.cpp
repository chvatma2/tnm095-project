#include "btcondition.h"

BTCondition::BTCondition(AgentComponent *agentComponent, std::function<bool()> condition, BTNode *parent)
    : BTNode (parent), m_agentComponent(agentComponent), m_condition(condition)
{

}

void BTCondition::execute()
{
    if(!m_child)
    {
        m_parent->childFinished(false);
        return;
    }
    bool conditionResult = m_condition();

    if(conditionResult)
    {
        m_child->execute();
    }
    else
    {
        m_parent->childFinished(false);
    }
}

void BTCondition::childFinished(bool success)
{
    m_parent->childFinished(success);
}

void BTCondition::setChild(BTNode *child)
{
    m_child = child;
}
