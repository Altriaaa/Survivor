#ifndef MAPVIEW_H
#define MAPVIEW_H
#include "maptile.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QtGui>

class MapView : public QGraphicsView
{
public:
    MapView();
    MapView(QWidget *parent);
    void init(QPixmap pixSquare = QPixmap(":/map/square.png"), QPixmap pixObstacle = QPixmap(":/map/obstacle.png"), int rowCount = 10, int colCount = 10);
private:
    int rowCount_;
    int colCount_;
    QVector<MapTile*> AllObs;
};

#endif // MAPVIEW_H
