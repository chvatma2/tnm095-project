#ifndef BTCONDITION_H
#define BTCONDITION_H

#include "btnode.h"
#include "agentcomponent.h"
#include <functional>

class BTCondition : public BTNode
{
public:
    BTCondition(AgentComponent *agentComponent, std::function<bool()> condition, BTNode* parent = nullptr);
    void execute() override;
    void childFinished(bool success) override;
    void setChild(BTNode *child);

private:
    AgentComponent *m_agentComponent = nullptr;
    std::function<bool()> m_condition;
    BTNode* m_child = nullptr;
};

#endif // BTCONDITION_H
