#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QtGui>

class Bullet : public QGraphicsPixmapItem
{
    friend class Character;
    friend class Magician;
    friend class Monster;
    friend class EliteMonster;
public:
    Bullet();
    Bullet(QPixmap pixmap, QGraphicsItem *parent = nullptr);
    void line_fly(int direc, int speed);
private:
    int direc = 0;
    int range = 0;
};

#endif // BULLET_H
