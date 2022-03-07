/*
 * Copyright (C) ricardo 2016 - All Rights Reserved
 */

#include "logviewwindow.h"
#include "ui_logviewwindow.h"

using namespace ThreeMotion;
using namespace std;

LogViewWindow::LogViewWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LogViewWindow) {
  ui->setupUi(this);
  ui->ActionStackLayout->setAlignment(Qt::AlignTop);

  scrollbar = ui->StagesScroll->verticalScrollBar();
  QObject::connect(scrollbar, SIGNAL(rangeChanged(int, int)), this,
                   SLOT(moveScrollBarToBottom(int, int)));

  QShortcut *shortcut = new QShortcut(QKeySequence("SPACE"), this);
  QObject::connect(shortcut, SIGNAL(activated()), this,
                   SLOT(on_playPauseButton_clicked()));

  updateTimer = new QTimer(this);
  connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
  TTime::Update();
  updateTimer->start(20);
}

LogViewWindow::~LogViewWindow() {
  delete ui;
  scrollbar = nullptr;
}

void LogViewWindow::init(WorldHolder::SceneType type) {
  QtHelper::clearLayout(ui->ActionStackLayout);
  actionsProgress.clear();

  sceneType = type;
  worldManager = WorldHolder::CreateWorld(sceneType);

  pause();

  if (worldManager) {
    QLabel *descriptionLabel = new QLabel();
    descriptionLabel->setText(
        QString::fromStdString(worldManager->description));
    descriptionLabel->setAlignment(Qt::AlignCenter);
    ui->ActionStackLayout->addWidget(descriptionLabel);
  }
}

void LogViewWindow::init() { this->init(this->sceneType); }

void LogViewWindow::update() {
  TTime::Update();
  if (worldManager && !paused) {
    worldManager->Update();

    for (shared_ptr<TEvent> event : worldManager->events) {
      shared_ptr<TEmotionEvent> emotionEvent =
          dynamic_pointer_cast<TEmotionEvent>(event);
      if (emotionEvent) {
        shared_ptr<TEmotion> emotion = emotionEvent->emotion;
        if (shared_ptr<TIAgent> replyAgent = emotion->replyToAgent.lock()) {
          for (std::vector<ActionProgress *>::reverse_iterator progress =
                   actionsProgress.rbegin();
               progress != actionsProgress.rend(); progress++) {
            if ((*progress)->agent == replyAgent) {
              (*progress)->addReply(event);
              break;
            }
          }
        } else {
          if (shared_ptr<TIAgent> sender = emotionEvent->sender.lock()) {
            for (std::vector<ActionProgress *>::reverse_iterator progress =
                     actionsProgress.rbegin();
                 progress != actionsProgress.rend(); progress++) {
              if ((*progress)->agent == sender) {
                (*progress)->addEmotion(emotion);
                break;
              }
            }
          }
        }
      } else {
        shared_ptr<TActionEvent> actionEvent =
            dynamic_pointer_cast<TActionEvent>(event);
        if (actionEvent) {
          if (auto iagent = actionEvent->sender.lock()) {
            auto stage = actionEvent->action->GetCurrentStage();
            ActionProgress *actionProgress = new ActionProgress();
            actionProgress->set(iagent, stage);
            ui->ActionStackLayout->addWidget(actionProgress);
            actionsProgress.push_back(actionProgress);
          }
        }
      }
    }

    for (auto it = actionsProgress.begin(); it != actionsProgress.end(); ++it) {
      (*it)->update();
    }
  }
}

void LogViewWindow::play() {
  ui->playPauseButton->setText("Pause (space)");
  paused = false;
}

void LogViewWindow::pause() {
  ui->playPauseButton->setText("Play (space)");
  paused = true;
}

// Utilities

void LogViewWindow::moveScrollBarToBottom(int min, int max) {
  Q_UNUSED(min);
  this->scrollbar->setValue(max); // Moves the scroll bar to the bottom so
                                  // that new stage are seen first.
}

void LogViewWindow::on_playPauseButton_clicked() {
  if (worldManager) {
    if (paused) {
      this->play();
    } else {
      this->pause();
    }
  }
}

void LogViewWindow::on_actionExit_triggered() { QApplication::exit(); }

void LogViewWindow::on_actionRestart_triggered() { init(); }

void LogViewWindow::on_actionFull_Model_triggered() {
  init(WorldHolder::SceneType::FULL_MODEL);
}

void LogViewWindow::on_actionNo_Anticipation_triggered() {

  init(WorldHolder::SceneType::NO_ANTICIPATION);
}

void LogViewWindow::on_actionRandom_triggered() {
  init(WorldHolder::SceneType::SCREENING);
}
