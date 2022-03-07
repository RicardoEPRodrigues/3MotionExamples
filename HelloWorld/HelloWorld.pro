#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T18:37:27
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloWorld
TEMPLATE = app


SOURCES += source/main.cpp\
    source/worldholder.cpp \
    source/logviewwindow.cpp \
    ../shared/source/actionprogress.cpp \
    ../shared/source/qthelper.cpp \

HEADERS  += \
    source/worldholder.h \
    source/logviewwindow.h \
    ../shared/source/actionprogress.h \
    ../shared/source/qthelper.h \

FORMS    += \
    ui/logviewwindow.ui \
    ../shared/ui/actionprogress.ui \

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
