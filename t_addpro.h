#ifndef T_ADDPRO_H
#define T_ADDPRO_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class t_Addpro;
}

class t_Addpro : public QWidget
{
    Q_OBJECT

public:
    explicit t_Addpro(QWidget *parent = 0);
    ~t_Addpro();

signals:
    void display(int number);

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_insertPtext_clicked();

    void on_insertPA_clicked();

    void on_insertPB_clicked();

    void on_insertPC_clicked();

    void on_insertPD_clicked();

private:
    Ui::t_Addpro *ui;
    QVariant varPText,varPA,varPB,varPC,varPD;//题干和选项的图片
    bool isPText,isPA,isPB,isPC,isPD;//题干和选项是否为图片


};

#endif // T_ADDPRO_H
