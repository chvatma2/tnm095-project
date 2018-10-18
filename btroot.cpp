#include "btroot.h"

BTRoot::BTRoot(BTNode *parent)
    : BTNode (parent)
{

}

void BTRoot::setChild(BTNode *child)
{
    m_child = child;
}

void BTRoot::execute()
{
    qDebug() << "ROOT";
    if(m_child != nullptr)
        m_child->execute();
}

void BTRoot::childFinished(bool success)
{
    return;
}
