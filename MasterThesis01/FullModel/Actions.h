/*
 * File Actions.h in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef ACTIONS_H
#define ACTIONS_H

#include "Action.h"
#include "IAgent.h"

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

#endif  // ACTIONS_H
