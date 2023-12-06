#include "monster.h"

Monster::Monster()
{
    ;
}

Monster::Monster(QPixmap pixmap, int wave, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
    limHealth = 94 + wave*6;
    curHealth = limHealth;
    damage = 5 + wave*2;
    speed = 1;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    curHealthBar = new QGraphicsRectItem;
    curHealthBar->setRect(this->x(), this->y()-2, 70, 3);
    curHealthBar->setBrush(Qt::red);
}

EliteMonster::EliteMonster(QPixmap pixmap, int wave, Monster *parent)
    :Monster(pixmap, wave, parent)
{
    limHealth = 114 + wave*6;
    curHealth = limHealth;
    damage = 7 + wave*3;
    speed = 1;
    direc = 2;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    curHealthBar = new QGraphicsRectItem;
    curHealthBar->setRect(this->x(), this->y()-2, 70, 3);
    curHealthBar->setBrush(Qt::red);
}


void Monster::move(qreal dx, qreal dy)
{
    QPointF position = this->scenePos();
    qreal x = position.x();
    qreal y = position.y();

    int direction = qrand()%5;

    if(dx >= x && dy >= y)
    {
        if(dx == x)
            direction = 3;
        else if(dy == y)
            direction = 4;
        else
            direction = QRandomGenerator::global()->bounded(3,5);
    }
    if(dx >= x && dy <= y)
    {
        if(dx == x)
            direction = 1;
        else if(dy == y)
            direction = 4;
        else
        {
            int rnd = QRandomGenerator::global()->bounded(0,2);
            if(rnd == 0)
                direction = 1;
            else
                direction = 4;
        }
    }
    if(dx <= x && dy <= y)
    {
        if(dx == x)
            direction = 1;
        else if(dy == y)
            direction = 2;
        else
        {
            int rnd = QRandomGenerator::global()->bounded(0,2);
            if(rnd == 0)
                direction = 1;
            else
                direction = 2;
        }
    }
    if(dx <= x && dy >= y)
    {
        if(dx == x)
            direction = 3;
        else if(dy == y)
            direction = 2;
        else
        {
            int rnd = QRandomGenerator::global()->bounded(0,2);
            if(rnd == 0)
                direction = 3;
            else
                direction = 2;
        }
    }

    switch (direction) {
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

    // Check if the next position is valid
    if (y >= 0 && y <= 630 && x >= 0 && x <= 630)
    {
        // Move the character to the next position
        setPos(x, y);
        curHealthBar->setPos(x, y-2);
        /*foreach(auto m, collidingItems(Qt::IntersectsItemShape))
        {
            if(dynamic_cast<MapTile*>(m))
            {
                if( ((MapTile*) m)->is_obs == true)
                    setPos(position);
            }
        }*/
    }
}

void EliteMonster::reverse()
{
    switch (direc) {
    case 1:
        direc = 3;
        break;
    case 2:
        direc = 4;
        break;
    case 3:
        direc = 1;
        break;
    case 4:
        direc = 2;
        break;
    default:
        return;
    }
}

void EliteMonster::attack()
{
    QPointF position = scenePos();
    qreal x = position.x();
    qreal y = position.y();

    QPixmap pixBullet(":/map/evilball.png");
    auto b = new Bullet(pixBullet);
    int d = QRandomGenerator::global()->bounded(0,2);
    if(d == 0)
        b->direc = 1;
    else
        b->direc = 3;
    b->range = 350;
    b->setPos(x, y);
    mons_bullets.push_back(b);
    scene()->addItem(b);
}

void EliteMonster::moveBullets()
{
    if(mons_bullets.size() != 0)
    {
        for(int i = 0; i < mons_bullets.size(); i++)
        {
            mons_bullets[i]->line_fly(mons_bullets[i]->direc, 3);
            mons_bullets[i]->range -= 3;
        }
        auto it = mons_bullets.begin();
        while(it != mons_bullets.end())
        {
            if((*it)->range <= 0)
            {
                scene()->removeItem(*it);
                delete(*it);
                it = mons_bullets.erase(it);
            }
            else
                ++it;
        }
    }
}

void EliteMonster::clearBullets()
{
    auto it = mons_bullets.begin();
    while(it != mons_bullets.end())
    {
        scene()->removeItem(*it);
        delete(*it);
        ++it;
    }
    mons_bullets.clear();
}

void EliteMonster::move(qreal dx, qreal dy)
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
    if (y >= 0 && y <= 630 && x >= 0 && x <= 630)
    {
        // Move the character to the next position
        setPos(x, y);
        curHealthBar->setPos(x, y-2);
        /*foreach(auto m, collidingItems(Qt::IntersectsItemShape))
        {
            if(dynamic_cast<MapTile*>(m))
            {
                if( ((MapTile*) m)->is_obs == true)
                {
                    setPos(position);
                    reverse();
                }
            }
        }*/
    }
    else
    {
        reverse();
    }
}
