#ifndef CONDIALOG_H
#define CONDIALOG_H

#include <QDialog>

namespace Ui {
class condialog;
}

class condialog : public QDialog
{
    Q_OBJECT

public:
    explicit condialog(QWidget *parent = nullptr);
    ~condialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::condialog *ui;
signals:
    void sigSave();
};

#endif // CONDIALOG_H
