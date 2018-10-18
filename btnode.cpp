#include "btnode.h"

BTNode::BTNode(BTNode *parent)
{
    m_parent = parent;
}

BTNode::~BTNode()
{

}

BTNode *BTNode::parent() const
{
    return m_parent;
}

State BTNode::state() const
{
    return m_currentState;
}

