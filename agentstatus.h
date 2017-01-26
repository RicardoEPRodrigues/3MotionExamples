/*
 * Copyright (C) ricardo 2016 - All Rights Reserved
 */
#ifndef AGENTSTATUS_H
#define AGENTSTATUS_H

#include "qthelper.h"

#include "divisactionwidget.h"

#include "Divisaction.h"
#include "DivisactionExtras.h"

namespace Ui {
    class AgentStatus;
}

class AgentStatus : public DivisactionWidget
{
    Q_OBJECT

public:
    explicit AgentStatus(QWidget *parent = 0);
    ~AgentStatus();

    void set(std::shared_ptr<Divisaction::IAgent>& agent);

    void update(std::vector<std::shared_ptr<Divisaction::Event>> events);
private:
    Ui::AgentStatus *ui;

    std::shared_ptr<Divisaction::Agent> agent;
    std::shared_ptr<Divisaction::TimeProgressiveStage> action;
    std::shared_ptr<Divisaction::TimeProgressiveStage> emotion;
};

#endif // AGENTSTATUS_H
