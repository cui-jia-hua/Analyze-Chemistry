#ifndef START_H
#define START_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QIcon>
#include <QBitmap>


namespace Ui {
class Start;
}

class Start : public QWidget
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = 0);
    ~Start();

signals:
    void display(int number);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Start *ui;

};


#endif // START_H
