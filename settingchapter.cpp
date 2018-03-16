#include "settingchapter.h"
#include "ui_settingchapter.h"
#include "createconnect.h"
#include "variate.h"

SettingChapter::SettingChapter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingChapter)
{
    ui->setupUi(this);
    changebutton(ui->pushButton,QString(":/image/picture/新修改按钮-蓝色.png"));
    changebutton(ui->pushButton_2,QString(":/image/picture/新修改按钮-蓝色.png"));
    changebutton(ui->pushButton_3,QString(":/image/picture/新修改按钮-蓝色.png"));
    changebutton(ui->pushButton_4,QString(":/image/picture/新修改按钮-蓝色.png"));
    ui->chapternames->setEditTriggers(QAbstractItemView::NoEditTriggers);
    refresh();
}

SettingChapter::~SettingChapter()
{
    delete ui;
}

void SettingChapter::refresh(){

    ui->chapternames->setColumnCount(2);
    ui->chapternames->setRowCount(chapternumber);
    QStringList headers;
    headers << tr("章节名称") << tr("题目数量");
    ui->chapternames->setHorizontalHeaderLabels(headers);

    if(!createConnection(db)) qDebug()<<"warning settingchapter";
    QSqlQuery query(db);
    QString tmp = "select * from pro";
    query.exec(tmp);int i=0;
    while(query.next()){
        QString name = query.value(1).toString();
        QString number = query.value(2).toString();
        ui->chapternames->setItem(i,0,new QTableWidgetItem(name));
        ui->chapternames->setItem(i,1,new QTableWidgetItem(number));
        i++;
    }

}

void SettingChapter::on_pushButton_clicked()//添加章节
{
    QString newchaptername = ui->chaptername->text();
    if(newchaptername == ""){
        QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                       QString("请输入章节名"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }
    else{
        if(!createConnection(db)) qDebug()<<"warning settingchapter 1";
        QSqlQuery query(db);QString tmp = "insert into pro (chapterindex,chaptername,questionnumber) values ";
        tmp+="(" + QString::number(++chapternumber) + ",\"" + newchaptername + "\","+ "0)";
        query.exec(tmp);qDebug()<<query.lastError();
        QMessageBox q (QMessageBox::NoIcon,QString("完成"),
                       QString("已添加"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }
    refresh();
}

void SettingChapter::on_pushButton_2_clicked()//修改名字
{
    QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                   QString("是否修改章节名为"+ui->chaptername->text()),
                   QMessageBox::Yes|QMessageBox::No,NULL);
    changemessagebox(q);
    if(q.exec() == QMessageBox::Yes){
        QString newchaptername = ui->chaptername->text();
        int nowrow = ui->chapternames->currentRow();//从零开始，什么都不选默认是零
        if(!createConnection(db)) qDebug()<<"warning setting chapter 2";
        QSqlQuery query(db);
        QString tmp = "update pro set chaptername = \""+newchaptername+"\" where chapterindex = "+QString::number(nowrow+1);
        query.exec(tmp);
        qDebug()<<query.lastError();
        QMessageBox q (QMessageBox::NoIcon,QString("完成"),
                       QString("已修改"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
        refresh();
    }
    else{
        QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                       QString("已取消"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }


}

void SettingChapter::on_pushButton_3_clicked()//删除章节
{
    int nowrow = ui->chapternames->currentRow();//从零开始，什么都不选默认是零
    QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                   QString("是否删除第")+QString::number(nowrow+1)+QString("章"),
                   QMessageBox::Yes|QMessageBox::No,NULL);
    changemessagebox(q);
    if(q.exec() == QMessageBox::Yes){

        if(!createConnection(db)) qDebug()<<"warning setting chapter 2";
        QSqlQuery query(db);
        QString tmp = "delete from pro where chapterindex = "+QString::number(nowrow+1);
        query.exec(tmp);
        tmp="delete from problem where danyuan = "+QString::number(nowrow+1);
        query.exec(tmp);
        tmp = "update pro set chapterindex = chapterindex-1 where chapterindex > "+QString::number(nowrow+1);
        query.exec(tmp);
        tmp = "update problem set danyuan = danyuan-1 where danyuan > "+QString::number(nowrow+1);
        query.exec(tmp);
        chapternumber--;
        for(int i = nowrow;i<chapternumber;i++){
            eachdanyuan[i]=eachdanyuan[i+1];
        }
        totalquestionnumber = 0;
        for(int i = 0; i < chapternumber;i++) totalquestionnumber += eachdanyuan[i];
        QMessageBox q (QMessageBox::NoIcon,QString("完成"),
                       QString("已删除"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
        refresh();
    }
    else{
        QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                       QString("已取消"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }

}

void SettingChapter::on_pushButton_4_clicked()
{
    emit display(3);
}
