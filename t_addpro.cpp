#include "t_addpro.h"
#include "ui_t_addpro.h"
#include "createconnect.h"
#include "variate.h"
#include "widget.h"

t_Addpro::t_Addpro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::t_Addpro)
{
    ui->setupUi(this);
    changebutton(ui->pushButton,QString(":/image/picture/橙色按钮.png"));
    changebutton(ui->pushButton_2,QString(":/image/picture/橙色按钮.png"));
    changebutton(ui->pushButton_3,QString(":/image/picture/橙色按钮.png"));
    /*
        //设置风格
        QFile qssfile(":/style/style/style.qss");
        qssfile.open(QFile::ReadOnly);
        QString qss;
        qss = qssfile.readAll();
        this->setStyleSheet(qss);
    */
    if(!createConnection(db)) qDebug()<<"warning login";
    QSqlQuery query(db);
    QString tmp = "select * from pro order by chapterindex asc";
    query.exec(tmp);
    while(query.next()){
        ui->comboBox->addItem(query.value(1).toString());
    }
    varPA = varPB = varPC = varPD = varPText = NULL;
    isPText = isPA = isPB = isPC = isPD = false;

}

t_Addpro::~t_Addpro()
{
    delete ui;
}

void t_Addpro::on_pushButton_3_clicked()//添加问题
{
    QString tigan = ui->textEdit->toPlainText();
    QString A = ui->textEdit_2->toPlainText();
    QString B = ui->textEdit_3->toPlainText();
    QString C = ui->textEdit_4->toPlainText();
    QString D = ui->textEdit_5->toPlainText();

    QButtonGroup thechoosed;
    thechoosed.addButton(ui->radioButton, 1);
    thechoosed.addButton(ui->radioButton_2, 2);
    thechoosed.addButton(ui->radioButton_3, 3);
    thechoosed.addButton(ui->radioButton_4, 4);
    int answer = thechoosed.checkedId();

    if(tigan == ""){
        QMessageBox q (QMessageBox::NoIcon,QString("请输入题干"),
                       QString("请输入题干"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }
    else if(A == "" || B == "" || C == "" || D == ""){
        QMessageBox q (QMessageBox::NoIcon,QString("请输入选项"),
                       QString("请输入选项"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }
    else if(answer == -1){
        QMessageBox q (QMessageBox::NoIcon,QString("请选择正确答案"),
                       QString("请选择正确答案"),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }

    else{
        QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                       QString("是否确定添加题目"),
                       QMessageBox::Yes| QMessageBox::No ,NULL);
        changemessagebox(q);

        //QMessageBox::StandardButton warning = QMessageBox::warning(NULL,QString("警告"), "<font size='22' color='red'>"+ QString("是否确定添加题目")+"</font>", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(q.exec() == QMessageBox::Yes){
            int d = ui->comboBox->currentIndex() + 1;//从零开始
            createConnection(db);
            QSqlQuery query(db);
            QString tmp = "insert into problem (danyuan,id,text,A,B,C,D,answer) values(?,?,?,?,?,?,?,?)";
            query.prepare(tmp);
            query.addBindValue(d);
            query.addBindValue(eachdanyuan[d-1]+1);
            query.addBindValue(tigan);
            query.addBindValue(A);
            query.addBindValue(B);
            query.addBindValue(C);
            query.addBindValue(D);
            query.addBindValue(answer);
            query.exec();
            qDebug()<<query.lastError();
            //如果是图片的话，更新存放图片的字段
            if(isPText){
                QSqlQuery query;
                tmp = "update problem set ptext = :value where danyuan = :danyuan and id = :id;";
                query.prepare(tmp);
                query.bindValue(":value", varPText);
                query.bindValue(":danyuan", d);
                query.bindValue(":id",eachdanyuan[d-1]+1);
                query.exec();
                qDebug()<<query.lastError();
            }
            if(isPA){
                QSqlQuery query;
                tmp = "update problem set pA = :value where danyuan = :danyuan and id = :id;";
                query.prepare(tmp);
                query.bindValue(":value", varPA);
                query.bindValue(":danyuan", d);
                query.bindValue(":id",eachdanyuan[d-1]+1);
                query.exec();
                qDebug()<<query.lastError();
            }
            if(isPB){
                QSqlQuery query;
                tmp = "update problem set pB = :value where danyuan = :danyuan and id = :id;";
                query.prepare(tmp);
                query.bindValue(":value", varPB);
                query.bindValue(":danyuan", d);
                query.bindValue(":id",eachdanyuan[d-1]+1);
                query.exec();
                qDebug()<<query.lastError();
            }
            if(isPC){
                QSqlQuery query;
                tmp = "update problem set pC = :value where danyuan = :danyuan and id = :id;";
                query.prepare(tmp);
                query.bindValue(":value", varPC);
                query.bindValue(":danyuan", d);
                query.bindValue(":id",eachdanyuan[d-1]+1);
                query.exec();
                qDebug()<<query.lastError();
            }
            if(isPD){
                QSqlQuery query;
                tmp = "update problem set pD = :value where danyuan = :danyuan and id = :id;";
                query.prepare(tmp);
                query.bindValue(":value", varPD);
                query.bindValue(":danyuan", d);
                query.bindValue(":id",eachdanyuan[d-1]+1);
                query.exec();
                qDebug()<<query.lastError();
            }

            eachdanyuan[d-1]++;
            tmp = "update pro set questionnumber = "+QString::number(eachdanyuan[d-1])+" where chapterindex = "+QString::number(d);
            query.exec(tmp);

            totalquestionnumber = 0;
            for(int i = 0; i < 9; i++)
                totalquestionnumber += eachdanyuan[i];

            QMessageBox q (QMessageBox::NoIcon,QString("添加成功"),
                           QString("添加成功"),
                           QMessageBox::Yes,NULL);
            changemessagebox(q);
            q.exec();
        }
        varPA = varPB = varPC = varPD = varPText = NULL;
        isPText = isPA = isPB = isPC = isPD = false;
        ui->textEdit->clear();ui->textEdit_2->clear();ui->textEdit_3->clear();ui->textEdit_4->clear();ui->textEdit_5->clear();
    }

}

void t_Addpro::on_pushButton_clicked()
{
    emit display(3);
}

void t_Addpro::on_pushButton_2_clicked()//更新章节
{
    ui->comboBox->clear();
    if(!createConnection(db)) qDebug()<<"warning login";
    QSqlQuery query(db);
    QString tmp = "select * from pro order by chapterindex asc";
    query.exec(tmp);
    while(query.next()){
        ui->comboBox->addItem(query.value(1).toString());
    }

}

void t_Addpro::on_insertPtext_clicked()
{
    QString fileName;QStringList fileNameList;
    QFileDialog* fd = new QFileDialog(this);//创建对话框
    fd->resize(240,320);    //设置显示的大小
    fd->setNameFilter(QString("pic(*.jpg *.png *.bmp *.jpeg)"));
    fd->setViewMode(QFileDialog::Detail);  //设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
    if (fd->exec() == QDialog::Accepted )   //如果成功的执行
    {
        fileNameList = fd->selectedFiles();    //返回文件列表的名称
        fileName = fileNameList[0];            //取第一个文件名
        qDebug() << fileName;
        QFile file(fileName);
        QByteArray data;
        file.open(QIODevice::ReadOnly);
        data = file.readAll();
        file.close();
        varPText.setValue(data);
        ui->textEdit->setText(fileName);
        isPText = true;
    }
}

void t_Addpro::on_insertPA_clicked()
{
    QString fileName;QStringList fileNameList;
    QFileDialog* fd = new QFileDialog(this);//创建对话框
    fd->resize(240,320);    //设置显示的大小
    fd->setNameFilter(QString("pic(*.jpg *.png *.bmp *.jpeg)"));
    fd->setViewMode(QFileDialog::Detail);  //设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
    if (fd->exec() == QDialog::Accepted )   //如果成功的执行
    {
        fileNameList = fd->selectedFiles();    //返回文件列表的名称
        fileName = fileNameList[0];            //取第一个文件名
        qDebug() << fileName;
        QFile file(fileName);
        QByteArray data;
        file.open(QIODevice::ReadOnly);
        data = file.readAll();
        file.close();
        varPA.setValue(data);
        ui->textEdit_2->setText(fileName);
        isPA = true;
    }
}

void t_Addpro::on_insertPB_clicked()
{
    QString fileName;QStringList fileNameList;
    QFileDialog* fd = new QFileDialog(this);//创建对话框
    fd->resize(240,320);    //设置显示的大小
    fd->setNameFilter(QString("pic(*.jpg *.png *.bmp *.jpeg)"));
    fd->setViewMode(QFileDialog::Detail);  //设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
    if (fd->exec() == QDialog::Accepted )   //如果成功的执行
    {
        fileNameList = fd->selectedFiles();    //返回文件列表的名称
        fileName = fileNameList[0];            //取第一个文件名
        qDebug() << fileName;
        QFile file(fileName);
        QByteArray data;
        file.open(QIODevice::ReadOnly);
        data = file.readAll();
        file.close();
        varPB.setValue(data);
        ui->textEdit_3->setText(fileName);
        isPB = true;
    }
}

void t_Addpro::on_insertPC_clicked()
{
    QString fileName;QStringList fileNameList;
    QFileDialog* fd = new QFileDialog(this);//创建对话框
    fd->resize(240,320);    //设置显示的大小
    fd->setNameFilter(QString("pic(*.jpg *.png *.bmp *.jpeg)"));
    fd->setViewMode(QFileDialog::Detail);  //设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
    if (fd->exec() == QDialog::Accepted )   //如果成功的执行
    {
        fileNameList = fd->selectedFiles();    //返回文件列表的名称
        fileName = fileNameList[0];            //取第一个文件名
        qDebug() << fileName;
        QFile file(fileName);
        QByteArray data;
        file.open(QIODevice::ReadOnly);
        data = file.readAll();
        file.close();
        varPC.setValue(data);
        ui->textEdit_4->setText(fileName);
        isPC = true;
    }
}

void t_Addpro::on_insertPD_clicked()
{
    QString fileName;QStringList fileNameList;
    QFileDialog* fd = new QFileDialog(this);//创建对话框
    fd->resize(240,320);    //设置显示的大小
    fd->setNameFilter(QString("pic(*.jpg *.png *.bmp *.jpeg)"));
    fd->setViewMode(QFileDialog::Detail);  //设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
    if (fd->exec() == QDialog::Accepted )   //如果成功的执行
    {
        fileNameList = fd->selectedFiles();    //返回文件列表的名称
        fileName = fileNameList[0];            //取第一个文件名
        qDebug() << fileName;
        QFile file(fileName);
        QByteArray data;
        file.open(QIODevice::ReadOnly);
        data = file.readAll();
        file.close();
        varPD.setValue(data);
        ui->textEdit_5->setText(fileName);
        isPD = true;
    }
}
