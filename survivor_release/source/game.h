#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "maptile.h"
#include "mapview.h"
#include "monster.h"
#include "bullet.h"
#include "condialog.h"

#include <fstream>
#include <QObject>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QtGui>
#include <QPainter>
#include <QMessageBox>

class Game : public QObject
{
    Q_OBJECT
    friend class MainWindow;
public:
    explicit Game(MapView* view_, QObject *parent = nullptr);
    void init();
    void enhance();
    void pause();
    void resume();

private:
    MapView* view;
    Character* character = nullptr;
    QVector<Monster*> monsters;
    QVector<Monster*> dead_cats;
    QVector<Monster*> coins;
    int timeleft;
    int wave;
    int money = 0;
    int money_k = 200;
    int lives = 1;
    QTimer* timer = nullptr;
    QTimer* timer_left = nullptr;
    QTimer* timer1 = nullptr;
    QTimer* timer2 = nullptr;
    QTimer* timer3 = nullptr;
    QTimer* timer4 = nullptr;
    QTimer* timer5 = nullptr;
    QTimer* timer6 = nullptr;

signals:
    void sigHealth(int);
    void sigAt(int e, int l, int att, int spd, int money);
    void sigTimeLeft(int t);
    void sigEnhance();
    void sigWave(int w);
    void sigSave();

private slots:
    void HpChange();
    void AtChange();
    void addMonster();
    void moveMonster();
    void monsAttack();
    void characAttack();
    void moveBullets();
    void wave_end();
    void remove_dead_cat();
    //void remove_coins();
    void helpSave();
};

#endif // GAME_H
