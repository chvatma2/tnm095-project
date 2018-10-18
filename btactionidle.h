#ifndef BTACTIONIDLE_H
#define BTACTIONIDLE_H

#include "btaction.h"

class BTActionIdle : public BTAction
{
public:
    BTActionIdle(BTAction **loopback, BTNode *parent);
    void tick() override;

};

#endif // BTACTIONIDLE_H
