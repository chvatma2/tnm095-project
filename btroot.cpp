#include "btroot.h"

BTRoot::BTRoot(BTNode *parent)
    : BTNode (parent)
{

}

BTRoot::~BTRoot()
{

}

void BTRoot::setChild(BTNode *child)
{
    m_child = child;
}

void BTRoot::tick()
{
    //If not running, do initialization

    //Update

    //If not running, do exit
}
