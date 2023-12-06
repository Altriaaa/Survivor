#ifndef CHARACTER_H
#define CHARACTER_H

#include "maptile.h"
#include "bullet.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QtGui>
#include <QPainter>
#include <QGraphicsRotation>

class Character : public QGraphicsPixmapItem
{
    friend class MapView;
    friend class Game;
    friend class MainWindow;
public:
    //构造函数
    Character();
    Character(QPixmap pixmap, QGraphicsItem *parent = nullptr);
    //处理键盘事件
    void keyPressEvent(QKeyEvent *event);
    virtual void attack();
    virtual void moveBullets();
protected:
    double limHealth;
    double curHealth;
    int damage;
    int speed;
    int atk_f;
    int atk_r;
    int atk_s;
    int exp;
    int lv;
    bool moveable;
    QVector<Bullet*> charac_bullets;
    QGraphicsRectItem* curHealthBar = nullptr;
};

class Magician : public Character
{
    friend class MapView;
    friend class Game;
    friend class MainWindow;
private:
    int direc;
public:
    Magician(QPixmap pixmap, Character *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void attack();
    void moveBullets();
};


#endif // CHARACTER_H
