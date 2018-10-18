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
    void findShortestPath(int dist, int* outBuffer, const int outBufferSize);

private:
    struct node
    {
        int index;
        int fCost;
        int hCost;
        int parent;
    };

    void loadMapFromFile();
    void loadTextures();
    void createTiles();
    void investigate(node n);
    int getDistance(int x, int y) const;

    QVector<QVector<TileType>> m_terrain;
    QHash<QPoint, GameObject*> m_tiles;
    QHash<QPoint, GameObject*> m_resources;
    QHash<QPoint, GameObject*> m_buildings;
    QMap<QString, TileType> m_tileMapping{{"G", TileType::GRASS}};
    QMap<TileType, QImage*> m_terrainImages;

    //A*
    std::vector<int> hCosts;
    std::vector<int> parents;
    std::priority_queue<node> prioQueue;
    int goalIndex, startIndex;
    int goalX, goalY;
    bool targetFound = false;
    int* pOutBuffer;
    int nOutBufferSize;

};

#endif // MAP_H
