#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QSlider>

#include "gameobject.h"

class CharacterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CharacterWidget(GameObject* character, QWidget *parent = nullptr);
    void updateCharacterWidget();
    int health();
    QString name();

signals:

public slots:
    void healthChange(int health);
    void hungerChange(int hunger);
    void setName(const QString& name);
    void setLaziness(int laziness);

private:
    QVBoxLayout* m_mainLayout;
    QProgressBar* m_healthBar;
    QProgressBar* m_hungerBar;
    QLabel* m_harvestedWood;
    QLabel* m_nameLabel;
    int m_health = 0;
    int m_hunger = 0;
    QString m_name;
    QPushButton* m_exportButton;
    QSlider* m_lazinessSlider;
    GameObject* m_character;
};

#endif // CHARACTERWIDGET_H
