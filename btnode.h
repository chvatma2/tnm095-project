#ifndef BTNODE_H
#define BTNODE_H

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
    BTNode* parent() const;
    virtual void tick() = 0;
    State state() const;

private:
    BTNode* m_parent;
    State m_currentState = State::FAIL;
};

#endif // BTNODE_H
