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

SOURCES += source/main.cpp\
    source/logviewwindow.cpp \
    source/worldholder.cpp \
    source/FullModel/Actions.cpp \
    source/FullModel/Emotions.cpp \
    source/FullModel/Modules/CoopSceneBobDecide.cpp \
    source/FullModel/Modules/CoopSceneBobReact.cpp \
    source/FullModel/Modules/CoopSceneHannaDecide.cpp \
    source/FullModel/Modules/CoopSceneHannaReact.cpp \
    source/Screening/S_Actions.cpp \
    source/Screening/Modules/S_CoopSceneBobReact.cpp \
    source/Screening/Modules/S_CoopSceneHannaReact.cpp \
    source/NoAnticipation/NA_Actions.cpp \
    source/NoAnticipation/Modules/NA_CoopSceneHannaReact.cpp \
    source/NoAnticipation/Modules/NA_CoopSceneBobReact.cpp \
    ../shared/source/actionprogress.cpp \
    ../shared/source/qthelper.cpp \

HEADERS  += \
    source/logviewwindow.h \
    source/worldholder.h \
    source/FullModel/Actions.h \
    source/FullModel/Emotions.h \
    source/FullModel/Modules/CoopSceneBobDecide.h \
    source/FullModel/Modules/CoopSceneBobReact.h \
    source/FullModel/Modules/CoopSceneHannaDecide.h \
    source/FullModel/Modules/CoopSceneHannaReact.h \
    source/Screening/S_Actions.h \
    source/Screening/Modules/S_CoopSceneBobReact.h \
    source/Screening/Modules/S_CoopSceneHannaReact.h \
    source/NoAnticipation/NA_Actions.h \
    source/NoAnticipation/Modules/NA_CoopSceneBobReact.h \
    source/NoAnticipation/Modules/NA_CoopSceneHannaReact.h \
    ../shared/source/actionprogress.h \
    ../shared/source/qthelper.h

FORMS    += \
    ui/logviewwindow.ui \
    ../shared/ui/actionprogress.ui

qmakeforce.target = dummy
qmakeforce.commands = rm -f Makefile ##to force rerun of qmake
qmakeforce.depends = FORCE
PRE_TARGETDEPS += $$qmakeforce.target
QMAKE_EXTRA_TARGETS += qmakeforce

unix:!macx: LIBS += -L$$PWD/../../3Motion/cmake-build-debug/ -lThreeMotion

INCLUDEPATH += $$PWD/../../3Motion/Source/
DEPENDPATH += $$PWD/../../3Motion/Source/

RESOURCES += \
    ../shared/resources/style.qrc

DISTFILES += \
    ../shared/resources/style.css
