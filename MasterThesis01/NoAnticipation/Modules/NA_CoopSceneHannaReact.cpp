/*
 * File CoopSceneHannaReact.cpp in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "NA_CoopSceneHannaReact.h"

using namespace ThreeMotion;

NoAnticipation::CoopSceneHannaReact::CoopSceneHannaReact() {
  alreadyFelt = std::vector<bool>(10);
}

void NoAnticipation::CoopSceneHannaReact::_execute() {
  if (std::shared_ptr<TTheoryOfMind> mentalState = theoryOfMindWeak.lock()) {
    if (!alreadyFelt[0] &&
        mentalState->self.IsActionInStage(TStageType::ANTICIPATION_INTERRUPTIBLE)) {
      mentalState->self.emotion = mentalState->self.GetEmotion("Fear");
      alreadyFelt[0] = true;
    } else if (!alreadyFelt[1] &&
               mentalState->self.IsActionInStage(TStageType::FOLLOW_THROUGH)) {
      mentalState->self.emotion = mentalState->self.GetEmotion("Happiness");
      alreadyFelt[1] = true;
    }

    TOtherMentalState* bobMentalRep;
    if ((bobMentalRep = mentalState->GetOther("Bob"))) {
      if (bobMentalRep->UpdateAction && bobMentalRep->UpdateEmotion &&
          bobMentalRep->action && bobMentalRep->emotion) {
        bobMentalRep->UpdateAction = false;
        bobMentalRep->UpdateEmotion = false;
        if (auto self = mentalState->self.agent.lock()) {
          if (auto origin = bobMentalRep->agent.lock()) {
            if (bobMentalRep->stage == TStageType::FOLLOW_THROUGH) {
              if ((mentalState->self.emotion =
                       mentalState->self.GetEmotion("Relief"))) {
                mentalState->self.emotion->replyToAgent = origin;
              }
            }
          }
        }
      } else if (bobMentalRep->UpdateAction && bobMentalRep->action) {
        // TODO deal with the case of having only an action
      } else if (bobMentalRep->UpdateEmotion && bobMentalRep->emotion) {
        // TODO deal with the case of having only an emotion
      }
    }
  }
}
