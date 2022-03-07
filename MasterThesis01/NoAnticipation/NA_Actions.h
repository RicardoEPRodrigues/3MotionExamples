/*
 * File ReactiveActions.h in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef NOANTICIPATION_ACTIONS_H
#define NOANTICIPATION_ACTIONS_H

#include "TAction.h"
#include "TIAgent.h"

namespace NoAnticipation {
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
}

#endif  // NOANTICIPATION_ACTIONS_H
