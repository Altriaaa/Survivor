#ifndef MAPTILE_H
#define MAPTILE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QtGui>

class MapTile : public QGraphicsPixmapItem
{
    friend class MapView;
    friend class Character;
    friend class Magician;
    friend class Monster;
    friend class EliteMonster;
public:
    MapTile();
    MapTile(QPixmap pixmap, QGraphicsItem *parent = nullptr);
private:
    bool is_obs;
};

#endif // MAPTILE_H
