#include "widget.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    qDebug() << QDir::currentPath();
    //QApplication::addLibraryPath("./plugins");
    w.setWindowIcon(QIcon("picture/title.png"));
    w.setWindowTitle(QString("分析化学实验测试系统"));

    return a.exec();
}
