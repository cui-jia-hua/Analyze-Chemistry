#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QIcon>
#include <QSqlDatabase>

class Start;
class Login;
class Test;
class Finaltest;
class T_Login;
class t_total;
class t_Get;
class t_Regist;
class T_Test;
class QStackedLayout;
class QVBoxLayout;
class t_Addpro;
class SettingChapter;
class SettingClass;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void closeEvent(QCloseEvent *event);



private:
    Start *start;
    Login *login;
    Test *test;
    T_Login *t_login;
    T_Test *t_test;
    t_total *myt_total;
    t_Get *t_get;
    t_Regist *t_regist;
    t_Addpro *t_addpro;
    SettingChapter *settingchapter;
    SettingClass *settingclass;
    QVBoxLayout *mainLayout;
    QStackedLayout *stackLayout;
};


#endif // WIDGET_H
