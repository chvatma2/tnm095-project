#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include <QPointF>

#include "component.h"

class PositionComponent : public Component
{
public:
    PositionComponent(const QPointF &position);
    ~PositionComponent();
    QPointF position() const;
    void setPosition(const QPointF &newPosition);

private:
    QPointF m_position;
};

#endif // POSITIONCOMPONENT_H
