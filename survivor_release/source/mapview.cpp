#include "mapview.h"

MapView::MapView()
{
    ;
}

MapView::MapView(QWidget *parent)
    : QGraphicsView(parent)
{
    ;
}

void MapView::init(QPixmap pixSquare, QPixmap pixObstacle, int rowCount, int colCount)
{
    rowCount_ = (rowCount);
    colCount_ = (colCount);
    setScene(new QGraphicsScene(this));
    scene()->setSceneRect(0, 0, colCount_ * pixSquare.width(), rowCount_ * pixSquare.height());

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    for (int row = 0; row < rowCount_; ++row)
    {
        for (int col = 0; col < colCount_; ++col)
        {
            auto tile = new MapTile(pixSquare);
            if(qrand()%6 == 0 && !(row == 0) && !(col == 0))
            {
                tile = new MapTile(pixObstacle);
                tile->is_obs = true;
                AllObs.push_back(tile);
            }
            tile->setPos(col * pixSquare.width(), row * pixSquare.height());
            scene()->addItem(tile);
        }
    }
}
