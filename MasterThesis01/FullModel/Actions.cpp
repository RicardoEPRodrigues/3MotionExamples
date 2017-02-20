/*
 * File Actions.cpp in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "Actions.h"
#include "Extra/TimeProgressiveStage.h"

using namespace std;
using namespace Divisaction;

Follow::Follow(std::weak_ptr<IAgent> agent) : Action() {
  this->setName("Follow");

  if (auto agentshr = agent.lock()) {
    auto anticipation = make_shared<TimeProgressiveStage>(
        string("starts to follow " + agentshr->name), 4000, 10000);
    this->setStage(StageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

    auto finished = make_shared<TimeProgressiveStage>(
        string("reaches " + agentshr->name), 4000, 7000);
    this->setStage(StageType::FOLLOW_THROUGH, finished);

    auto cancel = make_shared<TimeProgressiveStage>(
        string("stopped following " + agentshr->name + " abruptly"), 1000,
        3000);
    this->setStage(StageType::CANCEL, cancel);
  }
}

LongWalk::LongWalk() : Action() {
  this->setName("Long Walk");

  auto anticipation = make_shared<TimeProgressiveStage>(
      string("starts crossing the bridge"), 4000, 10000);
  this->setStage(StageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

  auto finished = make_shared<TimeProgressiveStage>(
      string("nears the end of the bridge"), 4000, 7000);
  this->setStage(StageType::FOLLOW_THROUGH, finished);

  auto cancel = make_shared<TimeProgressiveStage>(
      string("stopped walking abruptly before reaching the end of the bridge"),
      1000, 3000);
  this->setStage(StageType::CANCEL, cancel);
}

ThrowBall::ThrowBall() {
  this->setName("Throw Ball");

  auto anticipation = make_shared<TimeProgressiveStage>(
      string("starts swinging his arm to throw the ball"), 1000, 2000);
  this->setStage(StageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

  auto execution =
      make_shared<TimeProgressiveStage>(string("throws the ball"), 1000, 5000);
  this->setStage(StageType::ANTICIPATION_UNINTERRUPTIBLE, execution);

  auto finished = make_shared<TimeProgressiveStage>(
      string("sees the ball hit the target"), 1000, 1000);
  this->setStage(StageType::FOLLOW_THROUGH, finished);

  auto cancel = make_shared<TimeProgressiveStage>(
      string("stops his swing and doesn't throw the ball"), 1000, 1000);
  this->setStage(StageType::CANCEL, cancel);
}
