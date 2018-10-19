#include "btselector.h"

BTSelector::BTSelector(BTNode *parent)
    : BTNode (parent)
{

}

void BTSelector::execute()
{
    m_currentlyRunningChild = 0;
    if(m_currentlyRunningChild < m_children.size())
        m_children.at(0)->execute();
}

void BTSelector::childFinished(bool success)
{
    if(success)
    {
        m_currentlyRunningChild = -1;
        m_parent->childFinished(true);
    }
    else
    {
        m_currentlyRunningChild++;
        if(m_currentlyRunningChild < m_children.size())
        {
            m_children.at(m_currentlyRunningChild)->execute();
        }
        else
        {
            m_parent->childFinished(false);
        }
    }
}

void BTSelector::addChild(BTNode *child)
{
    m_children.push_back(child);
}

