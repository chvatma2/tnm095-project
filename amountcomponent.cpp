#include "amountcomponent.h"

AmountComponent::AmountComponent(float amount)
    :Component (ComponentType::AmountComponent), m_amount(amount)
{

}

float AmountComponent::amount() const
{
    return m_amount;
}

void AmountComponent::changeAmount(float delta)
{
    m_amount += delta;
}
