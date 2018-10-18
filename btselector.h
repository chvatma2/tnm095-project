#ifndef BTSELECTOR_H
#define BTSELECTOR_H

#include "btnode.h"

class BTSelector : public BTNode
{
public:
    BTSelector();
    void tick();
};

#endif // BTSELECTOR_H
