#include "btsetdata.h"

BTSetData::BTSetData(std::function<void()> settingFunction, BTNode *parent)
    : BTNode (parent), m_settingFunction(settingFunction)
{

}

void BTSetData::execute()
{
    m_settingFunction();
    m_parent->childFinished(true);
}

void BTSetData::childFinished(bool success)
{

}
