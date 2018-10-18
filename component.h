#ifndef COMPONENT_H
#define COMPONENT_H

enum class ComponentType
{
    AIComponent,
    RenderComponent,
    PositionComponent,
    AmountComponent,
    AgentComponent,
    SpriteComponent
};

class Component
{
public:
    Component(ComponentType type);
    virtual ~Component();
    ComponentType type();

private:
    ComponentType m_type;
};

#endif // COMPONENT_H
