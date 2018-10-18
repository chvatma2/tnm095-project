#include "characterwidget.h"

#include <QPalette>

CharacterWidget::CharacterWidget(GameObject *character, QWidget *parent) : QWidget(parent)
{
    m_character = character;
    m_mainLayout = new QVBoxLayout;
    m_nameLabel = new QLabel;
    m_healthBar = new QProgressBar;
    m_lazinessSlider = new QSlider(Qt::Horizontal);
    m_lazinessSlider->setMinimum(0);
    m_lazinessSlider->setMaximum(10);
    m_exportButton = new QPushButton("Export");
    m_healthBar->setMinimum(0);
    m_healthBar->setMaximum(100);
    m_mainLayout->addWidget(m_nameLabel);

    m_mainLayout->addWidget(m_healthBar);
    QHBoxLayout* lazinessLayout = new QHBoxLayout;
    lazinessLayout->addWidget(new QLabel("Laziness"));
    lazinessLayout->addWidget(m_lazinessSlider);
    m_mainLayout->addLayout(lazinessLayout);
    m_mainLayout->addWidget(m_exportButton);
    setLayout(m_mainLayout);
    update();
}

void CharacterWidget::update()
{

}

int CharacterWidget::health()
{
    return m_health;
}

QString CharacterWidget::name()
{
    return m_name;
}

void CharacterWidget::healthChange(int health)
{
    m_health = health;
    m_healthBar->setValue(health);
}

void CharacterWidget::setName(const QString &name)
{
    m_name = name;
    m_nameLabel->setText(m_name);
}

void CharacterWidget::setLaziness(int laziness)
{
    m_lazinessSlider->setValue(laziness);
}
