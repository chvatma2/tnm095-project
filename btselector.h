#ifndef BTSELECTOR_H
#define BTSELECTOR_H

#include "btnode.h"

#include <QVector>

class BTSelector : public BTNode
{
public:
    BTSelector(BTNode *parent = nullptr);
    void execute() override;
    void childFinished(bool success) override;
    void addChild(BTNode *child);

private:
    QVector<BTNode*> m_children;
    int m_currentlyRunningChild = -1;
};

#endif // BTSELECTOR_H
