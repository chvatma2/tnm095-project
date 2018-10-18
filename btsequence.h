#ifndef BTSEQUENCE_H
#define BTSEQUENCE_H

#include "btnode.h"

#include <QVector>

class BTSequence : public BTNode
{
public:
    BTSequence(BTNode *parent);
    void addChild(BTNode* child);
    void execute() override;
    void childFinished(bool succeeded) override;

private:
    QVector<BTNode*> m_children;
    int m_currentlyRunningChild = -1;
};

#endif // BTSEQUENCE_H
