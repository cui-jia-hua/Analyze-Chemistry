#ifndef T_REGIST_H
#define T_REGIST_H

#include <QWidget>
#include <Qstring>
#include <string>
#include <qDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class t_Regist;
}

class t_Regist : public QWidget
{
    Q_OBJECT

public:
    explicit t_Regist(QWidget *parent = 0);
    ~t_Regist();

signals:
    void display(int number);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::t_Regist *ui;
};

#endif // T_REGIST_H
