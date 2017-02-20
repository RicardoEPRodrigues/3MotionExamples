/*
 * Copyright (C) ricardo 2016 - All Rights Reserved
 */

#include "worldholder.h"

#include "logviewwindow.h"
#include <QApplication>
#include <QFile>

using namespace Divisaction;

void setStyle(QApplication& a) {
  QFile file(":/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());
  file.close();
  a.setStyleSheet(styleSheet);
}

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  setStyle(a);

  auto worldManager = WorldHolder::CreateWorld();

  LogViewWindow w;
  w.init(worldManager);
  w.show();

  const int retval = a.exec();

  // Shutdown functions

  return retval;
}
