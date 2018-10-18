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

float Map::traversalCostOfTile(int x, int y)
{
    float cost = m_tileTypeTraversalCost[m_terrain[x][y]];
    if(m_buildings.contains(QPoint(x, y)))
        return -1.0f;
    if(m_resources.contains(QPoint(x, y)))
        cost *= 1.5f;

    return cost;
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
