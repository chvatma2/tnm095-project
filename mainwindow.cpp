#include "mainwindow.h"

#include <QDebug>

#include "aifileloader.h"
#include "agentcomponent.h"
#include "spritecomponent.h"
#include "positioncomponent.h"
#include "rendercomponent.h"
#include "aicomponent.h"
#include "amountcomponent.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1020, 820);
    initializeSubsystems();
    initializeUI();
    m_time.start();
    m_updateThread = new QThread;

    m_logic = new GameLogic(&m_entities);
    m_logic->moveToThread(m_updateThread);
    QTimer *timer = new QTimer;
    timer->moveToThread(m_updateThread);
    m_logic->setTimer(timer);
    connect(m_updateThread, &QThread::started, m_logic, &GameLogic::start);
    m_updateThread->start();
}

MainWindow::~MainWindow()
{
    m_updateThread->quit();
    m_updateThread->wait();

    delete m_updateThread;
    delete m_logic;
}

void MainWindow::render(QOpenGLShaderProgram *program)
{
    m_gameMap->renderTiles(program);
    for(auto entity : m_entities)
        entity->render(program);
    m_characterListWidget->updateCharacterWidgets();
}

void MainWindow::init()
{
    m_gameMap->init();
    for(auto entity : m_entities)
    {
        entity->init();
    }
}

void MainWindow::initializeSubsystems()
{
    initializeGameWorld();
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
        AgentData data;
        auto characterMap = characterDocument.toVariantMap();
        data.health = characterMap["health"].toFloat();
        data.name = characterMap["name"].toString();
        data.hunger = characterMap["hunger"].toFloat();
        data.laziness = characterMap["laziness"].toInt();
        data.speed = characterMap["speed"].toFloat();
        AgentComponent *agentComp = new AgentComponent(data);
        character->setComponent(ComponentType::AgentComponent, agentComp);
        SpriteComponent *spriteComp = new SpriteComponent(32, 32, new QImage(characterMap["texture"].toString()));
        PositionComponent *posComp = new PositionComponent(QPointF(8.0f, 8.0f));
        character->setComponent(ComponentType::SpriteComponent, spriteComp);
        character->setComponent(ComponentType::PositionComponent, posComp);
        RenderComponent *renderComp = new RenderComponent(spriteComp, posComp);
        character->setComponent(ComponentType::RenderComponent, renderComp);
        character->setComponent(ComponentType::AIComponent, new AIComponent(renderComp, posComp, m_gameMap, agentComp));
        m_entities.push_back(character);
        m_characters.push_back(character);
   }
}

void MainWindow::initializeOpenGLWidget()
{
    m_openGLWidget = new OpenGLWidget(this);
    connect(m_openGLWidget, &OpenGLWidget::render, this, &MainWindow::render, Qt::DirectConnection);
    connect(m_openGLWidget, &OpenGLWidget::init, this, &MainWindow::init, Qt::DirectConnection);
}

void MainWindow::initializeGameWorld()
{
    m_gameMap = new Map(16, 16);

    for(int i = 0; i < 30; ++i)
    {
        GameObject* tree = new GameObject;
        SpriteComponent *spriteComp = new SpriteComponent(50, 50, new QImage("textures/tree.png"));
        PositionComponent *posComp = new PositionComponent(QPointF((i * 5) % 13, i%15));
        tree->setComponent(ComponentType::AmountComponent, new AmountComponent(100.0f));
        tree->setComponent(ComponentType::SpriteComponent, spriteComp);
        tree->setComponent(ComponentType::PositionComponent, posComp);
        tree->setComponent(ComponentType::RenderComponent, new RenderComponent(spriteComp, posComp));
        m_gameMap->addResource(QPoint((i * 5) % 13, i%15), tree);

        m_entities.push_back(tree);
    }

    GameObject* tree = new GameObject;
    SpriteComponent *spriteComp2 = new SpriteComponent(50, 50, new QImage("textures/tree.png"));
    PositionComponent *posComp2 = new PositionComponent(QPointF(4.0, 10.0));
    tree->setComponent(ComponentType::AmountComponent, new AmountComponent(100.0f));
    tree->setComponent(ComponentType::SpriteComponent, spriteComp2);
    tree->setComponent(ComponentType::PositionComponent, posComp2);
    tree->setComponent(ComponentType::RenderComponent, new RenderComponent(spriteComp2, posComp2));
    m_gameMap->addResource(QPoint(4.0, 10.0), tree);

    m_entities.push_back(tree);

    GameObject* tavern = new GameObject;
    SpriteComponent *spriteComp = new SpriteComponent(100, 100, new QImage("textures/tavern.png"));
    PositionComponent *posComp = new PositionComponent(QPointF(13.0, 13.0));
    tavern->setComponent(ComponentType::SpriteComponent, spriteComp);
    tavern->setComponent(ComponentType::PositionComponent, posComp);
    tavern->setComponent(ComponentType::RenderComponent, new RenderComponent(spriteComp, posComp));
    m_gameMap->addBuilding(QPoint(13, 13), tavern);
    m_entities.push_back(tavern);
}

void MainWindow::initializeUI()
{
    initializeOpenGLWidget();
    m_centralLayout = new QHBoxLayout;
    m_centralWidget = new QWidget;
    m_characterListWidget = new CharacterListWidget(m_characters);
    m_characterListWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    m_openGLWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    m_centralLayout->addWidget(m_characterListWidget);
    m_centralLayout->addWidget(m_openGLWidget);
    m_centralWidget->setLayout(m_centralLayout);
    setCentralWidget(m_centralWidget);
}

GameLogic::GameLogic(QVector<GameObject *> *entities)
    : QObject (), m_entities(entities)
{
}

GameLogic::~GameLogic()
{

}

void GameLogic::setTimer(QTimer *updateTimer)
{
    m_updateTimer = updateTimer;
}

void GameLogic::start()
{
    connect(m_updateTimer, &QTimer::timeout, this, &GameLogic::update);
    m_updateTimer->setTimerType(Qt::PreciseTimer);
    m_updateTimer->start(16);
    m_time.start();
}

void GameLogic::update()
{
    for(auto entity : *m_entities)
    {
        entity->update();
    }
}
