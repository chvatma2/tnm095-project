#ifndef BTACTION_H
#define BTACTION_H

#include "btnode.h"

class BTAction : public BTNode
{
public:
    BTAction(BTAction **componentReportLoopback, BTNode* parent);
    void execute() override;
    void childFinished(bool success) override;
    virtual void tick() = 0;

private:
    BTAction **m_componentReportLoopback;
};

#endif // BTACTION_H
