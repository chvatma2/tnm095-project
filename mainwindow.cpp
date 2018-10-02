#include "mainwindow.h"

#include "aifileloader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1024, 768);
    initializeSubsystems();
    initializeUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initializeSubsystems()
{
    loadCharacters();
}

void MainWindow::loadCharacters()
{
   AIFileLoader loader;
   loader.loadAIFiles();
   auto characterDocuments = loader.characterDocuments();
   for (auto characterDocument : characterDocuments)
   {
        GameObject* character = new GameObject;
        character->setVariables(characterDocument.toVariantMap());
        m_entities.push_back(character);
        m_characters.push_back(character);
   }
}

void MainWindow::initializeOpenGLWidget()
{
    m_openGLWidget = new OpenGLWidget(this);
}

void MainWindow::initializeUI()
{
    initializeOpenGLWidget();
    m_centralLayout = new QHBoxLayout;
    m_centralWidget = new QWidget;
    m_characterListWidget = new CharacterListWidget(m_characters);
    m_centralLayout->addWidget(m_characterListWidget);
    m_centralLayout->addWidget(m_openGLWidget);
    m_centralWidget->setLayout(m_centralLayout);
    setCentralWidget(m_centralWidget);
}
