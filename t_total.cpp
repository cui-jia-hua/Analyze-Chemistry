#include "t_total.h"
#include "ui_t_total.h"
#include "widget.h"
#include "variate.h"

t_total::t_total(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::t_total)
{
    ui->setupUi(this);
    changebutton(ui->pushButton,QString(":/image/picture/修改按钮-橙色.png"));
    changebutton(ui->pushButton_2,QString(":/image/picture/修改按钮-橙色.png"));
    changebutton(ui->pushButton_3,QString(":/image/picture/修改按钮-橙色.png"));
    changebutton(ui->pushButton_4,QString(":/image/picture/修改按钮-橙色.png"));
    changebutton(ui->pushButton_5,QString(":/image/picture/修改按钮-橙色.png"));
    changebutton(ui->pushButton_6,QString(":/image/picture/修改按钮-橙色.png"));
    /*
        //设置风格
        QFile qssfile(":/style/style/style.qss");
        qssfile.open(QFile::ReadOnly);
        QString qss;
        qss = qssfile.readAll();
        this->setStyleSheet(qss);
    */
}

t_total::~t_total()
{
    delete ui;
}

void t_total::on_pushButton_clicked()
{
    emit display(4);//查看修改题目
}

void t_total::on_pushButton_2_clicked()
{
    emit display(5);//注册修改用户
}

void t_total::on_pushButton_3_clicked()
{
    emit display(6);//导出成绩
}

void t_total::on_pushButton_4_clicked()
{
    emit display(7);//添加删除题目
}

void t_total::on_pushButton_5_clicked()
{
    emit display(8);//章节设置
}

void t_total::on_pushButton_6_clicked()
{
    emit display(9);//专业设置
}
