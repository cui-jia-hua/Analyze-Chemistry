#ifndef SETTINGCHAPTER_H
#define SETTINGCHAPTER_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class SettingChapter;
}

class SettingChapter : public QWidget
{
    Q_OBJECT

public:
    explicit SettingChapter(QWidget *parent = 0);
    ~SettingChapter();

signals:
    void display(int number);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::SettingChapter *ui;
    void refresh();
};

#endif // SETTINGCHAPTER_H
