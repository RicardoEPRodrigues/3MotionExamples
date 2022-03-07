/*
 * File Actions.h in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef ACTIONS_H
#define ACTIONS_H

#include "TAction.h"
#include "TIAgent.h"

class Follow : public ThreeMotion::TAction {
 public:
  Follow(std::weak_ptr<ThreeMotion::TIAgent> agent);
};

class LongWalk : public ThreeMotion::TAction {
 public:
  LongWalk();
};

class ThrowBall : public ThreeMotion::TAction {
 public:
  ThrowBall();
};

#endif  // ACTIONS_H
