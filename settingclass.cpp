#include "settingclass.h"
#include "ui_settingclass.h"
#include "variate.h"
#include "createconnect.h"

SettingClass::SettingClass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingClass)
{
    ui->setupUi(this);
    changebutton(ui->pushButton,QString(":/image/picture/新修改按钮-蓝色.png"));
    changebutton(ui->pushButton_2,QString(":/image/picture/新修改按钮-蓝色.png"));
    changebutton(ui->pushButton_3,QString(":/image/picture/新修改按钮-蓝色.png"));
    changebutton(ui->pushButton_4,QString(":/image/picture/新修改按钮-蓝色.png"));
    changebutton(ui->updatestuscore,QString(":/image/picture/新修改按钮-蓝色.png"));
    ui->classnames->setEditTriggers(QAbstractItemView::NoEditTriggers);

    refresh();
}

SettingClass::~SettingClass()
{
    delete ui;
}

void SettingClass::refresh()
{
    if(!createConnection(db)) qDebug()<<"warning settingclass ";
    QSqlQuery query(db);
    QString tmp = "select * from class";
    query.exec(tmp);
    int totalclassnumber = 0;
    while(query.next()){
        totalclassnumber++;
    }

    ui->classnames->setColumnCount(2);
    ui->classnames->setRowCount(totalclassnumber);
    QStringList headers;
    headers << tr("专业名称") << tr("专业人数");
    ui->classnames->setHorizontalHeaderLabels(headers);

    query.exec(tmp);int i = 0;
    while(query.next()){
        QString name = query.value(0).toString();
        QString number = query.value(2).toString();
        ui->classnames->setItem(i,0,new QTableWidgetItem(name));
        ui->classnames->setItem(i++,1,new QTableWidgetItem(number));
    }
    //更新同学某章成绩
    tmp = "select * from class order by number asc";
    query.exec(tmp);
    while(query.next()){
        ui->comboBox_class->addItem(query.value(0).toString());
    }
    tmp = "select * from pro order by chapterindex asc";
    query.exec(tmp);
    while(query.next()){
        ui->comboBox_chapter->addItem(query.value(1).toString());
    }
}

void SettingClass::on_pushButton_clicked()//新建
{

    QString text = ui->classname->text();
    QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                   QString("是否新建专业？ "+text),
                   QMessageBox::Yes|QMessageBox::No,NULL);
    changemessagebox(q);
    if(q.exec() == QMessageBox::Yes){
        createConnection(db);
        QSqlQuery query(db);
        //更新class表中的数据
        QString tmp = "insert into class (classname) values (\'" + text +"\')";
        qDebug()<<tmp;
        query.exec(tmp);
        //qDebug() << query.lastError();
        tmp = "select number from class where classname = \'"+text+"\'";
        query.exec(tmp);query.next();
        QString newclassname = "student"+query.value(0).toString();
        //qDebug()<<newclassname;
        //添加一个新的表
        QString createtable = "CREATE TABLE "+newclassname +" ("+
               "number INT  PRIMARY KEY," +
                "A1     INT,"+
                "A2     INT,"+
                "A3     INT,"+
                "A4     INT,"+
                "A5     INT,"+
                "A6     INT,"+
                "A7     INT,"+
                "A8     INT,"+
                "A9     INT,"+
                "A10     INT,"+
                "A11     INT,"+
                "A12     INT,"+
                "class  TEXT,"+
                "name   TEXT,"+
                "final  INT"+
            ");";
        query.exec(createtable);
        refresh();
        QMessageBox q (QMessageBox::NoIcon,QString("完成"),
                       QString("已新建专业 "+text),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }
    else{
        QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                       QString("已取消"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }

}

void SettingClass::on_pushButton_4_clicked()//返回
{
    emit display(3);
}

void SettingClass::on_pushButton_2_clicked()//改名
{
    QString newclassname = ui->classname->text();
    QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                   QString("是否修改专业名为 "+newclassname),
                   QMessageBox::Yes|QMessageBox::No,NULL);
    changemessagebox(q);
    if(q.exec() == QMessageBox::Yes){
        int nowrow = ui->classnames->currentRow();//从零开始，什么都不选默认是零
        if(!createConnection(db)) qDebug()<<"warning settingclass 2";
        QSqlQuery query(db);
        QString tmp = "select * from class";
        query.exec(tmp);int i = 0;int index = 0;
        while(query.next()){
            if(i == nowrow){
                index = query.value(1).toInt();
                tmp = "update class set classname = \""+newclassname+"\" where number = "+QString::number(index);

                query.exec(tmp);
                qDebug()<<query.lastError()<<tmp;
                break;
            }
            i++;
        }

        refresh();
        QMessageBox q (QMessageBox::NoIcon,QString("完成"),
                       QString("已完成"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }
    else{
        QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                       QString("已取消"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }

}

void SettingClass::on_pushButton_3_clicked()//删除
{

    int nowrow = ui->classnames->currentRow();//从零开始，什么都不选默认是零
    QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                   QString("是否删除第"+QString::number(nowrow+1)+"个专业？"),
                   QMessageBox::Yes|QMessageBox::No,NULL);
    changemessagebox(q);
    if(q.exec() == QMessageBox::Yes)
    {
        if(!createConnection(db)) qDebug()<<"warning setting class 2";
        QSqlQuery query(db);
        QString tmp = "select * from class";
        query.exec(tmp);int i = 0;int index = 0;
        while(query.next()){
            if(i == nowrow){
                index = query.value(1).toInt();
                tmp = "drop table student"+QString::number(index);

                query.exec(tmp);
                qDebug()<<query.lastError();
                break;
            }
            i++;
        }
        tmp = "delete from class where number = "+QString::number(index);
        query.exec(tmp);
        refresh();
        QMessageBox q (QMessageBox::NoIcon,QString("完成"),
                       QString("已删除"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }
    else{
        QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                       QString("已取消"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }



}

void SettingClass::on_updatestuscore_clicked()
{
    QString stunumber_str = ui->lineEdit->text();
    int stunumber = stunumber_str.toInt();
    QString classtext = ui->comboBox_class->currentText();
    QString chaptertext = ui->comboBox_chapter->currentText();
    QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                   QString("是否删除"+stunumber_str+"的"+chaptertext+"成绩?"),
                   QMessageBox::Yes|QMessageBox::No,NULL);
    changemessagebox(q);
    if(q.exec() == QMessageBox::Yes){

        QSqlQuery query(db);
        QString tmp = "select number from class where classname = \'"+classtext+"\'";
        query.exec(tmp);query.next();
        int index_class = query.value(0).toInt();
        tmp = "select chapterindex from pro where chaptername = \'"+chaptertext+"\'";
        query.exec(tmp);query.next();
        int index_chapter = query.value(0).toInt();
        qDebug()<<index_class << index_chapter;
        tmp = "update student" + QString::number(index_class) +" set A" +QString::number(index_chapter) + " = NULL where number = "+QString::number(stunumber);
        query.exec(tmp);
        qDebug() << tmp;
        qDebug()<<query.lastError();
        QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                       QString("已删除"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }else{
        QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                       QString("已取消"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }

}
