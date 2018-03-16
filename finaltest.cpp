#include "finaltest.h"
#include "ui_finaltest.h"
#include "widget.h"
#include "createconnect.h"
#include "variate.h"

using namespace std;

Finaltest::Finaltest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Finaltest)
{
    ui->setupUi(this);
    changebutton(ui->pushButton,QString(":/image/picture/橙色按钮.png"));

    panduan=0;

    if (!createConnection(db))
        qDebug() << "warning";
    QSqlQuery query;
    query = QSqlQuery(db);
    bool i = query.exec("select * from problem");
    if(!i) qDebug() << query.lastError();

    //设置标题
    QString str = "期末测试";
    ui->label_3->setText(str);
    qDebug()<<"totalquestionnumber = " <<totalquestionnumber;
    //产生随机数
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0; i<totalquestionnumber; ++i) a[i]=i;
    //for(int i=eachdanyuan[nowchapter]+1; i>1; --i) swap(a[i], a[qrand()%(i-1)]);
    for(int i = 0; i < totalquestionnumber; i++){
        if(qrand()%2){
            swap(a[i],a[(i+rand()%100) % totalquestionnumber]);
        }
    }
    for(int i = 0; i < 20; i++) qDebug() << a[i];

    query.seek(a[0]);
    setquestionpic(ui->text1,query);
    setchoosedpic(ui->test1a,query,1);
    setchoosedpic(ui->test1b,query,2);
    setchoosedpic(ui->test1c,query,3);
    setchoosedpic(ui->test1d,query,4);

//    ui->test1->setText(query.value(2).toString());
//    ui->test1a->setText(query.value(3).toString());
//    ui->test1b->setText(query.value(4).toString());
//    ui->test1c->setText(query.value(5).toString());
//    ui->test1d->setText(query.value(6).toString());

    query.seek(a[1]);
    setquestionpic(ui->text2,query);
    setchoosedpic(ui->test2a,query,1);
    setchoosedpic(ui->test2b,query,2);
    setchoosedpic(ui->test2c,query,3);
    setchoosedpic(ui->test2d,query,4);
//    ui->test2->setText(query.value(2).toString());
//    ui->test2a->setText(query.value(3).toString());
//    ui->test2b->setText(query.value(4).toString());
//    ui->test2c->setText(query.value(5).toString());
//    ui->test2d->setText(query.value(6).toString());
    query.seek(a[2]);
    setquestionpic(ui->text3,query);
    setchoosedpic(ui->test3a,query,1);
    setchoosedpic(ui->test3b,query,2);
    setchoosedpic(ui->test3c,query,3);
    setchoosedpic(ui->test3d,query,4);
//    ui->test3->setText(query.value(2).toString());
//    ui->test3a->setText(query.value(3).toString());
//    ui->test3b->setText(query.value(4).toString());
//    ui->test3c->setText(query.value(5).toString());
//    ui->test3d->setText(query.value(6).toString());
    query.seek(a[3]);
    setquestionpic(ui->text4,query);
    setchoosedpic(ui->test4a,query,1);
    setchoosedpic(ui->test4b,query,2);
    setchoosedpic(ui->test4c,query,3);
    setchoosedpic(ui->test4d,query,4);
//    ui->test4->setText(query.value(2).toString());
//    ui->test4a->setText(query.value(3).toString());
//    ui->test4b->setText(query.value(4).toString());
//    ui->test4c->setText(query.value(5).toString());
//    ui->test4d->setText(query.value(6).toString());
    query.seek(a[4]);
    setquestionpic(ui->text5,query);
    setchoosedpic(ui->test5a,query,1);
    setchoosedpic(ui->test5b,query,2);
    setchoosedpic(ui->test5c,query,3);
    setchoosedpic(ui->test5d,query,4);
//    ui->test5->setText(query.value(2).toString());
//    ui->test5a->setText(query.value(3).toString());
//    ui->test5b->setText(query.value(4).toString());
//    ui->test5c->setText(query.value(5).toString());
//    ui->test5d->setText(query.value(6).toString());
    query.seek(a[5]);
    setquestionpic(ui->text6,query);
    setchoosedpic(ui->test6a,query,1);
    setchoosedpic(ui->test6b,query,2);
    setchoosedpic(ui->test6c,query,3);
    setchoosedpic(ui->test6d,query,4);
//    ui->test6->setText(query.value(2).toString());
//    ui->test6a->setText(query.value(3).toString());
//    ui->test6b->setText(query.value(4).toString());
//    ui->test6c->setText(query.value(5).toString());
//    ui->test6d->setText(query.value(6).toString());
    query.seek(a[6]);
    setquestionpic(ui->text7,query);
    setchoosedpic(ui->test7a,query,1);
    setchoosedpic(ui->test7b,query,2);
    setchoosedpic(ui->test7c,query,3);
    setchoosedpic(ui->test7d,query,4);
//    ui->test7->setText(query.value(2).toString());
//    ui->test7a->setText(query.value(3).toString());
//    ui->test7b->setText(query.value(4).toString());
//    ui->test7c->setText(query.value(5).toString());
//    ui->test7d->setText(query.value(6).toString());
    query.seek(a[7]);
    setquestionpic(ui->text8,query);
    setchoosedpic(ui->test8a,query,1);
    setchoosedpic(ui->test8b,query,2);
    setchoosedpic(ui->test8c,query,3);
    setchoosedpic(ui->test8d,query,4);
//    ui->test8->setText(query.value(2).toString());
//    ui->test8a->setText(query.value(3).toString());
//    ui->test8b->setText(query.value(4).toString());
//    ui->test8c->setText(query.value(5).toString());
//    ui->test8d->setText(query.value(6).toString());
    query.seek(a[8]);
    setquestionpic(ui->text9,query);
    setchoosedpic(ui->test9a,query,1);
    setchoosedpic(ui->test9b,query,2);
    setchoosedpic(ui->test9c,query,3);
    setchoosedpic(ui->test9d,query,4);
//    ui->test9->setText(query.value(2).toString());
//    ui->test9a->setText(query.value(3).toString());
//    ui->test9b->setText(query.value(4).toString());
//    ui->test9c->setText(query.value(5).toString());
//    ui->test9d->setText(query.value(6).toString());
    query.seek(a[9]);
    setquestionpic(ui->text10,query);
    setchoosedpic(ui->test10a,query,1);
    setchoosedpic(ui->test10b,query,2);
    setchoosedpic(ui->test10c,query,3);
    setchoosedpic(ui->test10d,query,4);
//    ui->test10->setText(query.value(2).toString());
//    ui->test10a->setText(query.value(3).toString());
//    ui->test10b->setText(query.value(4).toString());
//    ui->test10c->setText(query.value(5).toString());
//    ui->test10d->setText(query.value(6).toString());
    query.seek(a[10]);
    setquestionpic(ui->text11,query);
    setchoosedpic(ui->test11a,query,1);
    setchoosedpic(ui->test11b,query,2);
    setchoosedpic(ui->test11c,query,3);
    setchoosedpic(ui->test11d,query,4);
//    ui->test11->setText(query.value(2).toString());
//    ui->test11a->setText(query.value(3).toString());
//    ui->test11b->setText(query.value(4).toString());
//    ui->test11c->setText(query.value(5).toString());
//    ui->test11d->setText(query.value(6).toString());
    query.seek(a[11]);
    setquestionpic(ui->text12,query);
    setchoosedpic(ui->test12a,query,1);
    setchoosedpic(ui->test12b,query,2);
    setchoosedpic(ui->test12c,query,3);
    setchoosedpic(ui->test12d,query,4);
//    ui->test12->setText(query.value(2).toString());
//    ui->test12a->setText(query.value(3).toString());
//    ui->test12b->setText(query.value(4).toString());
//    ui->test12c->setText(query.value(5).toString());
//    ui->test12d->setText(query.value(6).toString());
    query.seek(a[12]);
    setquestionpic(ui->text13,query);
    setchoosedpic(ui->test13a,query,1);
    setchoosedpic(ui->test13b,query,2);
    setchoosedpic(ui->test13c,query,3);
    setchoosedpic(ui->test13d,query,4);
//    ui->test13->setText(query.value(2).toString());
//    ui->test13a->setText(query.value(3).toString());
//    ui->test13b->setText(query.value(4).toString());
//    ui->test13c->setText(query.value(5).toString());
//    ui->test13d->setText(query.value(6).toString());
    query.seek(a[13]);
    setquestionpic(ui->text14,query);
    setchoosedpic(ui->test14a,query,1);
    setchoosedpic(ui->test14b,query,2);
    setchoosedpic(ui->test14c,query,3);
    setchoosedpic(ui->test14d,query,4);
//    ui->test14->setText(query.value(2).toString());
//    ui->test14a->setText(query.value(3).toString());
//    ui->test14b->setText(query.value(4).toString());
//    ui->test14c->setText(query.value(5).toString());
//    ui->test14d->setText(query.value(6).toString());
    query.seek(a[14]);
    setquestionpic(ui->text15,query);
    setchoosedpic(ui->test15a,query,1);
    setchoosedpic(ui->test15b,query,2);
    setchoosedpic(ui->test15c,query,3);
    setchoosedpic(ui->test15d,query,4);
//    ui->test15->setText(query.value(2).toString());
//    ui->test15a->setText(query.value(3).toString());
//    ui->test15b->setText(query.value(4).toString());
//    ui->test15c->setText(query.value(5).toString());
//    ui->test15d->setText(query.value(6).toString());
    query.seek(a[15]);
    setquestionpic(ui->text16,query);
    setchoosedpic(ui->test16a,query,1);
    setchoosedpic(ui->test16b,query,2);
    setchoosedpic(ui->test16c,query,3);
    setchoosedpic(ui->test16d,query,4);
//    ui->test16->setText(query.value(2).toString());
//    ui->test16a->setText(query.value(3).toString());
//    ui->test16b->setText(query.value(4).toString());
//    ui->test16c->setText(query.value(5).toString());
//    ui->test16d->setText(query.value(6).toString());
    query.seek(a[16]);
    setquestionpic(ui->text17,query);
    setchoosedpic(ui->test17a,query,1);
    setchoosedpic(ui->test17b,query,2);
    setchoosedpic(ui->test17c,query,3);
    setchoosedpic(ui->test17d,query,4);
//    ui->test17->setText(query.value(2).toString());
//    ui->test17a->setText(query.value(3).toString());
//    ui->test17b->setText(query.value(4).toString());
//    ui->test17c->setText(query.value(5).toString());
//    ui->test17d->setText(query.value(6).toString());
    query.seek(a[17]);
    setquestionpic(ui->text18,query);
    setchoosedpic(ui->test18a,query,1);
    setchoosedpic(ui->test18b,query,2);
    setchoosedpic(ui->test18c,query,3);
    setchoosedpic(ui->test18d,query,4);
//    ui->test18->setText(query.value(2).toString());
//    ui->test18a->setText(query.value(3).toString());
//    ui->test18b->setText(query.value(4).toString());
//    ui->test18c->setText(query.value(5).toString());
//    ui->test18d->setText(query.value(6).toString());
    query.seek(a[18]);
    setquestionpic(ui->text19,query);
    setchoosedpic(ui->test19a,query,1);
    setchoosedpic(ui->test19b,query,2);
    setchoosedpic(ui->test19c,query,3);
    setchoosedpic(ui->test19d,query,4);
//    ui->test19->setText(query.value(2).toString());
//    ui->test19a->setText(query.value(3).toString());
//    ui->test19b->setText(query.value(4).toString());
//    ui->test19c->setText(query.value(5).toString());
//    ui->test19d->setText(query.value(6).toString());
    query.seek(a[19]);
    setquestionpic(ui->text20,query);
    setchoosedpic(ui->test20a,query,1);
    setchoosedpic(ui->test20b,query,2);
    setchoosedpic(ui->test20c,query,3);
    setchoosedpic(ui->test20d,query,4);
//    ui->test20->setText(query.value(2).toString());
//    ui->test20a->setText(query.value(3).toString());
//    ui->test20b->setText(query.value(4).toString());
//    ui->test20c->setText(query.value(5).toString());
//    ui->test20d->setText(query.value(6).toString());

    //新建一个QTimer对象
    timer = new QTimer();testtime = 0;
    //设置定时器每个多少毫秒发送一个timeout()信号
    timer->setInterval(1000);
    //启动定时器
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    //改变定时器颜色
    QPalette lcdpat = ui->lcdNumber->palette();
    /*设置颜色，整体背景颜色 颜色蓝色,此函数的第一个参数可以设置多种。如文本、按钮按钮文字、多种*/
    lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::green);
    //设置当前窗口的调色板
    ui->lcdNumber->setPalette(lcdpat);
    //设置背景色
    ui->lcdNumber->setStyleSheet("background-color: black");
    ui->lcdNumber->setDigitCount(4);
    ui->lcdNumber->display(600);
}

void Finaltest::setquestionpic(QLabel*& q,QSqlQuery& query)
{
    if(query.value(8).toString() != ""){
        QByteArray bta = query.value(8).toByteArray();
        QPixmap img;img.loadFromData(bta);
        //img = img.scaled(q->width(),q->height());
        q->setPixmap(img);
    }else{
        q->setText(query.value(2).toString());
    }
}

void Finaltest::setchoosedpic(QRadioButton*& q,QSqlQuery& query,int a)
{
    int npic = a + 8;
    if(query.value(npic).toString() != ""){
        QByteArray bta = query.value(npic).toByteArray();
        QPixmap img;img.loadFromData(bta);
        //img = img.scaled(q->width(),q->height());
        q->setIconSize(QSize(500,200));q->setText("");
        q->setIcon(img);//q->setFixedSize(img.size());
    }else{
        q->setText(query.value(a+2).toString());
    }
}


void Finaltest::closeEvent(QCloseEvent *event)
{
    if(!panduan){
        QMessageBox q (QMessageBox::NoIcon,QString("退出程序"),
                       QString("警告：还未结束测试，是否退出（成绩将不会录入）?"),
                       QMessageBox::Yes|QMessageBox::No,NULL);
        changemessagebox(q);
        if (q.exec() == QMessageBox::Yes) {
            timer->stop();
            event->accept();  //接受退出信号，程序退出
        }
        else{
            event->ignore();
        }
    }
    else{
        timer->stop();
        event->accept();
    }

}
void Finaltest::onTimerOut()//自动提交
{
    testtime++;
    if(testtime >= 600){
        timer->stop();
        on_pushButton_clicked();
    }
    else ui->lcdNumber->display(600-testtime);
}


Finaltest::~Finaltest()
{
    delete ui;
}

void Finaltest::on_pushButton_clicked()
{
    timer->stop();
    QString Num =QString::number(studentnumber);
    qDebug () << "the" + Num + "upload the answer";
    int A[20] = {0};
    QButtonGroup thechoosed[20];// = new QButtonGroup(this);
    thechoosed[0].addButton(ui->test1a, 1);
    thechoosed[0].addButton(ui->test1b, 2);
    thechoosed[0].addButton(ui->test1c, 3);
    thechoosed[0].addButton(ui->test1d, 4);
    //ui->radioButton_1->setChecked(true);
   // A[0] = thechoosed[0].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[1].addButton(ui->test2a, 1);
    thechoosed[1].addButton(ui->test2b, 2);
    thechoosed[1].addButton(ui->test2c, 3);
    thechoosed[1].addButton(ui->test2d, 4);
    //ui->radioButton11->setChecked(true);
   // A[1] = thechoosed[1].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[2].addButton(ui->test3a, 1);
    thechoosed[2].addButton(ui->test3b, 2);
    thechoosed[2].addButton(ui->test3c, 3);
    thechoosed[2].addButton(ui->test3d, 4);
    //ui->radioButton11->setChecked(true);
   // A[2] = thechoosed[2].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[3].addButton(ui->test4a, 1);
    thechoosed[3].addButton(ui->test4b, 2);
    thechoosed[3].addButton(ui->test4c, 3);
    thechoosed[3].addButton(ui->test4d, 4);
    //ui->radioButton11->setChecked(true);
   // A[3] = thechoosed[3].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[4].addButton(ui->test5a, 1);
    thechoosed[4].addButton(ui->test5b, 2);
    thechoosed[4].addButton(ui->test5c, 3);
    thechoosed[4].addButton(ui->test5d, 4);
    //ui->radioButton11->setChecked(true);
    //A[4] = thechoosed[4].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[5].addButton(ui->test6a, 1);
    thechoosed[5].addButton(ui->test6b, 2);
    thechoosed[5].addButton(ui->test6c, 3);
    thechoosed[5].addButton(ui->test6d, 4);
    //ui->radioButton11->setChecked(true);
    //A[5] = thechoosed[5].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[6].addButton(ui->test7a, 1);
    thechoosed[6].addButton(ui->test7b, 2);
    thechoosed[6].addButton(ui->test7c, 3);
    thechoosed[6].addButton(ui->test7d, 4);
    //ui->radioButton11->setChecked(true);
    //A[6] = thechoosed[6].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[7].addButton(ui->test8a, 1);
    thechoosed[7].addButton(ui->test8b, 2);
    thechoosed[7].addButton(ui->test8c, 3);
    thechoosed[7].addButton(ui->test8d, 4);
    //ui->radioButton11->setChecked(true);
    //A[7] = thechoosed[7].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[8].addButton(ui->test9a, 1);
    thechoosed[8].addButton(ui->test9b, 2);
    thechoosed[8].addButton(ui->test9c, 3);
    thechoosed[8].addButton(ui->test9d, 4);
    //ui->radioButton11->setChecked(true);
   // A[8] = thechoosed[8].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[9].addButton(ui->test10a, 1);
    thechoosed[9].addButton(ui->test10b, 2);
    thechoosed[9].addButton(ui->test10c, 3);
    thechoosed[9].addButton(ui->test10d, 4);
    //ui->radioButton11->setChecked(true);
   // A[9] = thechoosed[9].checkedId();
    thechoosed[10].addButton(ui->test11a, 1);
    thechoosed[10].addButton(ui->test11b, 2);
    thechoosed[10].addButton(ui->test11c, 3);
    thechoosed[10].addButton(ui->test11d, 4);
    //ui->radioButton11->setChecked(true);
   // A[10] = thechoosed[10].checkedId();
    thechoosed[11].addButton(ui->test12a, 1);
    thechoosed[11].addButton(ui->test12b, 2);
    thechoosed[11].addButton(ui->test12c, 3);
    thechoosed[11].addButton(ui->test12d, 4);
    //ui->radioButton11->setChecked(true);
   // A[11] = thechoosed[11].checkedId();
    thechoosed[12].addButton(ui->test13a, 1);
    thechoosed[12].addButton(ui->test13b, 2);
    thechoosed[12].addButton(ui->test13c, 3);
    thechoosed[12].addButton(ui->test13d, 4);
    //ui->radioButton11->setChecked(true);
    //A[12] = thechoosed[12].checkedId();
    thechoosed[13].addButton(ui->test14a, 1);
    thechoosed[13].addButton(ui->test14b, 2);
    thechoosed[13].addButton(ui->test14c, 3);
    thechoosed[13].addButton(ui->test14d, 4);
    //ui->radioButton11->setChecked(true);
    //A[13] = thechoosed[13].checkedId();
    thechoosed[14].addButton(ui->test15a, 1);
    thechoosed[14].addButton(ui->test15b, 2);
    thechoosed[14].addButton(ui->test15c, 3);
    thechoosed[14].addButton(ui->test15d, 4);
    //ui->radioButton11->setChecked(true);
    //A[14] = thechoosed[14].checkedId();
    thechoosed[15].addButton(ui->test16a, 1);
    thechoosed[15].addButton(ui->test16b, 2);
    thechoosed[15].addButton(ui->test16c, 3);
    thechoosed[15].addButton(ui->test16d, 4);
    //ui->radioButton11->setChecked(true);
    //A[15] = thechoosed[15].checkedId();
    thechoosed[16].addButton(ui->test17a, 1);
    thechoosed[16].addButton(ui->test17b, 2);
    thechoosed[16].addButton(ui->test17c, 3);
    thechoosed[16].addButton(ui->test17d, 4);
    //ui->radioButton11->setChecked(true);
    //A[16] = thechoosed[16].checkedId();
    thechoosed[17].addButton(ui->test18a, 1);
    thechoosed[17].addButton(ui->test18b, 2);
    thechoosed[17].addButton(ui->test18c, 3);
    thechoosed[17].addButton(ui->test18d, 4);
    //ui->radioButton11->setChecked(true);
    //A[17] = thechoosed[17].checkedId();
    thechoosed[18].addButton(ui->test19a, 1);
    thechoosed[18].addButton(ui->test19b, 2);
    thechoosed[18].addButton(ui->test19c, 3);
    thechoosed[18].addButton(ui->test19d, 4);
    //ui->radioButton11->setChecked(true);
   // A[18] = thechoosed[18].checkedId();
    thechoosed[19].addButton(ui->test20a, 1);
    thechoosed[19].addButton(ui->test20b, 2);
    thechoosed[19].addButton(ui->test20c, 3);
    thechoosed[19].addButton(ui->test20d, 4);
    //ui->radioButton11->setChecked(true);
    //A[19] = thechoosed[19].checkedId();

    for(int i = 0; i < 20; i++){
        A[i] = thechoosed[i].checkedId();
    }
    //对比数据库中各题的答案
    int score = 0;

    QSqlQuery query;
    query = QSqlQuery(db);
    query.exec("select answer from problem");
    for(int i = 0; i < 20; i++){
        query.seek(a[i]);//小a是题目，大A是学生选择的答案
        if(query.value(0) == A[i])
            score++;
    }
    qDebug() << "the score is " << score;
    QString Score = QString::number(score);

    QSqlQuery query2;
    query2 = QSqlQuery(db);
    QString tmp = "update student" + QString::number(nowclassindex) + " set final = " + QString::number(score) + " where number = " + Num;//首字母大写为QString型
    query2.exec(tmp);

    QMessageBox q (QMessageBox::NoIcon,QString("已完成"),
                   QString("你的得分是: "+Score),
                   QMessageBox::Yes,NULL);
    changemessagebox(q);
    q.exec();

    panduan=1;
    this->close();
}
