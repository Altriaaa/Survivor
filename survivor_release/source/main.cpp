#include "mainwindow.h"
#include "character.h"
#include "maptile.h"
#include "mapview.h"
#include "game.h"
#include "predialog.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //绑定Game与MainWindow
    MainWindow w;
    Game game(w.getView());
    w.setGame(&game);

    //登录对话框
    PreDialog dlg;
    QObject::connect(&dlg, SIGNAL(sig_charac_order(int)), &w, SLOT(slo_charac_order(int)));
    QObject::connect(&dlg, SIGNAL(sigAllAt(QVector<int>)), &w, SLOT(sloAllAt(QVector<int>)));

    if (dlg.exec() == QDialog::Accepted)
    {
        game.init();
        QObject::connect(&game, SIGNAL(sigHealth(int)), &w, SLOT(sloHealth(int)));
        QObject::connect(&game, SIGNAL(sigAt(int, int, int, int, int)), &w, SLOT(sloAt(int, int, int, int, int)));
        QObject::connect(&game, SIGNAL(sigTimeLeft(int)), &w, SLOT(sloTimeLeft(int)));
        QObject::connect(&game, SIGNAL(sigWave(int)), &w, SLOT(sloWave(int)));
        QObject::connect(&game, SIGNAL(sigEnhance()), &w, SLOT(sloEnhance()));
        QObject::connect(&game, SIGNAL(sigSave()), &w, SLOT(sloSave()));
        w.show();
        return app.exec();
    }
    else return 0;
}
