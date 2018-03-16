#include "t_regist.h"
#include "ui_t_regist.h"
#include "widget.h"
#include "createconnect.h"
#include "variate.h"

t_Regist::t_Regist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::t_Regist)
{
    ui->setupUi(this);
    if (!createConnection(db))
        qDebug() << "warning 1";
}

t_Regist::~t_Regist()
{
    delete ui;
}

void t_Regist::on_pushButton_clicked()
{
    //注册
    QSqlQuery query;
    query = QSqlQuery(db);

    QString s = ui->lineEdit->text();
    QString tmp = "select * from teacher where username = \"" + s + "\"";
    query.exec(tmp);
    if(!query.next()){
        if(ui->lineEdit_2->text() == ui->lineEdit_3->text()){
            QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                           QString("是否确定注册"),
                           QMessageBox::Yes|QMessageBox::No,NULL);
            changemessagebox(q);

            if(q.exec() == QMessageBox::Yes){
                QString ss =  ui->lineEdit_2->text();
                tmp = "insert into teacher values ( '" + s + "', '" + ss + "' );";
                query.exec(tmp);
                QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                               QString("已经成功注册"),
                               QMessageBox::Yes,NULL);
                changemessagebox(q);
                q.exec();
            }
            else{
                QMessageBox q (QMessageBox::NoIcon,QString("取消"),
                               QString("已经取消注册"),
                               QMessageBox::Yes,NULL);
                changemessagebox(q);
                q.exec();
            }
        }
        else{
            QMessageBox q (QMessageBox::NoIcon,QString("请重新确认密码"),
                           QString("密码与确认密码不符"),
                           QMessageBox::Yes,NULL);
            changemessagebox(q);
            q.exec();
        }
    }
    else{
        QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                       QString("用户名已存在"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }
}

void t_Regist::on_pushButton_2_clicked()
{
    //删除
    QSqlQuery query;
    query = QSqlQuery(db);

    QString s = ui->lineEdit->text();
    QString tmp = "select * from teacher where username = \"" + s + "\"";
    query.exec(tmp);
    if(query.next()){
        QString a = query.value(1).toString();
        QString s1 = ui->lineEdit_2->text();
        QString s2 = ui->lineEdit_3->text();
        if(s1 == s2 && s2 == a){
            QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                           QString("是否确定删除用户"),
                           QMessageBox::Yes|QMessageBox::No,NULL);
            changemessagebox(q);
            if(q.exec() == QMessageBox::Yes){
                tmp = "delete from teacher where username = '" + s + "';";
                query.exec(tmp);
                QMessageBox q (QMessageBox::NoIcon,QString("完成！"),
                               QString("已经成功删除。"),
                               QMessageBox::Yes,NULL);
                changemessagebox(q);
                q.exec();
            }
            else{
                QMessageBox q (QMessageBox::NoIcon,QString("取消"),
                               QString("已经取消删除。"),
                               QMessageBox::Yes,NULL);
                changemessagebox(q);
                q.exec();
            }
        }
        else{
            QMessageBox q (QMessageBox::NoIcon,QString("密码不正确"),
                           QString("密码不正确！"),
                           QMessageBox::Yes,NULL);
            changemessagebox(q);
            q.exec();
        }
    }
    else{
        QMessageBox q (QMessageBox::NoIcon,QString("用户名不存在！"),
                       QString("用户名不存在！"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }
}

void t_Regist::on_pushButton_3_clicked()
{
    emit display(3);
}
