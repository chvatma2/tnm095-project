#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QMap>
#include <QString>
#include <QVariant>

#include "component.h"

class GameObject
{
public:
    GameObject();
    QVariant getVariable(const QString& variableName);
    void addVariable(const QString& variableName, const QVariant &value);
    void setVariables(QMap<QString, QVariant> variables);


private:
    QMap<ComponentType, Component*> m_components;
    QMap<QString, QVariant> m_variables;
};

#endif // GAMEOBJECT_H
