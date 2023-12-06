#include "bullet.h"

Bullet::Bullet()
{
    ;
}

Bullet::Bullet(QPixmap pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
    ;
}

void Bullet::line_fly(int direc, int speed)
{
    QPointF position = this->scenePos();
    qreal x = position.x();
    qreal y = position.y();

    switch (direc) {
    case 1:
        y -= speed;
        break;
    case 2:
        x -= speed;
        break;
    case 3:
        y += speed;
        break;
    case 4:
        x += speed;
        break;
    default:
        return;
    }
    setPos(x, y);
}
