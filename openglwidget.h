#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QTime>
#include <QOpenGLShader>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget() override;

signals:
    void render(QOpenGLShaderProgram *program);
    void init();
protected:
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void initializeGL() override;

private:
    QTime m_time;
    QOpenGLShader* m_spriteVertexShader;
    QOpenGLShader* m_spriteFragmentShader;
    QOpenGLShaderProgram *m_program;

};

#endif // OPENGLWIDGET_H
