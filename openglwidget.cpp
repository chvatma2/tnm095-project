#include "openglwidget.h"

#include <QDebug>
#include <QMatrix4x4>
#include "mainwindow.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

OpenGLWidget::~OpenGLWidget()
{

}

void OpenGLWidget::resizeGL(int w, int h)
{

}

void OpenGLWidget::paintGL()
{
    static const QColor clearColor(Qt::black);
    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    emit render(m_program);

    QMatrix4x4 p;
    p.ortho(0.0f, width(), height(), 0.0f, -1.0f, 1.0f);
    m_program->setUniformValue("projection", p);
    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 4, 4 * sizeof(GLfloat));


    update();
}

void OpenGLWidget::initializeGL()
{
    QSurfaceFormat format = context()->format();
    format.setSwapInterval(1);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    context()->setFormat(format);
    m_time.start();

    initializeOpenGLFunctions();
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    m_spriteVertexShader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    m_spriteFragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, this);

    const char *vsrc =
        "#version 330 core\n"
        "layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>\n"
        "out vec2 TexCoords;\n"
        "uniform mat4 model;\n"
        "uniform mat4 projection;\n"
        "void main()\n"
        "{\n"
        "    TexCoords = vertex.zw;\n"
        "    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);\n"
        "}\n";
    m_spriteVertexShader->compileSourceCode(vsrc);

    const char *fsrc =
        "#version 330 core\n"
        "in vec2 TexCoords;\n"
        "out vec4 color;\n"
        "uniform sampler2D image;\n"
        "void main()\n"
        "{\n"
        "    color =  texture(image, TexCoords);\n"
        "}\n";
    m_spriteFragmentShader->compileSourceCode(fsrc);

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShader(m_spriteVertexShader);
    m_program->addShader(m_spriteFragmentShader);
    m_program->bindAttributeLocation("vertex", 0);
    m_program->link();
    m_program->bind();
    m_program->setUniformValue("image", 0);
    emit init();
}
