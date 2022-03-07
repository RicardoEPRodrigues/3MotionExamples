/*
 * Copyright (C) ricardo 2016 - All Rights Reserved
 */

#include "actionprogress.h"
#include "ui_actionprogress.h"

using namespace std;
using namespace ThreeMotion;

ActionProgress::ActionProgress(QWidget *parent)
    : QWidget(parent), ui(new Ui::ActionProgress) {
    ui->setupUi(this);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);

    opacity = new QGraphicsOpacityEffect;
    animationOpacity = new QPropertyAnimation(opacity, "opacity");
    ui->actionProgressHolder->setGraphicsEffect(opacity);

    animationOpacity->setDuration(500);
    animationOpacity->setStartValue(0.0);
    animationOpacity->setEndValue(1.0);
    animationOpacity->setEasingCurve(QEasingCurve::InCubic);
    animationOpacity->start();

    ui->repliesHolder->setVisible(false);

    ui->progressBar->setProperty("disabled", false);

    previousWasEqualMax = 10;
    previousWasEqualCounter = 0;
}

ActionProgress::~ActionProgress() {
    delete ui;
    delete animationOpacity;
    delete opacity;
}

void ActionProgress::set(shared_ptr<TIAgent> &agent, shared_ptr<TStage> stage) {
    this->stage = std::dynamic_pointer_cast<TTimeProgressiveStage>(stage);
    this->agent = agent;
    if (this->stage) {
        concatDescription(QString(this->stage->getName().c_str()));
        ui->progressBar->setValue(floor(this->stage->GetProgress() * 100));
    }
}

void ActionProgress::update() {
    if (this->stage) {
        int progress = int(this->stage->GetProgress() * 100);
        if (progress > ui->progressBar->value()) {
            ui->progressBar->setValue(progress);
            if (ui->progressBar->property("disabled") == true) {
                QtHelper::setProperty(ui->progressBar, "disabled", false);
            }
            previousWasEqualCounter = 0;
        } else if (previousWasEqualCounter >= previousWasEqualMax) {
            if (progress > 1) {
                if (ui->progressBar->property("disabled") == false) {
                    QtHelper::setProperty(ui->progressBar, "disabled", true);
                }
            }
        } else {
            previousWasEqualCounter++;
        }
    }
    if (this->replies.size() > 0) {
        if (!this->ui->repliesHolder->isVisible()) {
            this->ui->repliesHolder->setVisible(true);
        }
        for (ActionProgress *reply : replies) {
            reply->update();
        }
    }
}

void ActionProgress::addEmotion(std::shared_ptr<TEmotion> emotion) {
    if (emotion) {
        concatDescription(QString(emotion->stage->getName().c_str()));
    }
}

void ActionProgress::concatDescription(QString text) {
    if (this->ui->Description->text().length() > 0) {
        this->ui->Description->setText(this->ui->Description->text() + " " +
                                       QString(agent->name.c_str()) + " " +
                                       text + ".");
    } else {
        this->ui->Description->setText(QString(agent->name.c_str()) + " " +
                                       text + ".");
    }
}

void ActionProgress::addReply(shared_ptr<TEvent> reply) {
    shared_ptr<TEmotionEvent> emotionEvent =
        dynamic_pointer_cast<TEmotionEvent>(reply);
    if (emotionEvent) {
        if (auto sender = emotionEvent->sender.lock()) {
            ActionProgress *actionProgress = new ActionProgress(this);
            actionProgress->setReply(sender, emotionEvent);
            this->replies.push_back(actionProgress);
            this->ui->replies->addWidget(actionProgress);
        }
    }
}

void ActionProgress::setReply(std::shared_ptr<TIAgent> &agent,
                              std::shared_ptr<TEmotionEvent> reply) {
    this->agent = agent;
    if (auto origin = reply->emotion->replyToAgent.lock()) {
        concatDescription(QString(reply->emotion->replyText.c_str()) +
                          QString(origin->name.c_str()));
    }
    this->set(agent, reply->emotion->stage);
}
