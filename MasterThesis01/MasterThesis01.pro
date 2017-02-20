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
    worldholder.cpp \
    FullModel/Actions.cpp \
    FullModel/Emotions.cpp \
    FullModel/Modules/CoopSceneBobDecide.cpp \
    FullModel/Modules/CoopSceneBobReact.cpp \
    FullModel/Modules/CoopSceneHannaDecide.cpp \
    FullModel/Modules/CoopSceneHannaReact.cpp \
    Screening/S_Actions.cpp \
    Screening/Modules/S_CoopSceneBobReact.cpp \
    Screening/Modules/S_CoopSceneHannaReact.cpp \
    NoAnticipation/NA_Actions.cpp \
    NoAnticipation/Modules/NA_CoopSceneHannaReact.cpp \
    NoAnticipation/Modules/NA_CoopSceneBobReact.cpp

HEADERS  += \
    actionprogress.h \
    qthelper.h \
    logviewwindow.h \
    worldholder.h \
    FullModel/Actions.h \
    FullModel/Emotions.h \
    FullModel/Modules/CoopSceneBobDecide.h \
    FullModel/Modules/CoopSceneBobReact.h \
    FullModel/Modules/CoopSceneHannaDecide.h \
    FullModel/Modules/CoopSceneHannaReact.h \
    Screening/S_Actions.h \
    Screening/Modules/S_CoopSceneBobReact.h \
    Screening/Modules/S_CoopSceneHannaReact.h \
    NoAnticipation/NA_Actions.h \
    NoAnticipation/Modules/NA_CoopSceneBobReact.h \
    NoAnticipation/Modules/NA_CoopSceneHannaReact.h

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
