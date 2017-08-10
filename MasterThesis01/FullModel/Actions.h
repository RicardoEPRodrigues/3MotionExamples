/*
 * File Actions.h in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef ACTIONS_H
#define ACTIONS_H

#include "DAction.h"
#include "DIAgent.h"

class Follow : public Divisaction::DAction {
 public:
  Follow(std::weak_ptr<Divisaction::DIAgent> agent);
};

class LongWalk : public Divisaction::DAction {
 public:
  LongWalk();
};

class ThrowBall : public Divisaction::DAction {
 public:
  ThrowBall();
};

#endif  // ACTIONS_H
