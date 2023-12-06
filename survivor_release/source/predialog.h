#ifndef PREDIALOG_H
#define PREDIALOG_H

#include <QDialog>
#include <QFile>
#include <QDebug>
#include <QTimer>

namespace Ui {
class PreDialog;
}

class PreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreDialog(QWidget *parent = nullptr);
    ~PreDialog();

private slots:
    void At_update();
    void on_Start_clicked();

    void on_cha_soldier_clicked();

    void on_cha_magician_clicked();

    void on_Continue_clicked();

    void on_c1_h_enhance_clicked();

    void on_c1_d_enhance_clicked();

    void on_c1_s_enhance_clicked();

    void on_c1_atk_f_enhance_clicked();

    void on_c1_atk_r_enhance_clicked();

    void on_c1_atk_s_enhance_clicked();

    void on_c2_h_enhance_clicked();

    void on_c2_d_enhance_clicked();

    void on_c2_s_enhance_clicked();

    void on_c2_atk_f_enhance_clicked();

    void on_c2_atk_r_enhance_clicked();

    void on_c2_atk_s_enhance_clicked();

    void on_money_k_enhance_clicked();

    void on_lives_enhance_clicked();

private:
    Ui::PreDialog *ui;
    QVector<int> allAt;
    QTimer* timer;

signals:
    void sig_charac_order(int);
    void sigAllAt(QVector<int>);

};

#endif // PREDIALOG_H
