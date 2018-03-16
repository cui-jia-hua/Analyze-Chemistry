#ifndef T_GET_H
#define T_GET_H

#include <QWidget>
#include <QAxObject>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QInputDialog>
#include <QRegExp>

namespace Ui {
class t_Get;
}

class t_Get : public QWidget
{
    Q_OBJECT

public:
    explicit t_Get(QWidget *parent = 0);
    /*//1./打开
    void newExcel(const QString &fileName);
    //2.增加1个Worksheet
    void appendSheet(const QString &sheetName,int cnt);
    //3.向Excel单元格中写入数据
    void setCellValue(int row, int column, const QString &value);
    //4.保存Excel
    void saveExcel(const QString &fileName);
    //5.释放Excel
    void  freeExcel();
*/
    ~t_Get();

signals:
    void display(int number);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::t_Get *ui;
    QAxObject* pApplication;
};

#endif // T_GET_H
