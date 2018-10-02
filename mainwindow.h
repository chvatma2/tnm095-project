#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVector>

#include "openglwidget.h"
#include "gameobject.h"
#include "characterlistwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initializeSubsystems();
    void loadCharacters();
    void initializeOpenGLWidget();
    void initializeUI();

    QHBoxLayout* m_centralLayout;
    QWidget* m_centralWidget;
    OpenGLWidget* m_openGLWidget;
    QVector<GameObject*> m_entities;
    QVector<GameObject*> m_characters;
    CharacterListWidget* m_characterListWidget;
};

#endif // MAINWINDOW_H
