#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "character.h"
#include "maptile.h"
#include "mapview.h"
#include "game.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    MapView* getView();
    void setGame(Game* game_);
    void setButtonUnable();

private:
    Ui::MainWindow *ui;
    Game* game;
    QVector<int> allAt;

private slots:
    void sloHealth(int h);
    void sloAt(int e, int l, int att, int spd, int money);
    void sloTimeLeft(int t);
    void sloWave(int w);
    void sloEnhance();
    void slo_charac_order(int n);
    void sloAllAt(QVector<int>);
    void sloSave();

    void on_h_enhance_clicked();
    void on_a_enhance_clicked();
    void on_s_enhance_clicked();
    void on_af_enhance_clicked();
    void on_ar_enhance_clicked();
    void on_as_enhance_clicked();
};
#endif // MAINWINDOW_H
