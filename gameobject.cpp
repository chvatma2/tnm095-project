#include "gameobject.h"

GameObject::GameObject()
{

}

QVariant GameObject::getVariable(const QString &variableName)
{
    if(!m_variables.contains(variableName))
        return QVariant();
   return m_variables[variableName];
}

void GameObject::addVariable(const QString &variableName, const QVariant &value)
{
    m_variables[variableName] = value;
}

void GameObject::setVariables(QMap<QString, QVariant> variables)
{
    m_variables = variables;
}
