#include "btseektreeaction.h"

BTSeekTreeAction::BTSeekTreeAction(AgentComponent *agentComponent, PositionComponent *pos, Map *gameMap, BTAction **componentReportLoopback, BTNode *parent)
    : BTAction (componentReportLoopback, parent), m_agentComponent(agentComponent), m_positionComponent(pos), m_gameMap(gameMap)
{

}

void BTSeekTreeAction::tick()
{
    if(!m_running)
    {
        m_path = m_gameMap->pathToClosestWood(m_positionComponent->position());
        if(m_path.empty())
        {
            m_parent->childFinished(false);
            return;
        }
        m_targetTree = m_gameMap->objectOnPosition(m_path.back());
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
        QPointF position = dynamic_cast<PositionComponent*>(m_targetTree->component(ComponentType::PositionComponent))->position();
        m_gameMap->changeResourceAmount(QPoint(static_cast<int>(position.x()), static_cast<int>(position.y())), -1.0);
        m_running = false;
        *m_componentReportLoopback = nullptr;
        m_parent->childFinished(true);
        m_targetTree = nullptr;
    }
}
