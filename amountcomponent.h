#ifndef AMOUNTCOMPONENT_H
#define AMOUNTCOMPONENT_H

#include "component.h"

class AmountComponent : public Component
{
public:
    AmountComponent(float amount);

    float amount() const;
    void changeAmount(float delta);

private:
    float m_amount = 1.0f;
};

#endif // AMOUNTCOMPONENT_H
