#include "btwalkrandom.h"

#include <QRandomGenerator>

BTWalkRandom::BTWalkRandom(AgentComponent *agentComponent, PositionComponent *pos, Map *gameMap, BTAction **componentReportLoopback, BTNode *parent)
    : BTAction (componentReportLoopback, parent), m_agentComponent(agentComponent), m_positionComponent(pos), m_gameMap(gameMap)
{

}

void BTWalkRandom::tick()
{
    if(!m_running)
    {
        QPoint randomPos(static_cast<int>(m_positionComponent->position().x() + QRandomGenerator::global()->generateDouble() * 6 - 3),
                         static_cast<int>(m_positionComponent->position().y() + QRandomGenerator::global()->generateDouble() * 6 - 3));
        if(randomPos.x() < 0)
            randomPos.setX(3);
        if(randomPos.y() < 0)
            randomPos.setY(3);
        if(randomPos.x() >= m_gameMap->width())
            randomPos.setX(m_gameMap->width() - 3);
        if(randomPos.y() >= m_gameMap->height())
            randomPos.setY(m_gameMap->height() - 3);

        m_path = m_gameMap->pathToPoint(m_positionComponent->position(), randomPos);
        if(m_path.empty())
        {
            m_parent->childFinished(false);
            return;
        }

        m_running = true;
        *m_componentReportLoopback = this;
    }

    float speed = m_agentComponent->data().speed / 60.0f;
    QVector2D pos(m_positionComponent->position());
    QVector2D dest(m_path.front());

    QVector2D diff(dest - pos);

    if(diff.length() <= speed )
    {
        m_positionComponent->setPosition(m_path.front());
        m_path.removeFirst();
    }
    else
    {
        m_positionComponent->setPosition((pos + diff.normalized() * speed).toPointF());
    }

    if(m_path.empty())
    {
        m_running = false;
        *m_componentReportLoopback = nullptr;
        m_parent->childFinished(true);
    }
}
