#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QPoint>
#include <QHash>
#include <QOpenGLTexture>

#include "gameobject.h"

#include <QOpenGLShaderProgram>

#include <queue>


enum class TileType
{
    GRASS
};

struct node
{
    int x, y;
    std::size_t index;
    float fCost;
    int hCost;
    std::size_t parent;
};

inline bool operator <(const node& x, const node& y)
{
    return x.fCost > y.fCost;
}

inline uint qHash (const QPoint & key)
{
    return qHash (static_cast <qint64> (key.x () ) << 32 | key.y () );
}

class Map
{
public:
    Map(int width, int height);
    bool addResource(const QPoint &position, GameObject* resourceObject);
    bool addBuilding(const QPoint &position, GameObject* building);
    bool isPositionEmpty(const QPoint &position) const;
    int height() const;
    int width() const;
    void renderTiles(QOpenGLShaderProgram *program);
    void init();

    //A*
    int findPath(int startX, int startY, int goalX, int goalY, std::size_t* pOutBuffer); //Returns total distance from start to goal


private:


    void loadMapFromFile();
    void loadTextures();
    void createTiles();

    //A*
    void investigate(node n);
    int getDistance(int x, int y) const;
    std::size_t getIndex(int x, int y) const;
    void visitNode(int x, int y, node n);
    float traversalCostOfTile(int x, int y);
    void findShortestPath(int dist, std::size_t* outBuffer);

    QVector<QVector<TileType>> m_terrain;
    QHash<QPoint, GameObject*> m_tiles;
    QHash<QPoint, GameObject*> m_resources;
    QHash<QPoint, GameObject*> m_buildings;
    QMap<QString, TileType> m_tileMapping{{"G", TileType::GRASS}};
    QMap<TileType, float> m_tileTypeTraversalCost{{TileType::GRASS, 1.0f}};
    QMap<TileType, QImage*> m_terrainImages;

    //A*
    std::vector<int> hCosts;
    std::vector<std::size_t> parents;
    std::priority_queue<node> prioQueue;
    std::size_t goalIndex, startIndex;
    int goalX, goalY;
    bool targetFound = false;
    std::size_t* pOutBuffer;

};

#endif // MAP_H
