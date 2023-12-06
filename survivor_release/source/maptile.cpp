#include "maptile.h"

MapTile::MapTile()
{
    ;
}

MapTile::MapTile(QPixmap pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent) , is_obs(false) {}
