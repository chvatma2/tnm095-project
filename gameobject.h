#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QMap>
#include <QString>
#include <QVariant>
#include <QOpenGLShaderProgram>

#include "component.h"

class GameObject
{
public:
    GameObject();
    void update();
    void render(QOpenGLShaderProgram *program);
    void init();
    void setComponent(ComponentType type, Component* component);
    Component* component(ComponentType type);

private:
    QMap<ComponentType, Component*> m_components;
};

#endif // GAMEOBJECT_H
