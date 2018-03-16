#ifndef T_TEST_H
#define T_TEST_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <string>
#include <QList>
#include <qDebug>
#include <QObject>
#include <Qstring>
#include <QTreeWidgetItem>
#include <QRegExp>
#include <QStackedWidget>
#include <QBuffer>

namespace Ui {
class T_Test;
}

class T_Test : public QWidget
{
    Q_OBJECT

public:
    explicit T_Test(QWidget *parent = 0);
    ~T_Test();

signals:
    void display(int number);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::T_Test *ui;
    QList<QTreeWidgetItem*> imagelist;
    void refresh();
    bool ismatch(QString);

};

#endif // T_TEST_H
