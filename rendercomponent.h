#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>


#include "component.h"
#include "spritecomponent.h"
#include "positioncomponent.h"

class RenderComponent : public Component
{
public:
    RenderComponent(SpriteComponent* spriteComponent, PositionComponent* positionComponent);
    ~RenderComponent();
    void render(QOpenGLShaderProgram *program);
    void init();
private:
    SpriteComponent* m_spriteComponent;
    PositionComponent* m_positionComponent;

    QOpenGLBuffer m_vbo;
    QOpenGLTexture *m_texture;
};

#endif // RENDERCOMPONENT_H
