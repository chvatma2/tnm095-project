#ifndef BTNODE_H
#define BTNODE_H


class BTNode
{
public:
    BTNode(BTNode* parent = nullptr);
    BTNode* parent() const;
    virtual execute() = 0;

private:
    BTNode* m_parent;
};

#endif // BTNODE_H
