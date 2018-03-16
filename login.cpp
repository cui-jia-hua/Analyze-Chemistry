#include "login.h"
#include "ui_login.h"
#include "widget.h"
#include "variate.h"
#include "test.h"
#include "finaltest.h"
#include "createconnect.h"


using namespace std;

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    if(!createConnection(db)) qDebug()<<"warning login";
    QSqlQuery query(db);
    QString tmp = "select * from pro order by chapterindex asc";
    query.exec(tmp);
    while(query.next()){
        ui->comboBox->addItem(query.value(1).toString());
    }
    ui->comboBox->addItem(tr("期末测试"));
    ui->pushButton->hide();
    ui->label_showclass->hide();
    ui->comboBox->hide();
    ui->label_3->hide();

/*
    //设置风格
    QFile qssfile(":/style/style/style.qss");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();
    this->setStyleSheet(qss);
*/

    changebutton(ui->pushButton,QString(":/image/picture/橙色按钮.png"));
    changebutton(ui->pushButton_2,QString(":/image/picture/橙色按钮.png"));
}

Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_clicked()//开始测试
{
    if (!createConnection(db))
        qDebug() << "warning 4323";
    QString tmp = "select * from student" + QString::number(nowclassindex) + " where number = " + QString::number(ui->xuehao->text().toInt());
    qDebug()<<tmp;
    QSqlQuery query;
    query = QSqlQuery(db);
    query.exec(tmp);query.next();
    if(ui->comboBox->currentIndex() >= 0 && ui->comboBox->currentIndex() < chapternumber){
        if(query.value(ui->comboBox->currentIndex()+1).toString() != ""){
            QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                           QString("该学号已经做过测试"),
                           QMessageBox::Yes,NULL);
            changemessagebox(q);
            q.exec();
            return;
        }
    }
    else{
        if(query.value(15).toString() != ""){
            QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                           QString("该学号已经做过测试"),
                           QMessageBox::Yes,NULL);
            changemessagebox(q);
            q.exec();
            return;
        }
    }

    nowchapter = ui->comboBox->currentIndex();//从零开始
    int number = ui->xuehao->text().toInt();
    studentnumber = number;
    if(nowchapter != chapternumber){//非期末考试
        test = new Test;
        test->showMaximized();
        test->show();
    }
    else{//期末考试
        finaltest = new Finaltest;
        finaltest->showMaximized();
        finaltest->show();
    }
    ui->label_showclass->hide();//当一个学生打开窗口后隐藏学生信息
    ui->xuehao->setText("");//当一个学生打开窗口后清空上一同学学号
    ui->pushButton->hide();
    ui->comboBox->hide();
    ui->label_3->hide();
}

int Login::findnumber(int stunum)
{
    if (!createConnection(db))
        qDebug() << "warning 1";

    QSqlQuery query;
    query = QSqlQuery(db);

    QString Num =QString::number(stunum);
    QString tmp = "select * from student" + QString::number(nowclassindex) + " where number = " + Num;
    qDebug()<<tmp;

    query.exec(tmp);
    query.next();

    if(!query.isValid()){
        QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                       QString("找不到此学号，请重新输入"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();

        return 0;
    }
    else{
        ui->label_showclass->show();
        QString tmp = "select * from class where number = "+QString::number(nowclassindex);
        query.exec(tmp);query.next();
        QString info = query.value(0).toString();
        QString find = "select class, name from student" + QString::number(nowclassindex) + " where number = " + Num;
        qDebug()<<find;
        query.exec(find);
        query.next();
        info += " ";
        info += query.value(0).toString();
        info += " ";
        info += query.value(1).toString();
        ui->label_showclass->setText(info);
        return 1;
    }
}

void Login::on_pushButton_2_clicked()
{
    int number = ui->xuehao->text().toInt();
    //检查数据库中该学号对应的人，并准备更新数据
    qDebug() << number;//显示当前学号
    if(!findnumber(number))//查找当前学号是否对应一个学生
    {
        qDebug() << "NO";
    }
    else
    {
        ui->pushButton->show();
        ui->comboBox->show();
        ui->label_3->show();
    }
}
