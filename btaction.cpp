#include "btaction.h"

BTAction::BTAction(BTAction **componentReportLoopback, BTNode *parent)
    : BTNode (parent), m_componentReportLoopback(componentReportLoopback)
{

}

void BTAction::execute()
{
    (*m_componentReportLoopback) = this;
    tick();
}

void BTAction::childFinished(bool success)
{

}

