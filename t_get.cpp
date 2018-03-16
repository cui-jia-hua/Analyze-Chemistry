#include "t_get.h"
#include "ui_t_get.h"
#include "variate.h"
#include "createconnect.h"

t_Get::t_Get(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::t_Get)
{
    ui->setupUi(this);
    changebutton(ui->pushButton,QString(":/image/picture/新修改按钮-蓝色.png"));
    changebutton(ui->pushButton_2,QString(":/image/picture/新修改按钮-蓝色.png"));
    changebutton(ui->pushButton_3,QString(":/image/picture/新修改按钮-蓝色.png"));
    changebutton(ui->pushButton_4,QString(":/image/picture/新修改按钮-蓝色.png"));
    ui->pushButton->setFixedSize(250,100);
    ui->pushButton_2->setFixedSize(250,100);
    ui->pushButton_3->setFixedSize(250,100);
    ui->pushButton_4->setFixedSize(250,100);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    /*
        //设置风格
        QFile qssfile(":/style/style/style.qss");
        qssfile.open(QFile::ReadOnly);
        QString qss;
        qss = qssfile.readAll();
        this->setStyleSheet(qss);
    */

    if (!createConnection(db))
        qDebug() << "warning 1";
    QSqlQuery query(db);
    QString tmp = "select questionnumber from pro";
    query.exec(tmp);totalquestionnumber = 0;chapternumber=0;
    while(query.next()){
        eachdanyuan[chapternumber] = query.value(0).toInt();
        totalquestionnumber += eachdanyuan[chapternumber];
        chapternumber++;
    }
    //提供班级选项
    tmp = "select * from class order by number asc";
    query.exec(tmp);
    while(query.next()){
        ui->comboBox->addItem(query.value(0).toString());
    }


}

t_Get::~t_Get()
{
    delete ui;
}

void t_Get::on_pushButton_clicked()//导出成绩单
{
    createConnection(db);
    QSqlQuery query(db);
    QString text = ui->comboBox->currentText();
    QString tmp = "select number from class where classname = \'"+text+"\'";
    qDebug()<<tmp;
    query.exec(tmp);query.next();
    int index = query.value(0).toInt();
    qDebug()<<index;

    QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                   QString("是否按照班级导出成绩单？"),
                   QMessageBox::Yes|QMessageBox::No,NULL);
    changemessagebox(q);

    if(q.exec() == QMessageBox::No){//按照专业导出成绩单
        QAxObject *excel = new QAxObject(this);
        excel->setControl("Excel.Application");//连接Excel控件
        excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
        excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示

        QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合

        QString path = QFileDialog::getSaveFileName(NULL,"Save files",".","Excel File(*.xlsx)");
        if(path == ""){
            QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                           QString("未选择路径"),
                           QMessageBox::Yes,NULL);
            changemessagebox(q);
            q.exec();
            return;
        }
        qDebug() << path;
        //QString path = QCoreApplication::applicationDirPath()+"/students/" +"score.xlsx";
        QFile file(path);
        if(!file.exists())
        {
          workbooks->dynamicCall("Add");
          QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
          workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(path));
         // workbooks->dynamicCall("Open(const QString&)", QString(QCoreApplication::applicationDirPath()+"/students/" +"score.xlsx"));//打开一个工作簿
        }
        workbooks->dynamicCall("Open(const QString&)", QDir::toNativeSeparators(path));//打开一个工作簿

        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
        QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
        QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//获取工作表集合的工作表1，即sheet1
        QAxObject *cell1,*cell2,*cell3,*cell4[13];
        //列表标题
        QString xuehao="A"+QString::number(1);//设置要操作的单元格，如A1
        QString name="B"+QString::number(1);
        QString stuclass="C"+QString::number(1);
        QString Y[13];
        char t = 'D';
        for(int i = 0; i < 13; i++){
            char T = t+i;
            Y[i]=QString(T)+QString::number(1);
        }

        cell1 = worksheet->querySubObject("Range(QVariant, QVariant)",xuehao);//获取单元格
        cell2 = worksheet->querySubObject("Range(QVariant, QVariant)",name);
        cell3 = worksheet->querySubObject("Range(QVariant, QVariant)",stuclass);
        for(int i = 0; i < 13; i++)  cell4[i] = worksheet->querySubObject("Range(QVariant, QVariant)",Y[i]);

        cell1->dynamicCall("SetValue(const QVariant&)",QVariant("学号"));//设置单元格的值
        cell2->dynamicCall("SetValue(const QVariant&)",QVariant("姓名"));
        cell3->dynamicCall("SetValue(const QVariant&)",QVariant("班级"));
        for(int i = 0; i < 12; i++){
            int I = i+1;
            cell4[i]->dynamicCall("SetValue(const QVariant&)",QVariant("第"+QString::number(I)+"章"));
        }
        cell4[12]->dynamicCall("SetValue(const QVraiant&)",QVariant("期末测试"));
        QString tmp = "select * from student"+QString::number(index);

        //成绩导入
        query.exec(tmp);
        for(int i=0;query.next();i++){
            QString xuehao="A"+QString::number(i+2);//设置要操作的单元格，如A1
            QString name="B"+QString::number(i+2);
            QString stuclass="C"+QString::number(i+2);
            QString Y[13];
            char t = 'D';
            for(int j = 0; j < 13; j++){
                char T = t+j;
                Y[j]=QString(T)+QString::number(i+2);
            }
            cell1 = worksheet->querySubObject("Range(QVariant, QVariant)",xuehao);//获取单元格
            cell2 = worksheet->querySubObject("Range(QVariant, QVariant)",name);
            cell3 = worksheet->querySubObject("Range(QVariant, QVariant)",stuclass);
            for(int j = 0; j < 13; j++)  cell4[j] = worksheet->querySubObject("Range(QVariant, QVariant)",Y[j]);

            cell1->dynamicCall("SetValue(const QVariant&)",QVariant(query.value(0).toInt()));//设置单元格的值
            cell2->dynamicCall("SetValue(const QVariant&)",QVariant(query.value(14).toString()));//姓名
            cell3->dynamicCall("SetValue(const QVariant&)",QVariant(query.value(13).toString()));//班级
            for(int i = 0; i < 12; i++){
                cell4[i]->dynamicCall("SetValue(const QVariant&)",QVariant(query.value(i+1).toInt()));
            }
            cell4[12]->dynamicCall("SetValue(const QVariant&)",QVariant(query.value(15).toInt()));//期末测试
        }


        workbook->dynamicCall("Save()");//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
        //qDebug() << filepath;
        workbook->dynamicCall("Close()");//关闭工作簿
        excel->dynamicCall("Quit()");//关闭excel
        delete excel;
        excel=NULL;
        QMessageBox q (QMessageBox::NoIcon,QString("已完成"),
                       QString("已导出到"+path),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }
    else{//按照班级导出成绩单
        QAxObject *excel = new QAxObject(this);
        excel->setControl("Excel.Application");//连接Excel控件
        excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
        excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示

        QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合

        QString path = QFileDialog::getSaveFileName(NULL,"Save files",".","Excel File(*.xlsx)");
        if(path == ""){
            QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                           QString("未选择路径"),
                           QMessageBox::Yes,NULL);
            changemessagebox(q);
            q.exec();
            return;
        }
        QFile file(path);
        if(!file.exists())
        {
          workbooks->dynamicCall("Add");
          QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
          workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(path));
         // workbooks->dynamicCall("Open(const QString&)", QString(QCoreApplication::applicationDirPath()+"/students/" +"score.xlsx"));//打开一个工作簿
        }
        workbooks->dynamicCall("Open(const QString&)", QDir::toNativeSeparators(path));//打开一个工作簿

        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
        QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
        QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//获取工作表集合的工作表1，即sheet1
        QAxObject *cell1,*cell2,*cell3,*cell4[13];
        //列表标题
        QString xuehao="A"+QString::number(1);//设置要操作的单元格，如A1
        QString name="B"+QString::number(1);
        QString stuclass="C"+QString::number(1);
        QString Y[13];
        char t = 'D';
        for(int i = 0; i < 13; i++){
            char T = t+i;
            Y[i]=QString(T)+QString::number(1);
        }

        cell1 = worksheet->querySubObject("Range(QVariant, QVariant)",xuehao);//获取单元格
        cell2 = worksheet->querySubObject("Range(QVariant, QVariant)",name);
        cell3 = worksheet->querySubObject("Range(QVariant, QVariant)",stuclass);
        for(int i = 0; i < 13; i++)  cell4[i] = worksheet->querySubObject("Range(QVariant, QVariant)",Y[i]);

        cell1->dynamicCall("SetValue(const QVariant&)",QVariant("学号"));//设置单元格的值
        cell2->dynamicCall("SetValue(const QVariant&)",QVariant("姓名"));
        cell3->dynamicCall("SetValue(const QVariant&)",QVariant("班级"));
        for(int i = 0; i < 12; i++){
            int I = i+1;
            cell4[i]->dynamicCall("SetValue(const QVariant&)",QVariant("第"+QString::number(I)+"章"));
        }
        cell4[12]->dynamicCall("SetValue(const QVariant&)",QVariant("期末测试"));

        QString classname = QInputDialog::getText(NULL,QString("请输入班级名"),QString("请输入班级名"));
        QString tmp = "select * from student"+QString::number(index)+" where class = \""+classname+"\"";

        //成绩导入
        query.exec(tmp);
        for(int i=0;query.next();i++){
            qDebug()<<query.lastError();
            QString xuehao="A"+QString::number(i+2);//设置要操作的单元格，如A1
            QString name="B"+QString::number(i+2);
            QString stuclass="C"+QString::number(i+2);
            QString Y[13];
            char t = 'D';
            for(int j = 0; j < 13; j++){
                char T = t+j;
                Y[j]=QString(T)+QString::number(i+2);
            }
            cell1 = worksheet->querySubObject("Range(QVariant, QVariant)",xuehao);//获取单元格
            cell2 = worksheet->querySubObject("Range(QVariant, QVariant)",name);
            cell3 = worksheet->querySubObject("Range(QVariant, QVariant)",stuclass);
            for(int j = 0; j < 13; j++)  cell4[j] = worksheet->querySubObject("Range(QVariant, QVariant)",Y[j]);

            cell1->dynamicCall("SetValue(const QVariant&)",QVariant(query.value(0).toInt()));//设置单元格的值
            cell2->dynamicCall("SetValue(const QVariant&)",QVariant(query.value(14).toString()));
            cell3->dynamicCall("SetValue(const QVariant&)",QVariant(query.value(13).toString()));
            for(int i = 0; i < 12; i++){
                cell4[i]->dynamicCall("SetValue(const QVariant&)",QVariant(query.value(i+1).toInt()));
            }
            cell4[12]->dynamicCall("SetValue(const QVariant&)",QVariant(query.value(15).toInt()));
        }
        workbook->dynamicCall("Save()");//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
        workbook->dynamicCall("Close()");//关闭工作簿
        excel->dynamicCall("Quit()");//关闭excel
        delete excel;
        excel=NULL;
        QMessageBox q (QMessageBox::NoIcon,QString("已完成"),
                       QString("已导出到"+path),
                       QMessageBox::Yes,NULL);
        changemessagebox(q);
        q.exec();
    }
}

void t_Get::on_pushButton_2_clicked()//导入学生名单
{
    createConnection(db);
    QSqlQuery query(db);
    QString text = ui->comboBox->currentText();
    QString tmp = "select number from class where classname = \'"+text+"\'";
    qDebug()<<tmp;
    query.exec(tmp);query.next();
    int index = query.value(0).toInt();
    qDebug()<<index;

    QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                   QString("是否导入学生名单（将清空所有学生成绩）！请确认前三列分别为学号、姓名、班级"),
                   QMessageBox::Yes|QMessageBox::No,NULL);
    changemessagebox(q);

    if(q.exec() == QMessageBox::Yes && index != -1){

        QString fileName;QStringList fileNameList;
        QFileDialog* fd = new QFileDialog(this);//创建对话框
        fd->resize(240,320);    //设置显示的大小
        fd->setNameFilter(QString("表格(*.xls *.xlsx)"));
        fd->setViewMode(QFileDialog::Detail);  //设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
        if (fd->exec() == QDialog::Accepted )   //如果成功的执行
        {
            fileNameList = fd->selectedFiles();    //返回文件列表的名称
            fileName = fileNameList[0];            //取第一个文件名

                QAxObject *excel = NULL;
                QAxObject *workbooks = NULL;
                QAxObject *workbook = NULL;
                excel = new QAxObject("Excel.Application");
                if (!excel)  {
                    qDebug() << "EXCEL对象丢失!";
                }
                excel->dynamicCall("SetVisible(bool)", false);
                workbooks = excel->querySubObject("WorkBooks");

                qDebug()<<fileName;
                workbooks->dynamicCall("Open(const QString&)",QDir::toNativeSeparators(fileName));
                workbook = excel->querySubObject("ActiveWorkBook");
                QAxObject * worksheet = workbook->querySubObject("WorkSheets(int)", 1);//打开第一个sheet
                QAxObject * usedrange = worksheet->querySubObject("UsedRange");//获取该sheet的使用范围对象
                QAxObject * rows = usedrange->querySubObject("Rows");
                QAxObject * columns = usedrange->querySubObject("Columns");
                int intRows = rows->property("Count").toInt();
                int intCols = columns->property("Count").toInt();
                qDebug() << "xls行数："<<intRows;
                qDebug() << "xls列数："<<intCols;

                createConnection(db);
                QSqlQuery query(db);
                QString tmp = "drop table student"+QString::number(index);
                query.exec(tmp);
                tmp = "CREATE TABLE student"+QString::number(index)+" (number INT PRIMARY KEY,A1 INT,A2 INT,A3 INT,A4 INT,A5 INT,A6 INT,A7 INT,A8 INT,A9 INT,A10 INT,A11 INT,A12 INT,class TEXT,name TEXT,final INT);";
                query.exec(tmp);

                // 批量载入数据，这里默认读取A1:C最后
                QVariantList Range;
                Range << QString("A1") << QString("C" +QString::number(intRows));
                QAxObject *allEnvData = worksheet->querySubObject("Range(QVariant,QVariant)", Range);
                QVariant allEnvDataQVariant = allEnvData->dynamicCall("Value2()");
                QVariantList allEnvDataList = allEnvDataQVariant.toList();

                //qDebug() << Range << allEnvDataQVariant;
                for(int i=0; i< intRows; i++){
                    QVariantList allEnvDataList_i =  allEnvDataList[i].toList() ;
                    //qDebug()<< allEnvDataList_i[0].toString()<< allEnvDataList_i[1].toString()<< allEnvDataList_i[2].toString();

                    tmp = "insert into student"+QString::number(index)+" (number,name,class) values (" +QString::number(allEnvDataList_i[0].toInt())+",\""+allEnvDataList_i[1].toString()+"\",\""+allEnvDataList_i[2].toString()+"\")";
                    query.exec(tmp);
                    qDebug()<<query.lastError();
                }

                tmp = "update class set totalnumber = "+QString::number(intRows)+" where number = "+QString::number(index);
                query.exec(tmp);
                QMessageBox q (QMessageBox::NoIcon,QString("完成"),
                               QString("已经成功导入学生名单。"),
                               QMessageBox::Yes,NULL);
                changemessagebox(q);
                q.exec();

                workbook->dynamicCall( "Close(Boolen)", false); // 关闭文件
                excel->dynamicCall( "Quit(void)" );              // 退出

            }

        else{
            QMessageBox q (QMessageBox::NoIcon,QString("警告"),
                           QString("未选择文件！"),
                           QMessageBox::Yes,NULL);
            changemessagebox(q);
            q.exec();
        }

    }
}

void t_Get::on_pushButton_3_clicked()
{
    emit display(3);
}

void t_Get::on_pushButton_4_clicked()//查询
{

    createConnection(db);
    QSqlQuery query(db);
    QString text = ui->comboBox->currentText();
    QString tmp = "select number from class where classname = \'"+text+"\'";
    query.exec(tmp);query.next();
    int index = query.value(0).toInt();

    totalstudentnumber = 0;//学生总数
    if (!createConnection(db))
        qDebug() << "warning 132";
    tmp = "select * from student"+QString::number(index);
    query.exec(tmp);
    while(query.next()) totalstudentnumber++;

    ui->tableWidget->setColumnCount(16);
    ui->tableWidget->setRowCount(totalstudentnumber);

    QStringList headers;
    headers << tr("学号") << tr("姓名") << tr("班级");
    for(int i = 0; i < 12; i ++){
        QString tmp = "第"+QString::number(i+1) + "章";
        headers << tmp;
    }
    QString ttmp = "期末测试";headers << ttmp;
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    query.exec(tmp);query.next();
    for(int i = 0; i < totalstudentnumber; i++){
        QString score[12];
        QString number = query.value(0).toString();
        QString banji = query.value(13).toString();
        QString name = query.value(14).toString();
        for(int k = 1; k <13; k++) score[k-1] = query.value(k).toString();
        QString final = query.value(15).toString();

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(number));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(banji));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(name));
        for(int j = 3; j < 15; j++) ui->tableWidget->setItem(i,j,new QTableWidgetItem(score[j-3]));
        ui->tableWidget->setItem(i,15,new QTableWidgetItem(final));
        query.next();
    }
}
