/*
 * File ReactiveActions.h in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef NOANTICIPATION_ACTIONS_H
#define NOANTICIPATION_ACTIONS_H

#include "Action.h"
#include "IAgent.h"

namespace NoAnticipation {
class Follow : public Divisaction::Action {
 public:
  Follow(std::weak_ptr<Divisaction::IAgent> agent);
};

class LongWalk : public Divisaction::Action {
 public:
  LongWalk();
};

class ThrowBall : public Divisaction::Action {
 public:
  ThrowBall();
};
}

#endif  // NOANTICIPATION_ACTIONS_H
