/*
 * Copyright (C) ricardo 2016 - All Rights Reserved
 */

#ifndef ACTIONPROGRESS_H
#define ACTIONPROGRESS_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

#include <math.h>

#include "qthelper.h"

#include "DAgent.h"
#include "DStage.h"
#include "DEvent.h"
#include "Extra/DTimeProgressiveStage.h"

namespace Ui {
    class ActionProgress;
}

class ActionProgress : public QWidget
{
    Q_OBJECT
private:

    std::vector<ActionProgress*> replies;

    QGraphicsOpacityEffect* opacity;
    QPropertyAnimation* animationOpacity;

    Ui::ActionProgress *ui;

    void setReply(std::shared_ptr<Divisaction::DIAgent>& agent, std::shared_ptr<Divisaction::DEmotionEvent> reply);

    int previousWasEqualCounter; // Helper variable to determine if progress bar should be disabled
    int previousWasEqualMax;
public:
    explicit ActionProgress(QWidget *parent = 0);
    ~ActionProgress();


    void set(std::shared_ptr<Divisaction::DIAgent>& agent, std::shared_ptr<Divisaction::DStage> stage);

    void addEmotion(std::shared_ptr<Divisaction::DEmotion> emotion);

    void concatDescription(QString text);

    void addReply(std::shared_ptr<Divisaction::DEvent> reply);

    void update();

    std::shared_ptr<Divisaction::DIAgent> agent;
    std::shared_ptr<Divisaction::DTimeProgressiveStage> stage;

};

#endif // ACTIONPROGRESS_H
