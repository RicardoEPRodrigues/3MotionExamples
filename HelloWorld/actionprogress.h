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

#include "TAgent.h"
#include "TStage.h"
#include "TEvent.h"
#include "Extra/TTimeProgressiveStage.h"

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

    void setReply(std::shared_ptr<ThreeMotion::TIAgent>& agent, std::shared_ptr<ThreeMotion::TEmotionEvent> reply);

    int previousWasEqualCounter; // Helper variable to determine if progress bar should be disabled
    int previousWasEqualMax;
public:
    explicit ActionProgress(QWidget *parent = 0);
    ~ActionProgress();


    void set(std::shared_ptr<ThreeMotion::TIAgent>& agent, std::shared_ptr<ThreeMotion::TStage> stage);

    void addEmotion(std::shared_ptr<ThreeMotion::TEmotion> emotion);

    void concatDescription(QString text);

    void addReply(std::shared_ptr<ThreeMotion::TEvent> reply);

    void update();

    std::shared_ptr<ThreeMotion::TIAgent> agent;
    std::shared_ptr<ThreeMotion::TTimeProgressiveStage> stage;

};

#endif // ACTIONPROGRESS_H
