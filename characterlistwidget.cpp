#include "characterlistwidget.h"
#include "agentcomponent.h"

CharacterListWidget::CharacterListWidget(QVector<GameObject *> &characters, QWidget *parent) : QWidget(parent)
{
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);
    m_scrollArea = new QScrollArea(this);
    m_mainLayout->addWidget(m_scrollArea);
    m_widgetList = new QWidget(this);
    m_listLayout = new QVBoxLayout;
    m_widgetList->setLayout(m_listLayout);
    for (GameObject* character : characters)
    {
        //TODO
        CharacterWidget* newWidget = new CharacterWidget(character);
        AgentData data = (dynamic_cast<AgentComponent*>(character->component(ComponentType::AgentComponent)))->data();
        newWidget->setName(data.name);
        newWidget->healthChange(data.health);
        newWidget->setLaziness(data.laziness);
        m_characterList.push_back(newWidget);
        m_listLayout->addWidget(newWidget);
    }
    m_listLayout->addStretch();
    m_scrollArea->setWidget(m_widgetList);
}
