#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVector>
#include <QTimer>
#include <QElapsedTimer>
#include <QThread>

#include "openglwidget.h"
#include "gameobject.h"
#include "characterlistwidget.h"
#include "map.h"

class GameLogic : public QObject
{
    Q_OBJECT
public:
    GameLogic(QVector<GameObject *> *entities);
    ~GameLogic();

    void setTimer(QTimer *updateTimer);

public slots:
    void start();
    void update();
private:
    QVector<GameObject*> *m_entities;
    QTimer *m_updateTimer;
    QTime m_time;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void render(QOpenGLShaderProgram *program);
    void init();

private:
    void initializeSubsystems();
    void loadCharacters();
    void initializeOpenGLWidget();
    void initializeGameWorld();
    void initializeUI();

    QHBoxLayout* m_centralLayout;
    QWidget* m_centralWidget;
    OpenGLWidget* m_openGLWidget;
    QVector<GameObject*> m_entities;
    QVector<GameObject*> m_characters;
    CharacterListWidget* m_characterListWidget;
    Map *m_gameMap;
    QElapsedTimer m_time;
    QThread* m_updateThread;
    GameLogic* m_logic;
};

#endif // MAINWINDOW_H
