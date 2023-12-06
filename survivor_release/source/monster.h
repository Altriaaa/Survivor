#ifndef MONSTER_H
#define MONSTER_H

#include "maptile.h"
#include "bullet.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QtGui>
#include <QRandomGenerator>

class Monster : public QGraphicsPixmapItem
{
    friend class Game;
public:
    //构造函数
    Monster();
    Monster(QPixmap pixmap, int wave = 1, QGraphicsItem *parent = nullptr);
    //移动函数
    virtual void move(qreal dx, qreal dy);

protected:
    double limHealth;
    double curHealth;
    int damage;
    int speed;
    QGraphicsRectItem* curHealthBar = nullptr;
};

class EliteMonster : public Monster
{
    friend class Game;
private:
    int direc;
    QVector<Bullet*> mons_bullets;
public:
    EliteMonster(QPixmap pixmap, int wave = 1, Monster *parent = nullptr);

    void move(qreal dx, qreal dy);
    void reverse();
    void attack();
    void moveBullets();
    void clearBullets();
};

#endif // MONSTER_H
