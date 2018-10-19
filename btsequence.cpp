#include "btsequence.h"

BTSequence::BTSequence(BTNode *parent)
    : BTNode (parent)
{

}

void BTSequence::addChild(BTNode *child)
{
    m_children.push_back(child);
}

void BTSequence::execute()
{
    m_currentlyRunningChild = 0;
    if(m_currentlyRunningChild < m_children.size())
        m_children.at(0)->execute();

}

void BTSequence::childFinished(bool succeeded)
{
    if(!succeeded)
    {
        m_parent->childFinished(false);
    }
    else
    {
        ++m_currentlyRunningChild;
        if(m_currentlyRunningChild < m_children.size())
        {
            m_children.at(m_currentlyRunningChild)->execute();
        }
        else
        {
            m_currentlyRunningChild = -1;
            m_parent->childFinished(true);
        }
    }
}
