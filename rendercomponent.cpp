#include "rendercomponent.h"

RenderComponent::RenderComponent(SpriteComponent *spriteComponent, PositionComponent *positionComponent)
    : Component (ComponentType::RenderComponent), m_spriteComponent(spriteComponent), m_positionComponent(positionComponent),
      m_vbo(QOpenGLBuffer::VertexBuffer)
{

}

RenderComponent::~RenderComponent()
{
    m_vbo.destroy();
}

void RenderComponent::render(QOpenGLShaderProgram *program)
{   
    if(m_visible)
    {
        QMatrix4x4 modelMatrix;
        m_vbo.bind();
        m_texture->bind();
        QPointF pos = m_positionComponent->position();
        modelMatrix.translate(pos.x() * 50.f, pos.y() * 50.f, 0.0);
        modelMatrix.scale(m_spriteComponent->width(), m_spriteComponent->height(), 1.0f);
        //modelMatrix.translate(0.5f * m_spriteComponent->width(), 0.5f * m_spriteComponent->height());

        program->setUniformValue("model", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void RenderComponent::init()
{
    m_vbo.create();
    m_vbo.bind();
    QVector<GLfloat> vertData;

    vertData.append(1.0f);
    vertData.append(0.0f);
    vertData.append(1.0f);
    vertData.append(0.0f);


    vertData.append(0.0f);
    vertData.append(0.0f);
    vertData.append(0.0f);
    vertData.append(0.0f);

    vertData.append(0.0f);
    vertData.append(1.0f);
    vertData.append(0.0f);
    vertData.append(1.0f);


    vertData.append(0.0f);
    vertData.append(1.0f);
    vertData.append(0.0f);
    vertData.append(1.0f);


    vertData.append(1.0f);
    vertData.append(1.0f);
    vertData.append(1.0f);
    vertData.append(1.0f);


    vertData.append(1.0f);
    vertData.append(0.0f);
    vertData.append(1.0f);
    vertData.append(0.0f);

    m_vbo.allocate(vertData.constData(), vertData.size() * sizeof (GLfloat));

    m_texture = new QOpenGLTexture(*m_spriteComponent->image());
}

void RenderComponent::setVisibility(bool visible)
{
    m_visible = visible;
}
