#include "test.h"
#include "ui_test.h"
#include "widget.h"
#include "createconnect.h"
#include "variate.h"

using namespace std;

//int a[20];

Test::Test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("测试"));

    changebutton(ui->pushButton,QString(":/image/picture/橙色按钮.png"));

    if(eachdanyuan[nowchapter] < 10){
        QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                       QString("请联系指导教师"),
                       QMessageBox::Yes|QMessageBox::No,NULL);
        changemessagebox(q);
        q.exec();
        this->close();
        return;
    }

    panduan=0;//是否用户主动提交

    if (!createConnection(db))
        qDebug() << "warning";
    QSqlQuery query;
    query = QSqlQuery(db);
    //设置标题
    QString str = "select * from pro where chapterindex = "+QString::number(nowchapter+1);
    query.exec(str);query.next();
    ui->label_title->setText(query.value(1).toString());

    bool i = query.exec("select * from problem where danyuan = " + QString::number(nowchapter+1));
    if(!i) qDebug() << query.lastError();

    //产生随机数
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0; i<eachdanyuan[nowchapter]; ++i) a[i]=i;
    //for(int i=eachdanyuan[nowchapter]+1; i>1; --i) swap(a[i], a[qrand()%(i-1)]);
    for(int i = 0; i < eachdanyuan[nowchapter]; i++){
        if(qrand()%2){
            swap(a[i],a[(i+rand()%100) % eachdanyuan[nowchapter]]);
        }
    }

    int tmpsum = 0;
    for(int i = 0; i < nowchapter; i++)
        tmpsum += eachdanyuan[i];

    for(int i = 0; i < 10; i++)
        qDebug() << a[i] << " ";

    query.seek(a[0]);
    setquestionpic(ui->text1,query);
    setchoosedpic(ui->radioButton_1,query,1);
    setchoosedpic(ui->radioButton_2,query,2);
    setchoosedpic(ui->radioButton_3,query,3);
    setchoosedpic(ui->radioButton_4,query,4);
    /*
    ui->radioButton_1->setText(query.value(3).toString());
    ui->radioButton_2->setText(query.value(4).toString());
    ui->radioButton_3->setText(query.value(5).toString());
    ui->radioButton_4->setText(query.value(6).toString());
    */
    query.seek(a[1]);
    setquestionpic(ui->text2,query);
    setchoosedpic(ui->radioButton_5,query,1);
    setchoosedpic(ui->radioButton_6,query,2);
    setchoosedpic(ui->radioButton_7,query,3);
    setchoosedpic(ui->radioButton_8,query,4);
    /*
    ui->text2->setText(query.value(2).toString());
    ui->radioButton_5->setText(query.value(3).toString());
    ui->radioButton_6->setText(query.value(4).toString());
    ui->radioButton_7->setText(query.value(5).toString());
    ui->radioButton_8->setText(query.value(6).toString());
    */
    query.seek(a[2] );
    setquestionpic(ui->text3,query);
    setchoosedpic(ui->radioButton_9,query,1);
    setchoosedpic(ui->radioButton_10,query,2);
    setchoosedpic(ui->radioButton_11,query,3);
    setchoosedpic(ui->radioButton_12,query,4);
    /*
    ui->text3->setText(query.value(2).toString());
    ui->radioButton_9->setText(query.value(3).toString());
    ui->radioButton_10->setText(query.value(4).toString());
    ui->radioButton_11->setText(query.value(5).toString());
    ui->radioButton_12->setText(query.value(6).toString());
    */
    query.seek(a[3] );
    setquestionpic(ui->text4,query);
    setchoosedpic(ui->radioButton_13,query,1);
    setchoosedpic(ui->radioButton_14,query,2);
    setchoosedpic(ui->radioButton_15,query,3);
    setchoosedpic(ui->radioButton_16,query,4);
    /*ui->text4->setText(query.value(2).toString());
    ui->radioButton_13->setText(query.value(3).toString());
    ui->radioButton_14->setText(query.value(4).toString());
    ui->radioButton_15->setText(query.value(5).toString());
    ui->radioButton_16->setText(query.value(6).toString());*/
    query.seek(a[4] );
    setquestionpic(ui->text5,query);
    setchoosedpic(ui->radioButton_17,query,1);
    setchoosedpic(ui->radioButton_18,query,2);
    setchoosedpic(ui->radioButton_19,query,3);
    setchoosedpic(ui->radioButton_20,query,4);
//    ui->text5->setText(query.value(2).toString());
//    ui->radioButton_17->setText(query.value(3).toString());
//    ui->radioButton_18->setText(query.value(4).toString());
//    ui->radioButton_19->setText(query.value(5).toString());
//    ui->radioButton_20->setText(query.value(6).toString());
    query.seek(a[5] );
    setquestionpic(ui->text6,query);
    setchoosedpic(ui->radioButton_21,query,1);
    setchoosedpic(ui->radioButton_22,query,2);
    setchoosedpic(ui->radioButton_23,query,3);
    setchoosedpic(ui->radioButton_24,query,4);
//    ui->text6->setText(query.value(2).toString());
//    ui->radioButton_21->setText(query.value(3).toString());
//    ui->radioButton_22->setText(query.value(4).toString());
//    ui->radioButton_23->setText(query.value(5).toString());
//    ui->radioButton_24->setText(query.value(6).toString());
    query.seek(a[6] );
    setquestionpic(ui->text7,query);
    setchoosedpic(ui->radioButton_25,query,1);
    setchoosedpic(ui->radioButton_26,query,2);
    setchoosedpic(ui->radioButton_27,query,3);
    setchoosedpic(ui->radioButton_28,query,4);
//    ui->text7->setText(query.value(2).toString());
//    ui->radioButton_25->setText(query.value(3).toString());
//    ui->radioButton_26->setText(query.value(4).toString());
//    ui->radioButton_27->setText(query.value(5).toString());
//    ui->radioButton_28->setText(query.value(6).toString());
    query.seek(a[7] );
    setquestionpic(ui->text8,query);
    setchoosedpic(ui->radioButton_29,query,1);
    setchoosedpic(ui->radioButton_30,query,2);
    setchoosedpic(ui->radioButton_31,query,3);
    setchoosedpic(ui->radioButton_32,query,4);
//    ui->text8->setText(query.value(2).toString());
//    ui->radioButton_29->setText(query.value(3).toString());
//    ui->radioButton_30->setText(query.value(4).toString());
//    ui->radioButton_31->setText(query.value(5).toString());
//    ui->radioButton_32->setText(query.value(6).toString());
    query.seek(a[8] );
    setquestionpic(ui->text9,query);
    setchoosedpic(ui->radioButton_33,query,1);
    setchoosedpic(ui->radioButton_34,query,2);
    setchoosedpic(ui->radioButton_35,query,3);
    setchoosedpic(ui->radioButton_36,query,4);
//    ui->text9->setText(query.value(2).toString());
//    ui->radioButton_33->setText(query.value(3).toString());
//    ui->radioButton_34->setText(query.value(4).toString());
//    ui->radioButton_35->setText(query.value(5).toString());
//    ui->radioButton_36->setText(query.value(6).toString());
    query.seek(a[9] );
    setquestionpic(ui->text10,query);
    setchoosedpic(ui->radioButton_37,query,1);
    setchoosedpic(ui->radioButton_38,query,2);
    setchoosedpic(ui->radioButton_39,query,3);
    setchoosedpic(ui->radioButton_40,query,4);
//    ui->text10->setText(query.value(2).toString());
//    ui->radioButton_37->setText(query.value(3).toString());
//    ui->radioButton_38->setText(query.value(4).toString());
//    ui->radioButton_39->setText(query.value(5).toString());
//    ui->radioButton_40->setText(query.value(6).toString());


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
    ui->lcdNumber->display(300);

}

Test::~Test()
{
    timer->stop();
    delete ui;
}

void Test::setquestionpic(QLabel*& q,QSqlQuery& query)
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

void Test::setchoosedpic(QRadioButton*& q,QSqlQuery& query,int a)
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

void Test::closeEvent(QCloseEvent *event)
{
    if(!panduan && eachdanyuan[nowchapter] >= 10){
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

void Test::onTimerOut()//自动提交
{
    testtime++;
    if(testtime >= 300){
        timer->stop();
        on_pushButton_clicked();
    }
    else ui->lcdNumber->display(300-testtime);
}

void Test::on_pushButton_clicked()//提交
{
    timer->stop();
    QString Num =QString::number(studentnumber);
    qDebug () << "the" + Num + "upload the answer";
    int A[20] = {0};
    QButtonGroup thechoosed[10];
    //thechoosed.// = new QButtonGroup(this);
    thechoosed[0].addButton(ui->radioButton_1, 1);
    thechoosed[0].addButton(ui->radioButton_2, 2);
    thechoosed[0].addButton(ui->radioButton_3, 3);
    thechoosed[0].addButton(ui->radioButton_4, 4);
    //A[0] = thechoosed[0].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[1].addButton(ui->radioButton_5, 1);
    thechoosed[1].addButton(ui->radioButton_6, 2);
    thechoosed[1].addButton(ui->radioButton_7, 3);
    thechoosed[1].addButton(ui->radioButton_8, 4);
    //ui->radioButton11->setChecked(true);
    //A[1] = thechoosed[1].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[2].addButton(ui->radioButton_9, 1);
    thechoosed[2].addButton(ui->radioButton_10, 2);
    thechoosed[2].addButton(ui->radioButton_11, 3);
    thechoosed[2].addButton(ui->radioButton_12, 4);
    //ui->radioButton11->setChecked(true);
    //A[2] = thechoosed[2].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[3].addButton(ui->radioButton_13, 1);
    thechoosed[3].addButton(ui->radioButton_14, 2);
    thechoosed[3].addButton(ui->radioButton_15, 3);
    thechoosed[3].addButton(ui->radioButton_16, 4);
    //ui->radioButton11->setChecked(true);
    //A[3] = thechoosed[3].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[4].addButton(ui->radioButton_17, 1);
    thechoosed[4].addButton(ui->radioButton_18, 2);
    thechoosed[4].addButton(ui->radioButton_19, 3);
    thechoosed[4].addButton(ui->radioButton_20, 4);
    //ui->radioButton11->setChecked(true);
    //A[4] = thechoosed[4].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[5].addButton(ui->radioButton_21, 1);
    thechoosed[5].addButton(ui->radioButton_22, 2);
    thechoosed[5].addButton(ui->radioButton_23, 3);
    thechoosed[5].addButton(ui->radioButton_24, 4);
    //ui->radioButton11->setChecked(true);
    //A[5] = thechoosed[5].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[6].addButton(ui->radioButton_25, 1);
    thechoosed[6].addButton(ui->radioButton_26, 2);
    thechoosed[6].addButton(ui->radioButton_27, 3);
    thechoosed[6].addButton(ui->radioButton_28, 4);
    //ui->radioButton11->setChecked(true);
   // A[6] = thechoosed[6].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[7].addButton(ui->radioButton_29, 1);
    thechoosed[7].addButton(ui->radioButton_30, 2);
    thechoosed[7].addButton(ui->radioButton_31, 3);
    thechoosed[7].addButton(ui->radioButton_32, 4);
    //ui->radioButton11->setChecked(true);
   // A[7] = thechoosed[7].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[8].addButton(ui->radioButton_33, 1);
    thechoosed[8].addButton(ui->radioButton_34, 2);
    thechoosed[8].addButton(ui->radioButton_35, 3);
    thechoosed[8].addButton(ui->radioButton_36, 4);
    //ui->radioButton11->setChecked(true);
    //A[8] = thechoosed[8].checkedId();
    //thechoosed = new QButtonGroup(this);
    thechoosed[9].addButton(ui->radioButton_37, 1);
    thechoosed[9].addButton(ui->radioButton_38, 2);
    thechoosed[9].addButton(ui->radioButton_39, 3);
    thechoosed[9].addButton(ui->radioButton_40, 4);
    //ui->radioButton11->setChecked(true);
    //A[9] = thechoosed[9].checkedId();

    for(int i = 0; i < 10; i++){
        A[i] = thechoosed[i].checkedId();
    }

    //对比数据库中各题的答案
    int score = 0;

    int tmpsum = 0;
    for(int i = 0; i < nowchapter; i++)
        tmpsum += eachdanyuan[i];


    QSqlQuery query;
    query = QSqlQuery(db);
    query.exec("select * from problem where danyuan = " + QString::number(nowchapter+1));
    for(int i = 0; i < 10; i++){
        query.seek(a[i] );//小a是题目，大A是学生选择的答案
        qDebug() << query.value(1) << query.value(7) << " a = " << a[i] << " A = " << A[i];
        if(query.value(7) == A[i])
            score++;
    }
    qDebug() << "the score is " << score;

    QSqlQuery query2;
    query2 = QSqlQuery(db);
    QString Now = QString::number(nowchapter + 1);
    QString Score = QString::number(score);
    QString tmp = "update student" + QString::number(nowclassindex) + " set A" + Now + " = " + Score + " where number = " + Num;//首字母大写为QString型
    query2.exec(tmp);
    QMessageBox q (QMessageBox::NoIcon,QString("已完成"),
                   QString("你的得分是: "+Score),
                   QMessageBox::Yes,NULL);
    changemessagebox(q);
    q.exec();
    panduan=1;
    this->close();
}
