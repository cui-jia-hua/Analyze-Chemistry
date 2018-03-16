#include "widget.h"
#include "start.h"
#include "login.h"
#include "test.h"
#include "t_login.h"
#include "t_test.h"
#include "t_total.h"
#include "t_get.h"
#include "t_regist.h"
#include "t_addpro.h"
#include "createconnect.h"
#include "settingchapter.h"
#include "variate.h"
#include "settingclass.h"
#include <QStackedLayout>
#include <QPushButton>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    //this->setFixedSize(1100, 700);
    start = new Start;
    login = new Login;
    t_login = new T_Login;
    t_test = new T_Test;
    myt_total = new t_total;
    t_get = new t_Get;
    t_regist = new t_Regist;
    stackLayout = new QStackedLayout;
    t_addpro = new t_Addpro;
    settingchapter = new SettingChapter;
    settingclass = new SettingClass;

    stackLayout->addWidget(start);// 0
    stackLayout->addWidget(login);// 1
    stackLayout->addWidget(t_login);// 2
    stackLayout->addWidget(myt_total);// 3
    stackLayout->addWidget(t_test);//4
    stackLayout->addWidget(t_regist);//5
    stackLayout->addWidget(t_get);// 6
    stackLayout->addWidget(t_addpro);// 7
    stackLayout->addWidget(settingchapter);//8
    stackLayout->addWidget(settingclass);//9

    connect(start, &Start::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(t_login,&T_Login::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(t_test,&T_Test::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(myt_total,&t_total::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(t_get,&t_Get::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(t_addpro,&t_Addpro::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(t_regist,&t_Regist::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(settingchapter,&SettingChapter::display, stackLayout, &QStackedLayout::setCurrentIndex);
    connect(settingclass,&SettingClass::display, stackLayout, &QStackedLayout::setCurrentIndex);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(stackLayout);
    setLayout(mainLayout);
}

Widget::~Widget()
{

}

void Widget::closeEvent(QCloseEvent *event)
{
    QMessageBox q (QMessageBox::NoIcon,QString("退出程序"),
                   QString("警告：是否退出?"),
                   QMessageBox::Yes| QMessageBox::No ,NULL);
    changemessagebox(q);
    if (q.exec() == QMessageBox::Yes) {
        event->accept();  //接受退出信号，程序退出
    }
    else{
        event->ignore();
    }
}
