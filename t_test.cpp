#include "t_test.h"
#include "ui_t_test.h"
#include "widget.h"
#include "createconnect.h"
#include "variate.h"

using namespace std;

T_Test::T_Test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::T_Test)
{
    ui->setupUi(this);

    changebutton(ui->pushButton,QString(":/image/picture/橙色按钮.png"));
    changebutton(ui->pushButton_2,QString(":/image/picture/橙色按钮.png"));
    changebutton(ui->pushButton_3,QString(":/image/picture/橙色按钮.png"));
    changebutton(ui->pushButton_4,QString(":/image/picture/橙色按钮.png"));

    /*
        //设置风格
        QFile qssfile(":/style/style/style.qss");
        qssfile.open(QFile::ReadOnly);
        QString qss;
        qss = qssfile.readAll();
        this->setStyleSheet(qss);
    */
    refresh();
}

T_Test::~T_Test()
{
    delete ui;
}

void T_Test::refresh(){
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel(tr("单元"));
    imagelist.clear();
    createConnection(db);
    QSqlQuery query(db);QString tmp = "select * from pro order by chapterindex asc";query.exec(tmp);query.next();
    for(int i = 0; i < chapternumber; i++){
        QTreeWidgetItem *imageItem = new QTreeWidgetItem(ui->treeWidget,QStringList(query.value(1).toString()));
        imagelist.append(imageItem);
        query.next();
    }

    for(int k = 0; k < chapternumber; k++){
        for(int i = 0; i < eachdanyuan[k]; i++){
            QString tmp = QString::number(k+1) + "-" + QString::number(i+1);
            QTreeWidgetItem *imageItem1 = new QTreeWidgetItem(imagelist[k],QStringList(QString(tmp))); //多个子节点
            imagelist[k]->addChild(imageItem1);
        }
    }
}

bool T_Test::ismatch(QString str){

}

void T_Test::on_pushButton_clicked()//查询
{
    if (!createConnection(db))
        qDebug() << "warning 1";
    else{
        QSqlQuery query;
        query = QSqlQuery(db);
        if(!ui->treeWidget->currentItem()){
            QMessageBox q (QMessageBox::NoIcon,QString("错误"),
                           QString("请选择试题"),
                           QMessageBox::Yes,NULL);
            changemessagebox(q);
            q.exec();
        }
        else{
            QString str = ui->treeWidget->currentItem()->text(0);qDebug()<<str;
            QString pattern(QString("(\\d+)[-](\\d+)"));
            QRegExp rx(pattern);
            if (!rx.exactMatch(str))
            {
                QMessageBox q (QMessageBox::NoIcon,QString("错误"),
                               QString("请选择试题"),
                               QMessageBox::Yes,NULL);
                changemessagebox(q);
                q.exec();
            }
            else{
                qDebug()<<rx.cap(0);
                int firstnum = rx.cap(1).toInt();
                int secondnum = rx.cap(2).toInt();
                QString tmp = "select * from problem where danyuan = "  + QString::number(firstnum) + " and id = " + QString::number(secondnum);
                qDebug() << tmp;
                query.exec(tmp);
                query.next();

                ui->textEdit_2->setTextColor("black");
                ui->textEdit_3->setTextColor("black");
                ui->textEdit_4->setTextColor("black");
                ui->textEdit_5->setTextColor("black");

                switch (query.value(7).toInt()) {
                case 1:
                    ui->textEdit_2->setTextColor("red");
                    ui->radioButton->setChecked(true);
                    break;
                case 2:
                    ui->textEdit_3->setTextColor("red");
                    ui->radioButton_2->setChecked(true);
                    break;
                case 3:
                    ui->textEdit_4->setTextColor("red");
                    ui->radioButton_3->setChecked(true);
                    break;
                case 4:
                    ui->textEdit_5->setTextColor("red");
                    ui->radioButton_4->setChecked(true);
                    break;
                default:
                    break;
                }
                ui->textEdit->setText(query.value(2).toString());
                ui->textEdit_2->setText(query.value(3).toString());
                ui->textEdit_3->setText(query.value(4).toString());
                ui->textEdit_4->setText(query.value(5).toString());
                ui->textEdit_5->setText(query.value(6).toString());
                //如果有图片的话
                if(query.value(8).toString() != ""){
                    qDebug()<<query.value(8);
                    ui->stackedWidget->setCurrentIndex(1);
                    QByteArray bta = query.value(8).toByteArray();
                    QPixmap img;img.loadFromData(bta);
                    img = img.scaled(ui->textEdit->width(),ui->textEdit->height());
                    ui->label->setPixmap(img);
                }else{
                    ui->stackedWidget->setCurrentIndex(0);
                }
                //A
                if(query.value(9).toString() != ""){
                    qDebug()<<query.value(9);
                    ui->stackedWidget_2->setCurrentIndex(1);
                    QByteArray bta = query.value(9).toByteArray();
                    QPixmap img;img.loadFromData(bta);
                    img = img.scaled(ui->textEdit_2->width(),ui->textEdit_2->height());
                    ui->label_2->setPixmap(img);
                }else{
                    ui->stackedWidget_2->setCurrentIndex(0);
                }
                //B
                if(query.value(10).toString() != ""){
                    qDebug()<<query.value(10);
                    ui->stackedWidget_3->setCurrentIndex(1);
                    QByteArray bta = query.value(10).toByteArray();
                    QPixmap img;img.loadFromData(bta);
                    img = img.scaled(ui->textEdit_3->width(),ui->textEdit_3->height());
                    ui->label_3->setPixmap(img);
                }else{
                    ui->stackedWidget_3->setCurrentIndex(0);
                }
                //C
                if(query.value(11).toString() != ""){
                    qDebug()<<query.value(11);
                    ui->stackedWidget_4->setCurrentIndex(1);
                    QByteArray bta = query.value(11).toByteArray();
                    QPixmap img;img.loadFromData(bta);
                    img = img.scaled(ui->textEdit_4->width(),ui->textEdit_4->height());
                    ui->label_4->setPixmap(img);
                }else{
                    ui->stackedWidget_4->setCurrentIndex(0);
                }
                //D
                if(query.value(12).toString() != ""){
                    qDebug()<<query.value(12);
                    ui->stackedWidget_5->setCurrentIndex(1);
                    QByteArray bta = query.value(12).toByteArray();
                    QPixmap img;img.loadFromData(bta);
                    img = img.scaled(ui->textEdit_5->width(),ui->textEdit_5->height());
                    ui->label_5->setPixmap(img);
                }else{
                    ui->stackedWidget_5->setCurrentIndex(0);
                }
            }
        }
    }
}

void T_Test::on_pushButton_2_clicked()
{
    emit display(3);
}

void T_Test::on_pushButton_3_clicked()//修改
{
    if (!createConnection(db))
        qDebug() << "warning 1";
    else{
        QSqlQuery query;
        query = QSqlQuery(db);
        if(!ui->treeWidget->currentItem()){
            QMessageBox q (QMessageBox::NoIcon,QString("错误"),
                           QString("请选择试题"),
                           QMessageBox::Yes,NULL);
            changemessagebox(q);
            q.exec();
        }
        else{
            QString str = ui->treeWidget->currentItem()->text(0);qDebug()<<str;
            QString pattern(QString("(\\d+)[-](\\d+)"));
            QRegExp rx(pattern);
            if (!rx.exactMatch(str))
            {
                QMessageBox q (QMessageBox::NoIcon,QString("错误"),
                            QString("请选择试题"),
                            QMessageBox::Yes,NULL);
                changemessagebox(q);
                q.exec();
            }
            else{
                qDebug()<<rx.cap(0);
                int firstnum = rx.cap(1).toInt();
                int secondnum = rx.cap(2).toInt();
                QString tmp = "select * from problem where danyuan = "  + QString::number(firstnum) + " and id = " + QString::number(secondnum);
                qDebug() << tmp;
                query.exec(tmp);
                query.next();

            //确定文字
            QString t0 = ui->textEdit->toPlainText();
            QString t1 = ui->textEdit_2->toPlainText();
            QString t2 = ui->textEdit_3->toPlainText();
            QString t3 = ui->textEdit_4->toPlainText();
            QString t4 = ui->textEdit_5->toPlainText();
            //确定正确选项
            QButtonGroup thechoosed;
            thechoosed.addButton(ui->radioButton, 1);
            thechoosed.addButton(ui->radioButton_2, 2);
            thechoosed.addButton(ui->radioButton_3, 3);
            thechoosed.addButton(ui->radioButton_4, 4);
            int A = thechoosed.checkedId();
            //更改
            if(A == -1){
                QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                               QString("请选择正确答案"),
                               QMessageBox::Yes,NULL);
                changemessagebox(q);
                q.exec();

            }
            else{
                QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                               QString("是否确定修改"),
                               QMessageBox::Yes|QMessageBox::No,NULL);
                changemessagebox(q);

                if(q.exec() == QMessageBox::Yes){
                    QString S = "update problem set text = \"" + t0 + "\" where danyuan = "  + QString::number(firstnum) +" and id = "+QString::number(secondnum);
                    query.exec(S);
                    S = "update problem set A = \"" + t1 + "\" where danyuan = "  + QString::number(firstnum) +" and id = "+QString::number(secondnum);
                    query.exec(S);
                    S = "update problem set B = \"" + t2 + "\" where danyuan = "  + QString::number(firstnum) +" and id = "+QString::number(secondnum);
                    query.exec(S);
                    S = "update problem set C = \"" + t3 + "\" where danyuan = "  + QString::number(firstnum) +" and id = "+QString::number(secondnum);
                    query.exec(S);
                    S = "update problem set D = \"" + t4 + "\" where danyuan = "  + QString::number(firstnum) +" and id = "+QString::number(secondnum);
                    query.exec(S);
                    S = "update problem set answer = " + QString::number(A) + " where danyuan = "  + QString::number(firstnum) +" and id = "+QString::number(secondnum);
                    query.exec(S);

                    QMessageBox q (QMessageBox::NoIcon,QString("修改成功"),
                                   QString("您已成功修改"),
                                   QMessageBox::Yes,NULL);
                    changemessagebox(q);
                    q.exec();
                }
            }
            refresh();
        }

    }

}
}

void T_Test::on_pushButton_4_clicked()//删除
{
    if(!ui->treeWidget->currentItem()){
        QMessageBox q (QMessageBox::NoIcon,QString("错误"),
                       QString("请选择试题"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }
    else{
        QString s = ui->treeWidget->currentItem()->text(0);
        qDebug() << s;
        string ss = s.toStdString();
        if(ss[1] != '-'){
            QMessageBox q (QMessageBox::NoIcon,QString("错误"),
                           QString("请选择试题"),
                           QMessageBox::Yes,NULL);
            changemessagebox(q);
            q.exec();
        }
        else{
            int danyuan,id;
            if(ss.length() == 3){
                danyuan = ss[0] - '0' ;
                id = ss[2] - '0' ;
            }
            else{
                danyuan = ss[0] - '0' ;//danyuan
                id = (ss[2] - '0') * 10 + (ss[3] - '0');//id
            }
            //qDebug() << danyuan << " " << id; + QString::number(danyuan) + "-" + QString::number(id) + " ?")
            QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                           QString("是否确定删除"),
                           QMessageBox::Yes|QMessageBox::No,NULL);
            changemessagebox(q);
            if(q.exec() == QMessageBox::Yes)
            {
                if (!createConnection(db))
                    qDebug() << "warning 1";
                QSqlQuery query;
                query = QSqlQuery(db);
                QString tmp = "delete from problem where danyuan = " + QString::number(danyuan) + " and id = " + QString::number(id);
                query.exec(tmp);

                tmp = "select questionnumber from pro where chapterindex = "+QString::number(danyuan);
                query.exec(tmp);query.next();
                int temp = query.value(0).toInt();
                tmp = "update pro set questionnumber = " + QString::number(temp-1) +" where chapterindex = "+QString::number(danyuan);//改变单元题目数
                query.exec(tmp);eachdanyuan[danyuan-1]--;

                tmp = "update problem set id = id-1 where danyuan = "+QString::number(danyuan)+" and id in (select id from problem where danyuan = " + QString::number(danyuan)  + " and id > "+ QString::number(id)+ ")";//改变题目的id顺序
                qDebug() << tmp;
                query.exec(tmp);

                totalquestionnumber = 0;
                for(int i = 0; i < 9; i++)
                    totalquestionnumber += eachdanyuan[i];
                refresh();
            }
        }
    }
}
