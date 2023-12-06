#include "healthbar.h"

HealthBar::HealthBar()
{
    ;
}

HealthBar::HealthBar(int max_hp_, QGraphicsItem *parent):
        QGraphicsRectItem(parent)
{
    max_hp = max_hp_;
    setBrush(Qt::red);
    setRect(0, 0, 70, 2);
}
