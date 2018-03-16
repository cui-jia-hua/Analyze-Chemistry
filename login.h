#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <Qstring>
#include <string>
#include <qDebug>
#include <QMessageBox>
#include <QDir>
#include <QCloseEvent>

class Test;
class Finaltest;

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Login *ui;
    Test *test;
    Finaltest *finaltest;
    int findnumber(int );

};


#endif // LOGIN_H
