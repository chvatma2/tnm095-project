#ifndef BTSETDATA_H
#define BTSETDATA_H

#include "btnode.h"

#include <functional>

class BTSetData : public BTNode
{
public:
    BTSetData(std::function<void()> settingFunction, BTNode *parent);

    void execute() override;
    void childFinished(bool success) override;

private:
    std::function<void()> m_settingFunction;
};

#endif // BTSETDATA_H
