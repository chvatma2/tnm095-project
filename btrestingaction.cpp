#include "btrestingaction.h"

#include <QVector2D>

BTRestingAction::BTRestingAction(AgentComponent *agentComponent, PositionComponent *pos, Map *gameMap, BTAction **componentReportLoopback, BTNode *parent)
    : BTAction (componentReportLoopback, parent), m_agentComponent(agentComponent), m_positionComponent(pos), m_gameMap(gameMap)
{

}

void BTRestingAction::tick()
{
    qDebug() << "RESTING TRAVEL";
    if(!m_running)
    {
        m_path = m_gameMap->pathToClosestHouse(m_positionComponent->position());
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
