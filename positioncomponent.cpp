#include "positioncomponent.h"

PositionComponent::PositionComponent(const QPointF &position)
    : Component(ComponentType::PositionComponent), m_position(position)
{

}

PositionComponent::~PositionComponent()
{

}

QPointF PositionComponent::position() const
{
    return m_position;
}

void PositionComponent::setPosition(const QPointF &newPosition)
{
    m_position = newPosition;
}
