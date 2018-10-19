#include "btseekingfoodaction.h"

BTSeekingFoodAction::BTSeekingFoodAction(AgentComponent *agentComponent, PositionComponent *pos, Map *gameMap, BTAction **componentReportLoopback, BTNode *parent)
    : BTAction (componentReportLoopback, parent), m_agentComponent(agentComponent), m_positionComponent(pos), m_gameMap(gameMap)
{

}

void BTSeekingFoodAction::tick()
{

}
