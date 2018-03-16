#ifndef T_TOTAL_H
#define T_TOTAL_H

#include <QWidget>
#include <QDebug>


namespace Ui {
class t_total;
}

class t_total : public QWidget
{
    Q_OBJECT

public:
    explicit t_total(QWidget *parent = 0);
    ~t_total();

signals:
    void display(int number);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::t_total *ui;
};

#endif // T_TOTAL_H
