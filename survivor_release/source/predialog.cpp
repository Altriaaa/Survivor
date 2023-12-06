#include "predialog.h"
#include "ui_predialog.h"

PreDialog::PreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreDialog)
{
    ui->setupUi(this);
    ui->Start->setEnabled(false);
    timer = new QTimer(this);
    timer->setInterval(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(At_update()));
    timer->start();
}

PreDialog::~PreDialog()
{
    delete ui;
}

void PreDialog::At_update()
{
    if(allAt.size() != 0)
    {
    ui->money->setText(tr("持有金币：%1").arg(allAt[0]));
    ui->c1_h->setText(tr("%1").arg(allAt[1]));
    ui->c1_d->setText(tr("%1").arg(allAt[2]));
    ui->c1_s->setText(tr("%1").arg(allAt[3]));
    ui->c1_atk_f->setText(tr("%1").arg(allAt[4]));
    ui->c1_atk_r->setText(tr("%1").arg(allAt[5]));
    ui->c1_atk_s->setText(tr("%1").arg(allAt[6]));
    ui->c2_h->setText(tr("%1").arg(allAt[7]));
    ui->c2_d->setText(tr("%1").arg(allAt[8]));
    ui->c2_s->setText(tr("%1").arg(allAt[9]));
    ui->c2_atk_f->setText(tr("%1").arg(allAt[10]));
    ui->c2_atk_r->setText(tr("%1").arg(allAt[11]));
    ui->c2_atk_s->setText(tr("%1").arg(allAt[12]));
    ui->money_k->setText(tr("%1").arg(allAt[13]));
    ui->lives->setText(tr("%1").arg(allAt[14]));
    }
}

void PreDialog::on_Start_clicked()
{
    emit sigAllAt(allAt);
    accept();
}

void PreDialog::on_cha_soldier_clicked()
{
    ui->save_label->setText(tr("当前选择：角色1"));
    emit sig_charac_order(0);
    ui->Start->setEnabled(true);
}

void PreDialog::on_cha_magician_clicked()
{
    ui->save_label->setText(tr("当前选择：角色2"));
    emit sig_charac_order(1);
    ui->Start->setEnabled(true);
}

void PreDialog::on_Continue_clicked()
{
    if(allAt.size() != 0)
        allAt.clear();
    QFile file("./save.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open the file.";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        // 在这里处理每一行的数据
        // 假设每行数据格式为：键=值
        QStringList parts = line.split('=');
        if (parts.size() == 2)
        {
            QString key = parts[0].trimmed();
            int value = parts[1].trimmed().toInt();
            allAt.push_back(value);
            //qDebug() << "Key:" << key << ", Value:" << value;
        }
    }
    file.close();
    emit sigAllAt(allAt);
    ui->save_label->setText(tr("存档已载入"));
}

void PreDialog::on_c1_h_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要100"));
    else if(allAt[0]<100)
        ui->save_label->setText(tr("金币不足，需要100"));
    else
    {
        allAt[1] += 20;
        allAt[0] -= 100;
    }
    emit sigAllAt(allAt);
    emit sig_charac_order(0);
}

void PreDialog::on_c1_d_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要100"));
    else if(allAt[0]<100)
        ui->save_label->setText(tr("金币不足，需要100"));
    else
    {
        allAt[2] += 5;
        allAt[0] -= 100;
    }
    emit sigAllAt(allAt);
    emit sig_charac_order(0);
}

void PreDialog::on_c1_s_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要1000"));
    else if(allAt[0]<1000)
        ui->save_label->setText(tr("金币不足，需要1000"));
    else
    {
        allAt[3] += 1;
        allAt[0] -= 1000;
    }
    emit sigAllAt(allAt);
    emit sig_charac_order(0);
}

void PreDialog::on_c1_atk_f_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要100"));
    else if(allAt[0]<100)
        ui->save_label->setText(tr("金币不足，需要100"));
    else
    {
        allAt[4] *= 0.95;
        allAt[0] -= 100;
    }
    emit sigAllAt(allAt);
    emit sig_charac_order(0);
}

void PreDialog::on_c1_atk_r_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要100"));
    else if(allAt[0]<100)
        ui->save_label->setText(tr("金币不足，需要100"));
    else
    {
        allAt[5] += 10;
        allAt[0] -= 100;
    }
    emit sigAllAt(allAt);
    emit sig_charac_order(0);
}

void PreDialog::on_c1_atk_s_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要1000"));
    else if(allAt[0]<100)
        ui->save_label->setText(tr("金币不足，需要1000"));
    else
    {
        allAt[6] += 1;
        allAt[0] -= 1000;
    }
    emit sigAllAt(allAt);
    emit sig_charac_order(0);
}

void PreDialog::on_c2_h_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要100"));
    else if(allAt[0]<100)
        ui->save_label->setText(tr("金币不足，需要100"));
    else
    {
        allAt[7] += 20;
        allAt[0] -= 100;
    }
    emit sigAllAt(allAt);
    emit sig_charac_order(1);
}
void PreDialog::on_c2_d_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要100"));
    else if(allAt[0]<100)
        ui->save_label->setText(tr("金币不足，需要100"));
    else
    {
        allAt[8] += 5;
        allAt[0] -= 100;
    }
    emit sigAllAt(allAt);
    emit sig_charac_order(1);
}

void PreDialog::on_c2_s_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要1000"));
    else if(allAt[0]<1000)
        ui->save_label->setText(tr("金币不足，需要1000"));
    else
    {
        allAt[9] += 1;
        allAt[0] -= 1000;
    }
    emit sigAllAt(allAt);
    emit sig_charac_order(1);
}

void PreDialog::on_c2_atk_f_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要100"));
    else if(allAt[0]<100)
        ui->save_label->setText(tr("金币不足，需要100"));
    else
    {
        allAt[10] *= 0.95;
        allAt[0] -= 100;
    }
    emit sigAllAt(allAt);
    emit sig_charac_order(1);
}

void PreDialog::on_c2_atk_r_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要100"));
    else if(allAt[0]<100)
        ui->save_label->setText(tr("金币不足，需要100"));
    else
    {
        allAt[11] += 10;
        allAt[0] -= 100;
    }
    emit sigAllAt(allAt);
    emit sig_charac_order(1);
}

void PreDialog::on_c2_atk_s_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要1000"));
    else if(allAt[0]<100)
        ui->save_label->setText(tr("金币不足，需要1000"));
    else
    {
        allAt[12] += 1;
        allAt[0] -= 1000;
    }
    emit sigAllAt(allAt);
    emit sig_charac_order(1);
}

void PreDialog::on_money_k_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要1000"));
    else if(allAt[0]<1000)
        ui->save_label->setText(tr("金币不足，需要1000"));
    else
    {
        allAt[13] += 10;
        allAt[0] -= 1000;
    }
    emit sigAllAt(allAt);
}

void PreDialog::on_lives_enhance_clicked()
{
    if(allAt.size() == 0)
        ui->save_label->setText(tr("金币不足，需要1000"));
    else if(allAt[0]<1000)
        ui->save_label->setText(tr("金币不足，需要1000"));
    else
    {
        allAt[14] += 1;
        allAt[0] -= 1000;
    }
    emit sigAllAt(allAt);
}
