#ifndef AGENTCOMPONENT_H
#define AGENTCOMPONENT_H

#include <QString>

#include "component.h"

struct AgentData
{
    float health = 100.0f;
    float hunger = 0.0f;
    int laziness = 0;
    float speed = 1.0f;
    QString name;
    float harvestedWood = 0.0f;
};

class AgentComponent : public Component
{
public:
    AgentComponent(const AgentData &data);
    ~AgentComponent();
    AgentData &data();
private:
    AgentData m_data;
};

#endif // AGENTCOMPONENT_H
