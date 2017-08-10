/*
 * File ReactiveActions.cpp in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "NA_Actions.h"
#include "Extra/DTimeProgressiveStage.h"

using namespace std;
using namespace Divisaction;

namespace NoAnticipation {

Follow::Follow(std::weak_ptr<DIAgent> agent) : DAction() {
  this->setName("Follow");

  if (auto agentshr = agent.lock()) {
    auto anticipation = make_shared<DTimeProgressiveStage>(
        string("follows " + agentshr->name), 2000, 7000);
    this->setStage(DStageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

    auto finished = make_shared<DTimeProgressiveStage>(
        string("reaches " + agentshr->name), 2000, 3000);
    this->setStage(DStageType::FOLLOW_THROUGH, finished);

    //            auto cancel = make_shared<TimeProgressiveStage>(
    //                    string("stopped following " + agentshr->getName() + "
    //                    abruptly"), 1000, 3000);
    //            this->setStage(StageType::CANCEL, cancel);
  }
}

LongWalk::LongWalk() : DAction() {
  this->setName("Long Walk");

  auto anticipation = make_shared<DTimeProgressiveStage>(
      string("crosses the bridge"), 2000, 7000);
  this->setStage(DStageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

  auto finished = make_shared<DTimeProgressiveStage>(
      string("reaches the end of the bridge"), 2000, 3000);
  this->setStage(DStageType::FOLLOW_THROUGH, finished);

  //        auto cancel = make_shared<TimeProgressiveStage>(
  //                string("stopped walking abruptly before reaching the end of
  //                the bridge"), 1000, 3000);
  //        this->setStage(StageType::CANCEL, cancel);
}

ThrowBall::ThrowBall() {
  this->setName("Throw Ball");

  auto anticipation =
      make_shared<DTimeProgressiveStage>(string("throws the ball"), 2000, 7000);
  this->setStage(DStageType::ANTICIPATION_INTERRUPTIBLE, anticipation);
  //
  //        auto execution = make_shared<TimeProgressiveStage>(string("throws
  //        the ball"), 1000, 5000);
  //        this->setStage(StageType::ANTICIPATION_UNINTERRUPTIBLE, execution);

  auto finished = make_shared<DTimeProgressiveStage>(
      string("sees the ball hit the target"), 2000, 3000);
  this->setStage(DStageType::FOLLOW_THROUGH, finished);

  //        auto cancel = make_shared<TimeProgressiveStage>(string("stops his
  //        swing and doesn't throw the ball"), 1000,
  //                                                        1000);
  //        this->setStage(StageType::CANCEL, cancel);
}
}
