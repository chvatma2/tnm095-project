#include "btnode.h"

BTNode::BTNode(BTNode *parent)
{
    m_parent = parent;
}

BTNode *BTNode::parent() const
{
    return m_parent;
}