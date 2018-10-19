#include "characterwidget.h"

#include "agentcomponent.h"

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
    m_healthBar->setMinimum(0);
    m_healthBar->setMaximum(100);
    m_mainLayout->addWidget(m_nameLabel);


    m_hungerBar = new QProgressBar;
    m_hungerBar->setMinimum(0);
    m_hungerBar->setMaximum(100);

    QHBoxLayout *healthBarLayout = new QHBoxLayout;
    healthBarLayout->addWidget(new QLabel("   HP"));
    healthBarLayout->addWidget(m_healthBar);
    m_mainLayout->addLayout(healthBarLayout);

    QHBoxLayout *hungerBarLayout = new QHBoxLayout;
    hungerBarLayout->addWidget(new QLabel("Hunger"));
    hungerBarLayout->addWidget(m_hungerBar);
    m_mainLayout->addLayout(hungerBarLayout);

    QHBoxLayout *harvestedLayout = new QHBoxLayout;
    harvestedLayout->addWidget(new QLabel("Harvested: "));
    m_harvestedWood = new QLabel;
    harvestedLayout->addWidget(m_harvestedWood);
    m_mainLayout->addLayout(harvestedLayout);

    QHBoxLayout* lazinessLayout = new QHBoxLayout;
    lazinessLayout->addWidget(new QLabel("Laziness"));
    lazinessLayout->addWidget(m_lazinessSlider);
    m_mainLayout->addLayout(lazinessLayout);
    setLayout(m_mainLayout);
    updateCharacterWidget();

    connect(m_lazinessSlider, &QSlider::valueChanged, this, &CharacterWidget::setLaziness);
}

void CharacterWidget::updateCharacterWidget()
{
    AgentComponent *agentComponent = dynamic_cast<AgentComponent*>(m_character->component(ComponentType::AgentComponent));
    healthChange(agentComponent->data().health);

    hungerChange(agentComponent->data().hunger);

    setLaziness(agentComponent->data().laziness);

    m_harvestedWood->setText(QString::number(agentComponent->data().harvestedWood));
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

void CharacterWidget::hungerChange(int hunger)
{
    m_hunger = hunger;
    m_hungerBar->setValue(hunger);
}

void CharacterWidget::setName(const QString &name)
{
    m_name = name;
    m_nameLabel->setText(m_name);
}

void CharacterWidget::setLaziness(int laziness)
{
    m_lazinessSlider->setValue(laziness);
    AgentComponent *agentComponent = dynamic_cast<AgentComponent*>(m_character->component(ComponentType::AgentComponent));
    agentComponent->data().laziness = laziness;

}
