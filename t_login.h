#ifndef T_LOGIN_H
#define T_LOGIN_H

#include <QWidget>
#include <Qstring>
#include <string>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QCursor>
#include <QObject>
#include <QHBoxLayout>
#include <QIcon>
#include <QBitmap>

namespace Ui {
class T_Login;
}

class T_Login : public QWidget
{
    Q_OBJECT

public:
    explicit T_Login(QWidget *parent = 0);
    ~T_Login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void display(int number);

private:
    Ui::T_Login *ui;

};

#endif // T_LOGIN_H
