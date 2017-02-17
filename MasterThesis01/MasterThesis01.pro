#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T18:37:27
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MasterThesis01
TEMPLATE = app


SOURCES += main.cpp\
    actionprogress.cpp \
    qthelper.cpp \
    logviewwindow.cpp \
    worldholder.cpp

HEADERS  += \
    actionprogress.h \
    qthelper.h \
    logviewwindow.h \
    worldholder.h

FORMS    += \
    actionprogress.ui \
    logviewwindow.ui \

qmakeforce.target = dummy
qmakeforce.commands = rm -f Makefile ##to force rerun of qmake
qmakeforce.depends = FORCE
PRE_TARGETDEPS += $$qmakeforce.target
QMAKE_EXTRA_TARGETS += qmakeforce

unix:!macx: LIBS += -L$$PWD/../../Divisaction/cmake-build-debug/ -lDivisaction

INCLUDEPATH += $$PWD/../../Divisaction/
DEPENDPATH += $$PWD/../../Divisaction/

RESOURCES += \
    style.qrc

DISTFILES += \
    style.css
