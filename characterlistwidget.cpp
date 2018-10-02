#include "characterlistwidget.h"

CharacterListWidget::CharacterListWidget(QVector<GameObject *> &characters, QWidget *parent) : QWidget(parent)
{
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);
    m_scrollArea = new QScrollArea(this);
    m_mainLayout->addWidget(m_scrollArea);
    m_widgetList = new QWidget(this);
    m_listLayout = new QVBoxLayout;
    m_widgetList->setLayout(m_listLayout);
    for (auto character : characters)
    {
        //TODO
    }
    m_scrollArea->setWidget(m_widgetList);
}
