#ifndef BTROOT_H
#define BTROOT_H

#include "btnode.h"

class BTRoot : public BTNode
{
public:
    BTRoot(BTNode* parent = nullptr);
    void setChild(BTNode* child);
    void execute() override;
    void childFinished(bool success) override;

private:
    BTNode *m_child = nullptr;
};

#endif // BTROOT_H
