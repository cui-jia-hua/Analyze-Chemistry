#include "start.h"
#include "ui_start.h"
#include "widget.h"
#include "variate.h"
#include "createconnect.h"

Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    changebutton(ui->pushButton,QString(":/image/picture/修改按钮-橙色.png"));
    changebutton(ui->pushButton_2,QString(":/image/picture/修改按钮-橙色.png"));

    if (!createConnection(db))
        qDebug() << "warning 1";
    QSqlQuery query;
    query = QSqlQuery(db);
    QString tmp = "select questionnumber from pro";
    query.exec(tmp);totalquestionnumber = 0;chapternumber=0;
    while(query.next()){
        eachdanyuan[chapternumber] = query.value(0).toInt();
        totalquestionnumber += eachdanyuan[chapternumber];
        chapternumber++;
    }
    //提供班级选项
    tmp = "select * from class order by number asc";
    query.exec(tmp);
    while(query.next()){
        ui->whichclass->addItem(query.value(0).toString());
    }

}

Start::~Start()
{
    delete ui;
}

void Start::on_pushButton_clicked()
{
    int nowindex = ui->whichclass->currentIndex();//从零开始
    //qDebug()<<nowindex<<";";
    if (!createConnection(db))
        qDebug() << "warning 111";
    QSqlQuery query;
    query = QSqlQuery(db);
    QString tmp = "select * from class";
    query.exec(tmp);
    do{
        query.next();
    }while(nowindex--);
    nowclassindex = query.value(1).toInt();
   // qDebug()<<nowclassindex<<";;;;;;;;;;;";

    emit display(1);//学生登录界面
}

void Start::on_pushButton_2_clicked()
{
    emit display(2);//教师入口
}
