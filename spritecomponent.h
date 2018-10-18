#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <QOpenGLTexture>

#include "component.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent(int width, int height, QImage *spriteImage);
    ~SpriteComponent();
    QImage *image();
    int width() const;
    int height() const;
private:
    QImage *m_spriteImage = nullptr;
    int m_width = 0;
    int m_height = 0;
};

#endif // SPRITECOMPONENT_H
