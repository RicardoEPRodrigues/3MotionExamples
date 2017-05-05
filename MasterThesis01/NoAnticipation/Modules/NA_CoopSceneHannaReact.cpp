/*
 * File CoopSceneHannaReact.cpp in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "NA_CoopSceneHannaReact.h"

using namespace Divisaction;

NoAnticipation::CoopSceneHannaReact::CoopSceneHannaReact() {
  alreadyFelt = std::vector<bool>(10);
}

void NoAnticipation::CoopSceneHannaReact::_execute() {
  if (std::shared_ptr<TheoryOfMind> mentalState = mentalStateWeak.lock()) {
    if (!alreadyFelt[0] &&
        mentalState->self.actionInStage(
            StageType::ANTICIPATION_INTERRUPTIBLE)) {
      mentalState->self.emotion = mentalState->self.getEmotion("Fear");
      alreadyFelt[0] = true;
    } else if (!alreadyFelt[1] &&
               mentalState->self.actionInStage(StageType::FOLLOW_THROUGH)) {
      mentalState->self.emotion = mentalState->self.getEmotion("Happiness");
      alreadyFelt[1] = true;
    }

    OtherMentalState* bobMentalRep;
    if ((bobMentalRep = mentalState->getOther("Bob"))) {
      if (bobMentalRep->updateAction && bobMentalRep->updateEmotion &&
          bobMentalRep->action && bobMentalRep->emotion) {
        bobMentalRep->updateAction = false;
        bobMentalRep->updateEmotion = false;
        if (auto self = mentalState->self.agent.lock()) {
          if (auto origin = bobMentalRep->agent.lock()) {
            if (bobMentalRep->state == StageType::FOLLOW_THROUGH) {
              if ((mentalState->self.emotion =
                       mentalState->self.getEmotion("Relief"))) {
                mentalState->self.emotion->replyToAgent(origin);
              }
            }
          }
        }
      } else if (bobMentalRep->updateAction && bobMentalRep->action) {
        // TODO deal with the case of having only an action
      } else if (bobMentalRep->updateEmotion && bobMentalRep->emotion) {
        // TODO deal with the case of having only an emotion
      }
    }
  }
}
