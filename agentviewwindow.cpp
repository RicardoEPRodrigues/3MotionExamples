/*
 * Copyright (C) ricardo 2016 - All Rights Reserved
 */
#include "agentviewwindow.h"
#include "ui_agentviewwindow.h"

#include "logviewwindow.h"

using namespace std;
using namespace Divisaction;

AgentViewWindow::AgentViewWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AgentViewWindow) {
    ui->setupUi(this);

    QShortcut *shortcut = new QShortcut(QKeySequence("SPACE"), this);
    QObject::connect(shortcut, SIGNAL(activated()), this,
                     SLOT(on_playPauseButton_clicked()));

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateWorld()));
    Time::update();
    updateTimer->start(20);
}

AgentViewWindow::~AgentViewWindow() {
    delete ui;
    if (updateTimer) {
        updateTimer->stop();
        delete updateTimer;
    }
}

void AgentViewWindow::init(std::shared_ptr<Divisaction::WorldManager>& worldManager) {
    worldManager = worldManager;
    this->pause();
    if (worldManager) {
        QLabel *descriptionLabel = new QLabel();
        descriptionLabel->setText(QString::fromStdString(worldManager->description));
        descriptionLabel->setAlignment(Qt::AlignCenter);
        ui->gridLayout->addWidget(descriptionLabel, 0, 0, 1, 2);

        for (auto agent : worldManager->agents) {
            AgentStatus *status = new AgentStatus(this);
            status->set(agent);
            agentsStatus.push_back(status);
            ui->gridLayout->addWidget(status);
        }
    }
}

void AgentViewWindow::restart() {
    if (worldManager) {
        worldManager = nullptr;
    }
    QtHelper::clearLayout(ui->gridLayout);
    agentsStatus.clear();

    init(worldManager);
}

void AgentViewWindow::updateWorld() {
    Time::update();
    if (worldManager && !paused) {
        worldManager->update();

        this->updateProgress();
    }
}

void AgentViewWindow::updateProgress() {
    if (worldManager) {
        for (AgentStatus *status : agentsStatus) {
            status->update(worldManager->events);
        }
    }
}

void AgentViewWindow::play() {
    if (worldManager) {
        ui->playPauseButton->setText("Pause (space)");
        Time::play();
        paused = false;
    }
}

void AgentViewWindow::pause() {
    if (worldManager) {
        ui->playPauseButton->setText("Play (space)");
        Time::pause();
        paused = true;
    }
}

void AgentViewWindow::on_playPauseButton_clicked() {
    if (worldManager) {
        if (paused) {
            this->play();
        } else {
            this->pause();
        }
    }
}

void AgentViewWindow::on_actionLog_View_triggered() {
    (new LogViewWindow())->show();
    updateTimer->stop();
    this->hide();
}

void AgentViewWindow::on_actionExit_triggered() { QApplication::exit(); }

void AgentViewWindow::on_actionRestart_triggered() { restart(); }
