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

#include "worldholder.h"

#include "Divisaction.h"

namespace Ui {
class LogViewWindow;
}

class LogViewWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit LogViewWindow(QWidget *parent = 0);
  ~LogViewWindow();

  WorldHolder::SceneType sceneType = WorldHolder::SceneType::FULL_MODEL;
  void init();
  void init(WorldHolder::SceneType type);

private:
  Ui::LogViewWindow *ui;
  QScrollBar *scrollbar;

  std::vector<ActionProgress *> actionsProgress;

  std::shared_ptr<Divisaction::DWorldManager> worldManager;

  QTimer *updateTimer;

  void play();
  void pause();
  bool paused;
private slots:
  void update();
  void moveScrollBarToBottom(int min, int max);
  void on_playPauseButton_clicked();
  void on_actionExit_triggered();
  void on_actionRestart_triggered();
  void on_actionFull_Model_triggered();
  void on_actionNo_Anticipation_triggered();
  void on_actionRandom_triggered();
};

#endif // DIVISACTIONWINDOW_H
