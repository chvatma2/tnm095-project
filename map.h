#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QPoint>
#include <QHash>
#include <QOpenGLTexture>

#include "gameobject.h"

#include <QOpenGLShaderProgram>


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

private:
    void loadMapFromFile();
    void loadTextures();
    void createTiles();

    QVector<QVector<TileType>> m_terrain;
    QHash<QPoint, GameObject*> m_tiles;
    QHash<QPoint, GameObject*> m_resources;
    QHash<QPoint, GameObject*> m_buildings;
    QMap<QString, TileType> m_tileMapping{{"G", TileType::GRASS}};
    QMap<TileType, QImage*> m_terrainImages;
};

#endif // MAP_H
