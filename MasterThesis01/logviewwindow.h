/*
 * Copyright (C) ricardo 2016 - All Rights Reserved
 */

#ifndef DIVISACTIONWINDOW_H
#define DIVISACTIONWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QScrollArea>
#include <QScrollBar>
#include <QShortcut>
#include <QTimer>

#include <memory>
#include <vector>

#include "actionprogress.h"

#include "Divisaction.h"

namespace Ui {
class LogViewWindow;
}

class LogViewWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit LogViewWindow(QWidget* parent = 0);
  ~LogViewWindow();

  void init(std::shared_ptr<Divisaction::WorldManager> worldManager);

 private:
  Ui::LogViewWindow* ui;
  QScrollBar* scrollbar;

  std::vector<ActionProgress*> actionsProgress;

  std::shared_ptr<Divisaction::WorldManager> worldManager;

  QTimer* updateTimer;

  void restart();

  void play();
  void pause();
  bool paused;
 private slots:
  void update();
  void moveScrollBarToBottom(int min, int max);
  void on_playPauseButton_clicked();
  void on_actionExit_triggered();
  void on_actionRestart_triggered();
};

#endif  // DIVISACTIONWINDOW_H
