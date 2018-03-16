#ifndef TEST_H
#define TEST_H

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
#include "variate.h"

namespace Ui {
class Test;
}

class Test : public QWidget
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = 0);
    ~Test();
    void closeEvent(QCloseEvent *event);
    void setquestionpic(QLabel*& q,QSqlQuery& query);
    void setchoosedpic(QRadioButton*& q,QSqlQuery& query,int a);

private slots:
    void on_pushButton_clicked();
    void onTimerOut();

private:
    Ui::Test *ui;
    int a[20];//产生随机数
    QTimer *timer;
    int testtime;
    int panduan;

};


#endif // TEST_H
