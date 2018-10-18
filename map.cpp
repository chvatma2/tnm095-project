#include "map.h"

#include <QFile>
#include <QDebug>
#include <QMap>

#include "spritecomponent.h"
#include "positioncomponent.h"
#include "rendercomponent.h"

Map::Map(int width, int height)
{
    m_terrain.resize(width);
    for(int i = 0; i < m_terrain.size(); ++i)
        m_terrain[i].resize(height);

    loadMapFromFile();
    loadTextures();
    createTiles();
}

bool Map::addResource(const QPoint &position, GameObject *resourceObject)
{
    if(!isPositionEmpty(position))
        return false;
    m_resources.insert(position, resourceObject);
    return true;
}

bool Map::addBuilding(const QPoint &position, GameObject *building)
{

    if(!isPositionEmpty(position))
        return false;
    m_resources.insert(position, building);
    return true;
}

bool Map::isPositionEmpty(const QPoint &position) const
{
    if(position.x() > m_terrain.size() || position.x() < 0)
        return false;
    if(position.y() > m_terrain[0].size() || position.y() < 0)
        return false;
    if(m_resources.contains(position) || m_buildings.contains(position))
        return false;
    return true;
}

int Map::height() const
{
    return m_terrain[0].size();
}

int Map::width() const
{
    return m_terrain.size();
}

void Map::renderTiles(QOpenGLShaderProgram *program)
{
    for(auto tile : m_tiles)
    {
        tile->render(program);
    }
}

void Map::init()
{
    for(auto tile : m_tiles)
    {
        tile->init();
    }
}

QList<QPoint> Map::pathToClosestWood(QPointF from)
{
    std::size_t buffer[500];

}

QList<QPoint> Map::pathToClosestHouse(QPointF from)
{
    
}

QList<QPoint> Map::pathToClosestDiner(QPointF from)
{
    
}

float Map::traversalCostOfTile(int x, int y)
{
    float cost = m_tileTypeTraversalCost[m_terrain[x][y]];
    if(m_buildings.contains(QPoint(x, y)))
        return -1.0f;
    if(m_resources.contains(QPoint(x, y)))
        cost *= 1.5f;

    return cost;
}

int Map::findPath(int startX, int startY, int goalX, int goalY, std::size_t* pOutBuffer, float* cost)
{
    std::size_t mapwidth = static_cast<std::size_t>(width());
    std::size_t mapheight = static_cast<std::size_t>(height());
    hCosts.assign(mapwidth*mapheight, -1);
    parents.assign(mapwidth*mapheight, static_cast<std::size_t>(-1));

    std::priority_queue<node> p;
    prioQueue = p;

    goalIndex = getIndex(goalX, goalY);
    this->goalX = goalX;
    this->goalY = goalY;

    node startingNode;
    startIndex = getIndex(startX, startY);
    startingNode.x = startX;
    startingNode.y = startY;
    startingNode.index = startIndex;
    startingNode.fCost = 0;
    startingNode.hCost = 0;
    startingNode.parent = static_cast<std::size_t>(-1);

    prioQueue.push(startingNode);
    targetFound = false;

    this->pOutBuffer = pOutBuffer;

    while (!prioQueue.empty() && !targetFound)
        {
            node n = prioQueue.top();
            prioQueue.pop();
            investigate(n);
        }

        if (hCosts[goalIndex] != -1)
        {
            findShortestPath(hCosts[goalIndex], pOutBuffer);
            *cost = goal.fCost;
            return hCosts[goalIndex];
        }
        else
        {
            return -1;
        }
}

QPoint Map::pointFromIndex(int index)
{
    int x = index % width();
    int y = static_cast<int>(std::floor(index / width()));
    return QPoint(x, y);
}

void Map::findShortestPath(int dist, std::size_t *outBuffer)
{
    int i = 1;
    std::size_t index = goalIndex;

    while (index != startIndex)
    {
       *(outBuffer + dist - i) = index;
       index = parents[index];
       ++i;
    }
}

void Map::loadMapFromFile()
{
    //Terrain
    QFile terrainFile("ai/terrain.csv");
    if (!terrainFile.open(QIODevice::ReadOnly))
    {
            qDebug() << terrainFile.errorString();
            return;
    }
    int row = 0;
    while (!terrainFile.atEnd())
    {
        QString line = terrainFile.readLine();
        line.remove('\n');
        line.remove('\r');
        QStringList wordList = line.split(',');
        int column = 0;
        for(auto word : wordList)
        {
            auto mapping = m_tileMapping.find(word);
            if(mapping == m_tileMapping.end())
            {
                qDebug() << "Unknown tile name: " << word;
                return;
            }
            m_terrain[row][column] = mapping.value();
            ++column;
        }
        ++row;
    }
}

void Map::loadTextures()
{
    m_terrainImages[TileType::GRASS] = new QImage("textures/Grass.png");
}

void Map::createTiles()
{
    for(int x = 0; x < m_terrain.size(); ++x)
    {
        for(int y = 0; y < m_terrain[0].size(); ++y)
        {
            GameObject* tile = new GameObject;
            tile->setComponent(ComponentType::PositionComponent, new PositionComponent(QPointF(x, y)));
            tile->setComponent(ComponentType::SpriteComponent, new SpriteComponent(50, 50, m_terrainImages[m_terrain[x][y]]));
            tile->setComponent(ComponentType::RenderComponent, new RenderComponent(dynamic_cast<SpriteComponent*>(tile->component(ComponentType::SpriteComponent)),
                                                                                   dynamic_cast<PositionComponent*>(tile->component(ComponentType::PositionComponent))));
            m_tiles.insert(QPoint(x,y), tile);
        }
    }
}

QList<QPoint> Map::rawBufferToPath(std::size_t *buffer, int length)
{
    QList<QPoint> result;
    for(int i = 0; i < length; ++i)
    {
        result.push_back( pointFromIndex(buffer[i]));
    }

    return result;
}

void Map::investigate(node n)
{
    // check if the node is the target
       if (n.index == goalIndex)
       {
           goal = n;
           targetFound = true;
           hCosts[n.index] = n.hCost;
           parents[n.index] = n.parent;
           return;
       }

       // check wether the node was already visited
       if (hCosts[n.index] != -1)
       {
           return;
       }

       // if this is the shortest path from the source to this node:
       int x = n.x;
       int y = n.y;

       // set parent and hCost
       hCosts[n.index] = n.hCost;
       parents[n.index] = n.parent;

       // visit node on the left
       if (0 <= x - 1)
       {
           visitNode(x - 1, y, n);
       }
       // visit node on the right
       if (x + 1 < width())
       {
           visitNode(x + 1, y, n);
       }
       // visit node below
       if (0 <= y - 1)
       {
           visitNode(x, y - 1, n);
       }
       //visit node above
       if (y + 1 < height())
       {
           visitNode(x, y + 1, n);
       }
}

int Map::getDistance(int x, int y) const
{
    return std::max(x - goalX, goalX - x) + std::max(y - goalY, goalY - y); //Manhattan distance

    /*
    int dx = abs(node.x - goal.x)
    int dy = abs(node.y - goal.y)
    return

    */
}

std::size_t Map::getIndex(int x, int y) const
{
    return static_cast<std::size_t>(y * width() + x);
}

void Map::visitNode(int x, int y, node n)
{
    std::size_t newId = getIndex(x, y);
    if (hCosts[newId] == -1 && traversalCostOfTile(x, y) > 0)
    {
        node newNode;
        newNode.x = x;
        newNode.y = y;
        newNode.index = newId;
        newNode.parent = n.index;
        newNode.hCost = n.hCost + 1;
        newNode.fCost = (n.hCost + 1) + getDistance(x, y) + traversalCostOfTile(x, y); //TODO: change traversal cost to int??
        prioQueue.push(newNode);
    }
}
