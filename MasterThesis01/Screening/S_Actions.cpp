/*
 * File ReactiveActions.cpp in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "S_Actions.h"
#include "Extra/TTimeProgressiveStage.h"

using namespace std;
using namespace ThreeMotion;

namespace Screening {

Follow::Follow(std::weak_ptr<TIAgent> agent) : TAction() {
  this->setName("Follow");

  if (auto agentshr = agent.lock()) {
    auto anticipation = make_shared<TTimeProgressiveStage>(
        string("follows " + agentshr->name), 2000, 7000);
    this->SetStage(TStageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

    auto finished = make_shared<TTimeProgressiveStage>(
        string("reaches " + agentshr->name), 2000, 3000);
    this->SetStage(TStageType::FOLLOW_THROUGH, finished);

    //            auto cancel = make_shared<TimeProgressiveStage>(
    //                    string("stopped following " + agentshr->getName() + "
    //                    abruptly"), 1000, 3000);
    //            this->SetStage(StageType::CANCEL, cancel);
  }
}

LongWalk::LongWalk() : TAction() {
  this->setName("Long Walk");

  auto anticipation = make_shared<TTimeProgressiveStage>(
      string("crosses the bridge"), 2000, 7000);
  this->SetStage(TStageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

  auto finished = make_shared<TTimeProgressiveStage>(
      string("reaches the end of the bridge"), 2000, 3000);
  this->SetStage(TStageType::FOLLOW_THROUGH, finished);

  //        auto cancel = make_shared<TimeProgressiveStage>(
  //                string("stopped walking abruptly before reaching the end of
  //                the bridge"), 1000, 3000);
  //        this->SetStage(StageType::CANCEL, cancel);
}

ThrowBall::ThrowBall() {
  this->setName("Throw Ball");

  auto anticipation =
      make_shared<TTimeProgressiveStage>(string("throws the ball"), 2000, 7000);
  this->SetStage(TStageType::ANTICIPATION_INTERRUPTIBLE, anticipation);
  //
  //        auto execution = make_shared<TimeProgressiveStage>(string("throws
  //        the ball"), 1000, 5000);
  //        this->SetStage(StageType::ANTICIPATION_UNINTERRUPTIBLE, execution);

  auto finished = make_shared<TTimeProgressiveStage>(
      string("sees the ball hit the target"), 2000, 3000);
  this->SetStage(TStageType::FOLLOW_THROUGH, finished);

  //        auto cancel = make_shared<TimeProgressiveStage>(string("stops his
  //        swing and doesn't throw the ball"), 1000,
  //                                                        1000);
  //        this->SetStage(StageType::CANCEL, cancel);
}
}
