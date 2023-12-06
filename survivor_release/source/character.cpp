#include "character.h"
#include <QMessageBox>

Character::Character()
{
    ;
}

Character::Character(QPixmap pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
    limHealth = 350;
    curHealth = limHealth;
    damage = 20;
    speed = 7;
    atk_f = 1000;
    atk_r = 360;
    atk_s = 9;
    exp = 0;
    lv = 0;
    moveable = true;
    setPos(0, 0);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    curHealthBar = new QGraphicsRectItem;
    curHealthBar->setRect(this->x()-10, this->y()-2, 70, 3);
    curHealthBar->setBrush(Qt::red);
}

Magician::Magician(QPixmap pixmap, Character *parent)
    :Character(pixmap, parent)
{
    limHealth = 280;
    curHealth = limHealth;
    damage = 30;
    speed = 7;
    atk_f = 800;
    atk_r = 400;
    atk_s = 4;
    moveable = true;
    exp = 0;
    lv = 0;
    direc = 4;
    setPos(0, 0);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    curHealthBar = new QGraphicsRectItem;
    curHealthBar->setRect(this->x()-10, this->y()-2, 70, 3);
    curHealthBar->setBrush(Qt::red);
}

void Character::keyPressEvent(QKeyEvent *e)
{
    if(moveable == false)
        return ;
    QPointF position = this->scenePos();
    qreal x = position.x();
    qreal y = position.y();

    switch (e->key()) {
    case Qt::Key_W:
        y -= speed;
        break;
    case Qt::Key_A:
        x -= speed;
        break;
    case Qt::Key_S:
        y += speed;
        break;
    case Qt::Key_D:
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
        curHealthBar->setPos(x-10, y-2);
        foreach(auto m, collidingItems(Qt::IntersectsItemShape))
        {
            if(dynamic_cast<MapTile*>(m))
            {
                if( ((MapTile*) m)->is_obs == true)
                    setPos(position);
            }
        }
    }
}

void Magician::keyPressEvent(QKeyEvent *e)
{
    if(moveable == false)
        return ;
    QPointF position = this->scenePos();
    qreal x = position.x();
    qreal y = position.y();

    switch (e->key()) {
    case Qt::Key_W:
        y -= speed;
        direc = 1;
        break;
    case Qt::Key_A:
        x -= speed;
        direc = 2;
        break;
    case Qt::Key_S:
        y += speed;
        direc = 3;
        break;
    case Qt::Key_D:
        x += speed;
        direc = 4;
        break;
    default:
        return;
    }

    if (y >= 0 && y <= 630 && x >= 0 && x <= 630)
    {
        // Move the character to the next position
        setPos(x, y);
        curHealthBar->setPos(x-10, y-2);
        foreach(auto m, collidingItems(Qt::IntersectsItemShape))
        {
            if(dynamic_cast<MapTile*>(m))
            {
                if( ((MapTile*) m)->is_obs == true)
                    setPos(position);
            }
        }
    }
}

void Character::attack()
{
    QPointF position = scenePos();
    qreal x = position.x();
    qreal y = position.y();

    QPixmap pixBullet(":/map/normal_bullet.png");
    /*if(charac_bullets.size() != 0)
    {
        foreach(auto b, charac_bullets)
            delete b;
    }
    charac_bullets.clear();*/
    for(int i = 0; i < 4; i++)
    {
        auto b = new Bullet(pixBullet);
        b->range = atk_r;
        b->direc = i+1;
        b->setPos(x, y);
        charac_bullets.push_back(b);
        scene()->addItem(b);
    }
}

void Magician::attack()
{
    QPointF position = scenePos();
    qreal x = position.x();
    qreal y = position.y();

    QPixmap pixBullet(":/map/magicball.png");
    auto b = new Bullet(pixBullet);
    b->direc = direc;
    b->range = atk_r;
    b->setPos(x, y);
    charac_bullets.push_back(b);
    scene()->addItem(b);
}

void Character::moveBullets()
{
    if(charac_bullets.size() != 0)
    {
        for(int i = 0; i < charac_bullets.size(); i++)
        {
            charac_bullets[i]->line_fly(charac_bullets[i]->direc, atk_s);
            charac_bullets[i]->range -= atk_s;
        }
        auto it = charac_bullets.begin();
        while(it != charac_bullets.end())
        {
            if((*it)->range <= 0)
            {
                scene()->removeItem(*it);
                delete(*it);
                it = charac_bullets.erase(it);
            }
            else
                ++it;
        }
    }
}

void Magician::moveBullets()
{
    if(charac_bullets.size() != 0)
    {
        for(int i = 0; i < charac_bullets.size(); i++)
        {
            charac_bullets[i]->line_fly(charac_bullets[i]->direc, atk_s);
            charac_bullets[i]->range -= atk_s;
        }
        auto it = charac_bullets.begin();
        while(it != charac_bullets.end())
        {
            if((*it)->range <= 0)
            {
                scene()->removeItem(*it);
                delete(*it);
                it = charac_bullets.erase(it);
            }
            else
                ++it;
        }
    }
}



