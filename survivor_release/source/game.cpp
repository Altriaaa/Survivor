#include "game.h"

Game::Game(MapView* view_, QObject *parent) : QObject(parent)
{
    view = view_;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
}

void Game::init()
{
    //load();
    view->scene()->addItem(character);
    view->scene()->addItem(character->curHealthBar);

    //主刷新定时器（生命更新、数值更新）
    timer = new QTimer(this);
    timer->setInterval(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(HpChange()));
    connect(timer, SIGNAL(timeout()), this, SLOT(AtChange()));
    timer->start();

    //游戏剩余时间定时器
    wave = 1;
    timeleft = 60;
    timer_left = new QTimer(this);
    timer_left->setInterval(1000);
    connect(timer_left, SIGNAL(timeout()), this, SLOT(wave_end()));
    timer_left->start();

    //角色攻击定时器
    timer1 = new QTimer(this);
    timer1->setInterval(character->atk_f);
    connect(timer1, SIGNAL(timeout()), this, SLOT(characAttack()));
    timer1->start();

    //怪物攻击定时器
    timer5 = new QTimer(this);
    timer5->setInterval(2500);
    connect(timer5, SIGNAL(timeout()), this, SLOT(monsAttack()));
    timer5->start();

    //刷怪定时器
    timer2 = new QTimer(this);
    timer2->setInterval(5000 - 250*wave);
    connect(timer2, SIGNAL(timeout()), this, SLOT(addMonster()));
    timer2->start();

    //子弹移动,怪物移动定时器
    timer3 = new QTimer(this);
    timer3->setInterval(25);
    connect(timer3, SIGNAL(timeout()), this, SLOT(moveBullets()));
    connect(timer3, SIGNAL(timeout()), this, SLOT(moveMonster()));
    timer3->start();

    //清除怪物残骸定时器
    timer4 = new QTimer(this);
    timer4->setInterval(2000);
    connect(timer4, SIGNAL(timeout()), this, SLOT(remove_dead_cat()));
    timer4->start();

//    //清除金币定时器
//    timer6 = new QTimer(this);
//    timer6->setInterval(10000);
//    connect(timer6, SIGNAL(timeout()), this, SLOT(remove_coins()));
//    timer6->start();
}

void Game::remove_dead_cat()
{
    for(auto dc = dead_cats.begin(); dc != dead_cats.end(); ++dc)
    {
        view->scene()->removeItem(*dc);
        delete(*dc);
    }
    dead_cats.clear();
}

//void Game::remove_coins()
//{
//    for(auto c = coins.begin(); c != coins.end(); ++c)
//    {
//        if((*c) != nullptr)
//        {
//            view->scene()->removeItem(*c);
//            delete(*c);
//        }
//    }
//    coins.clear();
//}

void Game::pause()
{
    timer->stop();
    timer1->stop();
    timer2->stop();
    timer3->stop();
    timer4->stop();
    timer5->stop();
    //timer6->stop();
    timer_left->stop();
    character->moveable = false;
}

void Game::enhance()
{
    pause();
    emit sigEnhance();
}

void Game::resume()
{
    timer->start();
    timer1->start();
    timer2->start();
    timer3->start();
    timer4->start();
    timer5->start();
    //timer6->start();
    timer_left->start();
    character->moveable = true;
}

void Game::HpChange()
{

    //玩家受到伤害
    foreach(Monster* m, monsters)
    {
        if(m->collidesWithItem(character, Qt::IntersectsItemShape))
        {
            character->curHealth -= m->damage;
            character->curHealthBar->setRect(0, 0, ((character->curHealth)/(character->limHealth))*70, 3);
        }
    }

//    foreach(auto c, coins)
//    {
//        if(c != nullptr)
//        {
//            if(c->collidesWithItem(character, Qt::IntersectsItemShape))
//            {
//                money += money_k;
//            }

//            //view->scene()->removeItem(c);
//            //delete c;
//        }a
//    }

    auto it_c = coins.begin();
    while(it_c != coins.end())
    {
        if((*it_c)->collidesWithItem(character, Qt::IntersectsItemShape))
        {
            money += money_k*0.1;
            view->scene()->removeItem(*it_c);
            delete(*it_c);
            it_c = coins.erase(it_c);
        }
        else
            ++it_c;
    }

    foreach(auto m, monsters)
    {
        if(dynamic_cast<EliteMonster*>(m))
        {
            foreach(auto b, ((EliteMonster*)m)->mons_bullets)
            {
                if(b->collidesWithItem(character, Qt::IntersectsItemShape))
                {
                    character->curHealth -= m->damage;
                    character->curHealthBar->setRect(0, 0, ((character->curHealth)/(character->limHealth))*70, 3);
                }
            }
        }
    }
    character->curHealthBar->setRect(0, 0, ((character->curHealth)/(character->limHealth))*70, 3); //再次更新血条

    //怪物受到伤害
    foreach(auto b, character->charac_bullets)
    {
        foreach(auto m, b->collidingItems(Qt::IntersectsItemShape))
        {
            if(dynamic_cast<Monster*>(m))
            {

                ((Monster*)m)->curHealth -= character->damage;
                ((Monster*)m)->curHealthBar->setRect(0, 0, (((Monster*)m)->curHealth/((Monster*)m)->limHealth)*70, 3);
            }
        }
    }
    auto it = monsters.begin();
    while(it != monsters.end())
    {
        if((*it)->curHealth <= 0)
        {
            QPointF pos = (*it)->scenePos();
            if(dynamic_cast<EliteMonster*>(*it))
                ((EliteMonster*)(*it))->clearBullets();
            view->scene()->removeItem(*it);
            view->scene()->removeItem((*it)->curHealthBar);
            delete (*it);
            it = monsters.erase(it);
            character->exp += 5;

            QPixmap pixDeadCat(":/map/deadbomb.png");
            auto dc = new Monster(QPixmap(pixDeadCat));
            dc->setPos(pos);
            dead_cats.push_back(dc);
            view->scene()->addItem(dc);

            int rnd = QRandomGenerator::global()->bounded(0,2);
            if(rnd == 0)
            {
                QPixmap pixCoin(":/map/coin.png");
                auto c = new Monster(QPixmap(pixCoin));
                c->setPos(pos);
                coins.push_back(c);
                view->scene()->addItem(c);
            }
        }
        else
            ++it;
    }
    //发送Hp变化信号、Hp处理
    emit sigHealth(character->curHealth);
    if (character->curHealth <= 0)
    {
        if(lives > 0)
        {
            lives--;
            character->curHealth = character->limHealth;
        }
        else
        {
            QMessageBox::information(nullptr, "Game Over", "You lost!");
            qApp->exit();
        }
    }
}

void Game::AtChange()
{
    if(character->exp >= 50)
    {
        character->lv += 1;
        character->exp = 0;
        enhance();
    }
    emit sigAt(character->exp, character->lv, character->damage, character->speed, money);
}

void Game::addMonster()
{
    QPixmap pixMonster(":/map/monster.png");
    QPixmap pixMonster2(":/map/catbomb.png");
    QPixmap pixMonster3(":/map/monster2.png");
    int m_startCol = qrand() % 10;
    int m_startRow = qrand() % 10;
    int rnd = QRandomGenerator::global()->bounded(0,2);
    auto mons1 = new Monster(pixMonster, wave);
    Monster* mons2;
    if(rnd < 1)
        mons2 = new Monster(pixMonster2, wave);
    else
        mons2 = new EliteMonster(pixMonster3, wave);
    mons1->setPos(m_startRow*70 , 630);
    mons2->setPos(630, m_startCol*70);
    monsters.push_back(mons1);
    monsters.push_back(mons2);
    view->scene()->addItem(mons1);
    view->scene()->addItem(mons1->curHealthBar);
    view->scene()->addItem(mons2);
    view->scene()->addItem(mons2->curHealthBar);
}

void Game::moveMonster()
{
    QPointF position = character->scenePos();
    qreal x = position.x();
    qreal y = position.y();
    foreach(Monster* m, monsters)
    {
        m->move(x, y);
    }
}

void Game::moveBullets()
{
    character->moveBullets();
    foreach(auto m, monsters)
    {
        if(dynamic_cast<EliteMonster*>(m))
        {
            ((EliteMonster*)m)->moveBullets();
        }
    }
}

void Game::monsAttack()
{
    foreach(auto m, monsters)
    {
        if(dynamic_cast<EliteMonster*>(m))
        {
            ((EliteMonster*)m)->attack();
        }
    }
}

void Game::characAttack() { character->attack(); }

void Game::helpSave()
{
    emit sigSave();
}

void Game::wave_end()
{
    timeleft -= 1;
    emit sigTimeLeft(timeleft);
    if(timeleft == 0)
    {
        money += money_k;
        //QMessageBox::information(nullptr, "Game Over", "You Win!");
        pause();
        condialog dlg;
        QObject::connect(&dlg, SIGNAL(sigSave()), this, SLOT(helpSave()));
        if (dlg.exec() == QDialog::Accepted)
        {
            wave++;
            emit sigWave(wave);
            timeleft = 60+wave*3;
            auto it = monsters.begin();
            while(it != monsters.end())
            {
                if(dynamic_cast<EliteMonster*>(*it))
                    ((EliteMonster*)(*it))->clearBullets();
                view->scene()->removeItem(*it);
                view->scene()->removeItem((*it)->curHealthBar);
                delete(*it);
                it = monsters.erase(it);
            }
            resume();
        }
    }
}
