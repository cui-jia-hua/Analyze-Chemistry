#ifndef CREATECONNECT_H
#define CREATECONNECT_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>


static bool createConnection(QSqlDatabase &db)
{
    db.setDatabaseName(".\\data\\text.db");
    if (!db.open()) {
        QMessageBox::warning(NULL, ("error"), db.lastError().text());
        return false;
    }
    qDebug() << "database connect ok";
    return true;
}

static void changemessagebox(QMessageBox &q)
{
    q.setStyleSheet(
        QString("QPushButton {"
                        "background-color:#89AFDE;"
                        " border-style: outset;"
                        " font: bold 32px;"
                        " min-width: 3.5em;"
                        " min-height: 1.7em;"
                        "}"
                 "QLabel { color:red;font:40px;font-family:\"黑体\"}")
    );

    q.setButtonText(QMessageBox::Yes,QString("确定"));
    q.setButtonText(QMessageBox::No,QString("取消"));
}

#endif // CREATECONNECT_H
