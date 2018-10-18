#ifndef BTNODE_H
#define BTNODE_H

#include <QDebug>

enum class State
{
    RUNNING,
    SUCCESS,
    FAIL
};

class BTNode
{
public:
    BTNode(BTNode* parent = nullptr);
    virtual ~BTNode();
    BTNode* parent() const;
    virtual void execute() = 0;
    virtual void childFinished(bool success) = 0;
    State state() const;

protected:
    BTNode* m_parent;
    State m_currentState = State::FAIL;
};

#endif // BTNODE_H
