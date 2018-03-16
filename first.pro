#-------------------------------------------------
#
# Project created by QtCreator 2017-04-24T16:13:45
#
#-------------------------------------------------

QT       += core gui sql axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = first
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        widget.cpp \
    start.cpp \
    login.cpp \
    test.cpp \
    t_login.cpp \
    t_test.cpp \
    variate.cpp \
    t_total.cpp \
    t_regist.cpp \
    t_get.cpp \
    finaltest.cpp \
    t_addpro.cpp \
    settingchapter.cpp \
    settingclass.cpp

HEADERS  += widget.h \
    start.h \
    login.h \
    test.h \
    t_login.h \
    t_test.h \
    createconnect.h \
    variate.h \
    t_total.h \
    t_regist.h \
    t_get.h \
    finaltest.h \
    t_addpro.h \
    settingchapter.h \
    settingclass.h

FORMS += \
    start.ui \
    login.ui \
    test.ui \
    t_login.ui \
    t_test.ui \
    t_total.ui \
    t_regist.ui \
    t_get.ui \
    finaltest.ui \
    t_addpro.ui \
    settingchapter.ui \
    settingclass.ui

RESOURCES += \
    pic.qrc

RC_ICONS =title.ico

DISTFILES +=
