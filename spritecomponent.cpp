#include "spritecomponent.h"

SpriteComponent::SpriteComponent(int width, int height, QImage *spriteImage)
    : Component (ComponentType::SpriteComponent), m_spriteImage(spriteImage), m_width(width), m_height(height)
{

}

SpriteComponent::~SpriteComponent()
{

}

QImage *SpriteComponent::image()
{
    return m_spriteImage;
}

int SpriteComponent::width() const
{
   return m_width;
}

int SpriteComponent::height() const
{
    return m_height;
}
