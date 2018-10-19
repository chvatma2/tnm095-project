#include "gameobject.h"

#include "rendercomponent.h"
#include "aicomponent.h"

GameObject::GameObject()
{

}

void GameObject::update()
{
    if(!m_components.contains(ComponentType::AIComponent))
        return;
    if(!m_components.contains(ComponentType::PositionComponent))
        return; 
    dynamic_cast<AIComponent*>(m_components[ComponentType::AIComponent])->update();
}

void GameObject::render(QOpenGLShaderProgram *program)
{
    if(!m_components.contains(ComponentType::RenderComponent))
        return;
    dynamic_cast<RenderComponent*>(m_components[ComponentType::RenderComponent])->render(program);
}

void GameObject::init()
{
    if(!m_components.contains(ComponentType::RenderComponent))
        return;
    dynamic_cast<RenderComponent*>(m_components[ComponentType::RenderComponent])->init();
}

void GameObject::setComponent(ComponentType type, Component *component)
{
    if(m_components.contains(type))
        delete m_components[type];
    m_components[type] = component;
}

void GameObject::deleteComponent(ComponentType type)
{
    m_components.remove(type);
}

Component *GameObject::component(ComponentType type)
{
    auto component = m_components.find(type);
    if(component == m_components.end())
        return nullptr;
    return component.value();
}
