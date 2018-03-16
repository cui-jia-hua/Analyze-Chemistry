#ifndef FINALTEST_H
#define FINALTEST_H

#include <QWidget>
#include <QString>
#include <qDebug>
#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtGlobal>
#include <QTime>
#include <algorithm>
#include <QButtonGroup>
#include <QMessageBox>
#include <QTimer>
#include <QFile>
#include <QPalette>
#include <QCloseEvent>
#include <QRadioButton>

namespace Ui {
class Finaltest;
}

class Finaltest : public QWidget
{
    Q_OBJECT

public:
    explicit Finaltest(QWidget *parent = 0);
    ~Finaltest();
    void closeEvent(QCloseEvent *event);
    void setquestionpic(QLabel*& q,QSqlQuery& query);
    void setchoosedpic(QRadioButton*& q,QSqlQuery& query,int a);

private slots:
    void on_pushButton_clicked();
    void onTimerOut();

private:
    Ui::Finaltest *ui;
    int a[200];//产生随机数
    QTimer *timer;
    int testtime;
    int panduan;
};

#endif // FINALTEST_H
