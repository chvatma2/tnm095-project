#include "component.h"

Component::Component(ComponentType type)
    : m_type(type)
{

}

Component::~Component()
{

}

ComponentType Component::type()
{
    return m_type;
}
