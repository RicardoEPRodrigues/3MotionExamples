/*
 * Copyright (C) ricardo 2016 - All Rights Reserved
 */

#include "logviewwindow.h"
#include "ui_logviewwindow.h"

//#include "agentviewwindow.h"

using namespace Divisaction;
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
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateWorld()));
    Time::update();
    updateTimer->start(20);
}

LogViewWindow::~LogViewWindow() {
    delete ui;
    scrollbar = nullptr;
}

void LogViewWindow::init(std::shared_ptr<Divisaction::WorldManager>& worldManager) {
    this->worldManager = worldManager;
    this->pause();
    if (this->worldManager) {

    QLabel *descriptionLabel = new QLabel();
    descriptionLabel->setText(
        QString::fromStdString(worldManager->description));
    descriptionLabel->setAlignment(Qt::AlignCenter);
    ui->ActionStackLayout->addWidget(descriptionLabel);
    }
}

void LogViewWindow::restart() {
    if (worldManager) {
        worldManager = nullptr;
    }
    QtHelper::clearLayout(ui->ActionStackLayout);
    this->actionsProgress.clear();

    init(worldManager);
}

void LogViewWindow::updateWorld() {
    Time::update();
    if (worldManager && !paused) {
        worldManager->update();

        this->updateProgress();
    }
}

struct ActionProgress_stage_equal {
    const std::shared_ptr<Stage> to_find;

    bool operator()(const ActionProgress *other) const {
        return other->stage == to_find;
    }
};

void LogViewWindow::updateProgress() {
    if (worldManager) {
//        for (shared_ptr<IAgent> iagent : worldManager->getAgents()) {
//            shared_ptr<Agent> agent = dynamic_pointer_cast<Agent>(iagent);
//            if (agent) {
//                shared_ptr<Action> action = dynamic_pointer_cast<Action>(
//                    agent->getMentalState()->self.action);
//                if (action) {
//                    auto stage = action->getCurrentStage();

//                    auto it = std::find_if(actionsProgress.begin(),
//                                           actionsProgress.end(),
//                                           ActionProgress_stage_equal{stage});
//                    if (it == actionsProgress.end()) {
//                        ActionProgress *actionProgress = new ActionProgress();
//                        actionProgress->set(iagent, stage);
//                        ui->ActionStackLayout->addWidget(actionProgress);
//                        actionsProgress.push_back(actionProgress);
//                    }
//                }

//                //                shared_ptr<Emotion> emotion =
//                //                dynamic_pointer_cast<Emotion>(agent->getMentalState()->self.emotion);
//                //                if (emotion) {
//                //                    auto stage = emotion->getStage();

//                //                    auto it = actionsProgress.find(stage);
//                //                    if (it == actionsProgress.end()) {
//                //                        ActionProgress * actionProgress = new
//                //                        ActionProgress();
//                //                        actionProgress->set(iagent, stage);
//                //                        ui->ActionStackLayout->addWidget(actionProgress);
//                //                        actionsProgress[stage] =
//                //                        actionProgress;
//                //                    }
//                //                }
//            }
//        }
        for (shared_ptr<Event> event : worldManager->events) {
            shared_ptr<EmotionEvent> emotionEvent =
                dynamic_pointer_cast<EmotionEvent>(event);
            if (emotionEvent) {
                shared_ptr<Emotion> emotion = emotionEvent->emotion;
                if (shared_ptr<IAgent> replyAgent =
                        emotion->getReplyAgent().lock()) {
                    for (std::vector<ActionProgress *>::reverse_iterator
                             progress = actionsProgress.rbegin();
                         progress != actionsProgress.rend(); progress++) {
                        if ((*progress)->agent == replyAgent) {
                            (*progress)->addReply(event);
                            break;
                        }
                    }
                } else {
                    if (shared_ptr<IAgent> sender =
                            emotionEvent->sender.lock()) {
                        for (std::vector<ActionProgress *>::reverse_iterator
                                 progress = actionsProgress.rbegin();
                             progress != actionsProgress.rend(); progress++) {
                            if ((*progress)->agent == sender) {
                                (*progress)->addEmotion(emotion);
                                break;
                            }
                        }
                    }
                }
            } else {
                shared_ptr<ActionEvent> actionEvent =
                    dynamic_pointer_cast<ActionEvent>(event);
                if (actionEvent) {

                    if (auto iagent = actionEvent->sender.lock()) {
                        auto stage = actionEvent->action->getCurrentStage();
                        ActionProgress *actionProgress = new ActionProgress();
                        actionProgress->set(iagent, stage);
                        ui->ActionStackLayout->addWidget(actionProgress);
                        actionsProgress.push_back(actionProgress);
                    }
                }
            }
        }

        for (auto it = actionsProgress.begin(); it != actionsProgress.end();
             ++it) {
            (*it)->update();
        }
    }
}

void LogViewWindow::play() {
    if (worldManager) {
        ui->playPauseButton->setText("Pause (space)");
        paused = false;
    }
}

void LogViewWindow::pause() {
    if (worldManager) {
        ui->playPauseButton->setText("Play (space)");
        paused = true;
    }
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

void LogViewWindow::on_actionAction_View_triggered() {
//    (new AgentViewWindow())->show();
//    updateTimer->stop();
//    this->hide();
}

void LogViewWindow::on_actionRestart_triggered() { restart(); }
