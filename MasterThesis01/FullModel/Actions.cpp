/*
 * File Actions.cpp in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "Actions.h"
#include "Extra/TTimeProgressiveStage.h"

using namespace std;
using namespace ThreeMotion;

Follow::Follow(std::weak_ptr<TIAgent> agent) : TAction() {
  this->setName("Follow");

  if (auto agentshr = agent.lock()) {
    auto anticipation = make_shared<TTimeProgressiveStage>(
        string("starts to follow " + agentshr->name), 4000, 10000);
    this->SetStage(TStageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

    auto finished = make_shared<TTimeProgressiveStage>(
        string("reaches " + agentshr->name), 4000, 7000);
    this->SetStage(TStageType::FOLLOW_THROUGH, finished);

    auto cancel = make_shared<TTimeProgressiveStage>(
        string("stopped following " + agentshr->name + " abruptly"), 1000,
        3000);
    this->SetStage(TStageType::CANCEL, cancel);
  }
}

LongWalk::LongWalk() : TAction() {
  this->setName("Long Walk");

  auto anticipation = make_shared<TTimeProgressiveStage>(
      string("starts crossing the bridge"), 4000, 10000);
  this->SetStage(TStageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

  auto finished = make_shared<TTimeProgressiveStage>(
      string("nears the end of the bridge"), 4000, 7000);
  this->SetStage(TStageType::FOLLOW_THROUGH, finished);

  auto cancel = make_shared<TTimeProgressiveStage>(
      string("stopped walking abruptly before reaching the end of the bridge"),
      1000, 3000);
  this->SetStage(TStageType::CANCEL, cancel);
}

ThrowBall::ThrowBall() {
  this->setName("Throw Ball");

  auto anticipation = make_shared<TTimeProgressiveStage>(
      string("starts swinging his arm to throw the ball"), 1000, 2000);
  this->SetStage(TStageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

  auto execution =
      make_shared<TTimeProgressiveStage>(string("throws the ball"), 1000, 5000);
  this->SetStage(TStageType::ANTICIPATION_UNINTERRUPTIBLE, execution);

  auto finished = make_shared<TTimeProgressiveStage>(
      string("sees the ball hit the target"), 1000, 1000);
  this->SetStage(TStageType::FOLLOW_THROUGH, finished);

  auto cancel = make_shared<TTimeProgressiveStage>(
      string("stops his swing and doesn't throw the ball"), 1000, 1000);
  this->SetStage(TStageType::CANCEL, cancel);
}
