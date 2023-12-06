#include "condialog.h"
#include "ui_condialog.h"

condialog::condialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::condialog)
{
    ui->setupUi(this);
}

condialog::~condialog()
{
    delete ui;
}

void condialog::on_pushButton_clicked()
{
    accept();
}

void condialog::on_pushButton_2_clicked()
{
    qApp->exit();
}

void condialog::on_pushButton_3_clicked()
{
    emit sigSave();
}
