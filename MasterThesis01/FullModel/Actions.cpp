/*
 * File Actions.cpp in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "Actions.h"
#include "Extra/DTimeProgressiveStage.h"

using namespace std;
using namespace Divisaction;

Follow::Follow(std::weak_ptr<DIAgent> agent) : DAction() {
  this->setName("Follow");

  if (auto agentshr = agent.lock()) {
    auto anticipation = make_shared<DTimeProgressiveStage>(
        string("starts to follow " + agentshr->name), 4000, 10000);
    this->setStage(DStageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

    auto finished = make_shared<DTimeProgressiveStage>(
        string("reaches " + agentshr->name), 4000, 7000);
    this->setStage(DStageType::FOLLOW_THROUGH, finished);

    auto cancel = make_shared<DTimeProgressiveStage>(
        string("stopped following " + agentshr->name + " abruptly"), 1000,
        3000);
    this->setStage(DStageType::CANCEL, cancel);
  }
}

LongWalk::LongWalk() : DAction() {
  this->setName("Long Walk");

  auto anticipation = make_shared<DTimeProgressiveStage>(
      string("starts crossing the bridge"), 4000, 10000);
  this->setStage(DStageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

  auto finished = make_shared<DTimeProgressiveStage>(
      string("nears the end of the bridge"), 4000, 7000);
  this->setStage(DStageType::FOLLOW_THROUGH, finished);

  auto cancel = make_shared<DTimeProgressiveStage>(
      string("stopped walking abruptly before reaching the end of the bridge"),
      1000, 3000);
  this->setStage(DStageType::CANCEL, cancel);
}

ThrowBall::ThrowBall() {
  this->setName("Throw Ball");

  auto anticipation = make_shared<DTimeProgressiveStage>(
      string("starts swinging his arm to throw the ball"), 1000, 2000);
  this->setStage(DStageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

  auto execution =
      make_shared<DTimeProgressiveStage>(string("throws the ball"), 1000, 5000);
  this->setStage(DStageType::ANTICIPATION_UNINTERRUPTIBLE, execution);

  auto finished = make_shared<DTimeProgressiveStage>(
      string("sees the ball hit the target"), 1000, 1000);
  this->setStage(DStageType::FOLLOW_THROUGH, finished);

  auto cancel = make_shared<DTimeProgressiveStage>(
      string("stops his swing and doesn't throw the ball"), 1000, 1000);
  this->setStage(DStageType::CANCEL, cancel);
}
