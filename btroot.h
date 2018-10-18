#ifndef BTROOT_H
#define BTROOT_H

#include "btnode.h"

class BTRoot : public BTNode
{
public:
    BTRoot(BTNode* parent = nullptr);
    void setChild(BTNode* child);
    void tick();

private:
    BTNode *m_child = nullptr;
};

#endif // BTROOT_H
