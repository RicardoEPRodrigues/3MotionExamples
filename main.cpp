/*
 * Copyright (C) ricardo 2016 - All Rights Reserved
 */

#include "Divisaction.h"
#include "DivisactionExtras.h"
#include "Extra/Examples.h"

#include "logviewwindow.h"
//#include "agentviewwindow.h"
#include <QApplication>
#include <QFile>

void setStyle(QApplication& a) {
    QFile file(":/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    a.setStyleSheet(styleSheet);
}


std::shared_ptr<class Divisaction::WorldManager> worldManager;

void setWorldManager() {
    worldManager = Divisaction::Examples::exampleCoop();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setStyle(a);

    setWorldManager();

    LogViewWindow w;

    w.init(worldManager);
//    AgentViewWindow w;
    w.show();

    const int retval = a.exec();

    //Shutdown functions

    return retval;
}
