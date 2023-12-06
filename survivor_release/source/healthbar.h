#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QtGui>

class HealthBar : public QGraphicsRectItem
{
    friend class Game;
private:
    int max_hp;
    int cur_hp;

public:
    HealthBar();
    HealthBar(int max_hp_, QGraphicsItem *parent = nullptr);
};

#endif // HEALTHBAR_H
