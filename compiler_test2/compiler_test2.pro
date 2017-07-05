#-------------------------------------------------
#
# Project created by QtCreator 2016-12-11T13:48:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = compiler_test2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lexical.cpp \
    syntax.cpp \
    s_table.cpp \
    quaternion.cpp \
    target.cpp

HEADERS  += mainwindow.h \
    lexical.h \
    lexical_analyse.h \
    syntax_analyse.h \
    syntax.h \
    s_table.h \
    quaternion.h \
    cal_quat.h \
    target.h \
    target_code.h

FORMS    += mainwindow.ui \
    lexical.ui \
    syntax.ui \
    s_table.ui \
    quaternion.ui \
    target.ui

RESOURCES += \
    compiler_image.qrc
