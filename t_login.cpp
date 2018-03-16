#include "t_login.h"
#include "ui_t_login.h"
#include "variate.h"
#include "widget.h"
#include "createconnect.h"
using namespace std;

T_Login::T_Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::T_Login)
{
    ui->setupUi(this);
    changebutton(ui->pushButton,QString(":/image/picture/绿色按钮.png"));
    changebutton(ui->pushButton_2,QString(":/image/picture/绿色按钮.png"));
/*
    //设置风格
    QFile qssfile(":/style/style/style.qss");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();
    this->setStyleSheet(qss);
*/
    //设置图标
    QPixmap image ;image.load(":/image/picture/username.png") ;image = image.scaled(21,21);
    ui->lineEdit->setTextMargins(21,0,0,0);
    QLabel *lock = new QLabel(this);
    lock->setMaximumSize(21,21);
    lock->setCursor(QCursor(Qt::ArrowCursor));
    lock->setPixmap(QPixmap(image));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->setContentsMargins(1, 1, 1, 1);
        buttonLayout->addStretch();
        buttonLayout->addWidget(lock);
        buttonLayout->setDirection(QBoxLayout::RightToLeft);
        ui->lineEdit->setLayout(buttonLayout);

    image.load(":/image/picture/password.png") ;image = image.scaled(21,21);
    ui->lineEdit_2->setTextMargins(21,0,0,0);
    QLabel *lock2 = new QLabel(this);
    lock2->setMaximumSize(21,21);
    lock2->setCursor(QCursor(Qt::ArrowCursor));
    lock2->setPixmap(QPixmap(image));

    QSpacerItem *spaceitem2 = new QSpacerItem(150,10,QSizePolicy::Expanding);
    QHBoxLayout *editLayout2 = new QHBoxLayout();
    editLayout2->setContentsMargins(1, 0, 1, 0);
    editLayout2->addWidget(lock2);
    editLayout2->addSpacerItem(spaceitem2);
    ui->lineEdit_2->setLayout(editLayout2);

}

T_Login::~T_Login()
{
    delete ui;
}


void T_Login::on_pushButton_clicked()
{
    QString username = "fenxihuaxue";
    QString password = "00000000";
    int t = 0;
    if(ui->lineEdit->text() != username || ui->lineEdit_2->text() != password){
        if (!createConnection(db))
            qDebug() << "warning t_login";
        QSqlQuery query(db);
        QString tmp = "select * from teacher";
        query.exec(tmp);
        while(query.next()){
            if(query.value(0).toString() == ui->lineEdit->text() && query.value(1).toString() == ui->lineEdit_2->text())
                t = 1;
            qDebug() << query.lastError();
        }

    }
    else t = 1;
    if(t == 1) emit display(3);
    else{
        QMessageBox q (QMessageBox::NoIcon,QString("未找到该用户"),
                       QString("不存在该用户"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }
}

void T_Login::on_pushButton_2_clicked()
{
    emit display(0);
}
