#include "aicomponent.h"

#include <QRandomGenerator>

#include "btselector.h"
#include "btcondition.h"
#include "btactionidle.h"
#include "btsequence.h"
#include "btrestingaction.h"
#include "btsetdata.h"
#include "btseektreeaction.h"
#include "btwalkrandom.h"

AIComponent::AIComponent(RenderComponent *renderComponent, PositionComponent *positionComponent, Map *gameMap, AgentComponent *agentComponent)
    : Component (ComponentType::AIComponent), m_renderComponent(renderComponent), m_positionComponent(positionComponent), m_agentComponent(agentComponent), m_gameMap(gameMap)
{
    generateBehaviorTree();
}

void AIComponent::update()
{
    m_agentComponent->data().health -= 0.2f / 60.0f;
    m_agentComponent->data().hunger += 0.6f / 60.0f;

    if(m_currentAction == nullptr)
    {
        m_treeRoot->execute();
    }
    else
    {
        m_currentAction->tick();
    }
}

void AIComponent::generateBehaviorTree()
{
    m_treeRoot = new BTRoot;
    auto topSelector = new BTSelector(m_treeRoot);
    m_treeRoot->setChild(topSelector);


    auto restingCondition = new BTCondition(m_agentComponent, [this](){return this->m_agentComponent->data().health < 20;}, topSelector);
    topSelector->addChild(restingCondition);
    restingCondition->setChild(createRestingTree(restingCondition));

    auto eatingCondition = new BTCondition(m_agentComponent, [this](){return this->m_agentComponent->data().hunger > 70;}, topSelector);
    topSelector->addChild(eatingCondition);
    eatingCondition->setChild(createEatingTree(eatingCondition));

    auto woodcuttingCondition = new BTCondition(m_agentComponent, [this](){return QRandomGenerator::global()->generateDouble() * 15.0 > this->m_agentComponent->data().laziness;}, topSelector);
    topSelector->addChild(woodcuttingCondition);
    woodcuttingCondition->setChild(createWoodCuttingTree(woodcuttingCondition));

    topSelector->addChild(createLazyTree(topSelector));
}

BTNode *AIComponent::createWoodCuttingTree(BTNode *parent)
{
    BTSequence* root = new BTSequence(parent);
    root->addChild(new BTSeekTreeAction(m_agentComponent, m_positionComponent, m_gameMap, &m_currentAction, root));
    root->addChild(new BTActionIdle(4.0f / m_agentComponent->data().speed, &m_currentAction, root));
    root->addChild(new BTSetData([this](){return this->m_agentComponent->data().harvestedWood += 1.0f;}, root));

    return root;
}

BTNode *AIComponent::createRestingTree(BTNode *parent)
{
    BTSequence* root = new BTSequence(parent);
    root->addChild(new BTRestingAction(m_agentComponent, m_positionComponent, m_gameMap, &m_currentAction, root));
    root->addChild(new BTSetData([this](){this->m_renderComponent->setVisibility(false);}, root));
    root->addChild(new BTActionIdle(10.0f, &m_currentAction, root));
    root->addChild(new BTSetData([this](){this->m_renderComponent->setVisibility(true);}, root));
    root->addChild(new BTSetData([this](){this->m_agentComponent->data().health = 100;}, root));

    return root;
}

BTNode *AIComponent::createEatingTree(BTNode *parent)
{
    BTSequence* root = new BTSequence(parent);
    root->addChild(new BTRestingAction(m_agentComponent, m_positionComponent, m_gameMap, &m_currentAction, root));
    root->addChild(new BTSetData([this](){this->m_renderComponent->setVisibility(false);}, root));
    root->addChild(new BTActionIdle(2.0f, &m_currentAction, root));
    root->addChild(new BTSetData([this](){this->m_renderComponent->setVisibility(true);}, root));
    root->addChild(new BTSetData([this](){return this->m_agentComponent->data().hunger = 0;}, root));

    return root;
}

BTNode *AIComponent::createLazyTree(BTNode *parent)
{
    BTSequence* root = new BTSequence(parent);

    root->addChild(new BTWalkRandom(m_agentComponent, m_positionComponent, m_gameMap, &m_currentAction, root));
    root->addChild(new BTActionIdle(2.0f * (0.5 + QRandomGenerator::global()->generateDouble()), &m_currentAction, root));

    return root;
}
