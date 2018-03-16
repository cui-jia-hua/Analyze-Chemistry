#ifndef VARIATE_H
#define VARIATE_H

#include <QSqlDatabase>
#include <QPushButton>
#include <QPixmap>
#include <QBitmap>

extern int nowchapter;//第几章
extern int studentnumber;//学号
extern int chapternumber;//单元总数
extern int eachdanyuan[20];//每个单元题目的数量
extern int totalquestionnumber;//总题目数
extern int totalstudentnumber;//总学生数
extern QSqlDatabase db;//数据库
extern int nowclassindex;//当前专业班级

static void changebutton(QPushButton *&p,QString str)
{
    QPixmap pixmap(str);pixmap = pixmap.scaled(350,128);
    p->setFixedSize(pixmap.size());
    p->setMask(QBitmap(pixmap.mask()));
}

#endif // VARIATE_H
