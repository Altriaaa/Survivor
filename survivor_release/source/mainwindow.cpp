#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "character.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->myview->init();
    ui->myview->setFixedSize(705, 705);
    allAt.push_back(0);
    allAt.push_back(350);
    allAt.push_back(20);
    allAt.push_back(7);
    allAt.push_back(1000);
    allAt.push_back(360);
    allAt.push_back(9);
    allAt.push_back(280);
    allAt.push_back(30);
    allAt.push_back(7);
    allAt.push_back(800);
    allAt.push_back(400);
    allAt.push_back(4);
    allAt.push_back(200);
    allAt.push_back(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MapView* MainWindow::getView()
{
    return ui->myview;
}

void MainWindow::setGame(Game *game_)
{
    game = game_;
}

void MainWindow::setButtonUnable()
{
    ui->h_enhance->setEnabled(false);
    ui->a_enhance->setEnabled(false);
    ui->s_enhance->setEnabled(false);
    ui->af_enhance->setEnabled(false);
    ui->as_enhance->setEnabled(false);
    ui->ar_enhance->setEnabled(false);
    ui->enhance_label->setText(tr("强化系统（暂无强化）"));
    ui->enhance_label->setStyleSheet("color: black; font: 11pt '华文细黑'; ");
}

void MainWindow::slo_charac_order(int n)
{
    if(n == 1)
    {
        QPixmap pixCharacter(":/map/character1.png");
        if(game->character!= nullptr)
            delete game->character;
        game->character = new Magician(pixCharacter);
        if(allAt.size() > 0)
        {
            game->character->limHealth = allAt[7];
            game->character->curHealth = allAt[7];
            game->character->damage = allAt[8];
            game->character->speed = allAt[9];
            game->character->atk_f = allAt[10];
            game->character->atk_r = allAt[11];
            game->character->atk_s = allAt[12];
        }
    }
    else
    {
        QPixmap pixCharacter(":/map/character0.png");
        if(game->character!= nullptr)
            delete game->character;
        game->character = new Character(pixCharacter);
        if(allAt.size() > 0)
        {
            game->character->limHealth = allAt[1];
            game->character->curHealth = allAt[1];
            game->character->damage = allAt[2];
            game->character->speed = allAt[3];
            game->character->atk_f = allAt[4];
            game->character->atk_r = allAt[5];
            game->character->atk_s = allAt[6];
        }
    }
}

void MainWindow::sloHealth(int h)
{
    ui->health->setText(tr("剩余Hp: %1").arg(h));
}

void MainWindow::sloAt(int e, int l, int att, int spd, int money)
{
    ui->Exp->setText(tr("当前经验: %1").arg(e));
    ui->Lv->setText(tr("当前等级: %1").arg(l));
    ui->damage->setText(tr("攻击力: %1").arg(att));
    ui->speed->setText(tr("速度: %1").arg(spd));
    ui->money->setText(tr("当前金币: %1").arg(money));
}

void MainWindow::sloTimeLeft(int t)
{
    ui->timeleft->setText(tr("剩余时间: %1").arg(t));
}

void MainWindow::sloWave(int w)
{

    //game->money_k = allAt[13];
    ui->wave->setText(tr("当前波次: %1").arg(w));
}

void MainWindow::sloEnhance()
{
    ui->enhance_label->setText(tr("选择一项进行强化"));
    ui->enhance_label->setStyleSheet("color: red; font: 11pt '华文细黑'; ");
    int rnd1 = QRandomGenerator::global()->bounded(0, 6);
    int rnd2 = 0;
    do{
        rnd2 = QRandomGenerator::global()->bounded(0, 6);
    }while(rnd2 == rnd1);
    int rnd3 = 0;
    do{
        rnd3 = QRandomGenerator::global()->bounded(0, 6);
    }while(rnd3 == rnd1 || rnd3 == rnd2);

    QVector<QPushButton*> btn_list;
    btn_list.push_back(ui->h_enhance);
    btn_list.push_back(ui->a_enhance);
    btn_list.push_back(ui->s_enhance);
    btn_list.push_back(ui->af_enhance);
    btn_list.push_back(ui->as_enhance);
    btn_list.push_back(ui->ar_enhance);
    btn_list[rnd1]->setEnabled(true);
    btn_list[rnd2]->setEnabled(true);
    btn_list[rnd3]->setEnabled(true);

//    ui->h_enhance->setEnabled(true);
//    ui->a_enhance->setEnabled(true);
//    ui->s_enhance->setEnabled(true);
//    ui->af_enhance->setEnabled(true);
//    ui->as_enhance->setEnabled(true);
//    ui->ar_enhance->setEnabled(true);

}

void MainWindow::sloAllAt(QVector<int> allAt_)
{
    if(allAt_.size() != 0)
        allAt = allAt_;
    if(allAt.size() != 0)
        game->money = allAt[0];
        game->money_k = allAt[13];
        game->lives = allAt[14];
}

void MainWindow::sloSave()
{
    if(allAt.size() == 0)
        return ;
    // 创建文件对象
    QFile file("./save.txt");

    // 打开文件以写入模式
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // 创建文本流对象，并与文件关联
        QTextStream out(&file);

        // 写入角色数值到文本流
        out << "money=" << game->money << "\n";
        out << "c1_limhealth=" << allAt[1] << "\n";
        out << "c1_damage=" << allAt[2] << "\n";
        out << "c1_speed=" << allAt[3] << "\n";
        out << "c1_atk_f=" << allAt[4] << "\n";
        out << "c1_atk_r=" << allAt[5] << "\n";
        out << "c1_atk_s=" << allAt[6] << "\n";
        out << "c2_limhealth=" << allAt[7] << "\n";
        out << "c2_damage=" << allAt[8] << "\n";
        out << "c2_speed=" << allAt[9] << "\n";
        out << "c2_atk_f=" << allAt[10] << "\n";
        out << "c2_atk_r=" << allAt[11] << "\n";
        out << "c2_atk_s=" << allAt[12] << "\n";
        out << "money_k=" << allAt[13] << "\n";
        out << "lives=" << game->lives << "\n";

        // 关闭文件
        file.close();
    }
    qApp->quit();
}

void MainWindow::on_h_enhance_clicked()
{
    game->character->curHealth += 20;
    if(game->character->curHealth > game->character->limHealth)
        game->character->limHealth = game->character->curHealth;
    setButtonUnable();
    game->resume();
}

void MainWindow::on_a_enhance_clicked()
{
    game->character->damage += 5;
    setButtonUnable();
    game->resume();
}

void MainWindow::on_s_enhance_clicked()
{
    game->character->speed += 1;
    setButtonUnable();
    game->resume();
}

void MainWindow::on_af_enhance_clicked()
{
    game->character->atk_f *= 0.9;
    game->timer1->setInterval(game->character->atk_f);
    setButtonUnable();
    game->resume();
}

void MainWindow::on_ar_enhance_clicked()
{
    game->character->atk_r *= 1.2;
    setButtonUnable();
    game->resume();
}

void MainWindow::on_as_enhance_clicked()
{
    game->character->atk_s += 1;
    setButtonUnable();
    game->resume();
}
