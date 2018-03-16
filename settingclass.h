#ifndef SETTINGCLASS_H
#define SETTINGCLASS_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QInputDialog>


namespace Ui {
class SettingClass;
}

class SettingClass : public QWidget
{
    Q_OBJECT

public:
    explicit SettingClass(QWidget *parent = 0);
    ~SettingClass();

signals:
    void display(int number);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_updatestuscore_clicked();

private:
    Ui::SettingClass *ui;
    void refresh();
};

#endif // SETTINGCLASS_H
