/*
 * File CoopSceneHannaReact.cpp in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "S_CoopSceneHannaReact.h"

using namespace Divisaction;

Screening::CoopSceneHannaReact::CoopSceneHannaReact() {
  alreadyFelt = std::vector<bool>(10);
}

void Screening::CoopSceneHannaReact::_execute() {
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
        if (auto origin = bobMentalRep->agent.lock()) {
          wait(4000, [this, bobMentalRep]() {
            if (std::shared_ptr<TheoryOfMind> innerMentalState =
                    mentalStateWeak.lock()) {
              if (auto innerOrigin = bobMentalRep->agent.lock()) {
                if (bobMentalRep->state ==
                    StageType::ANTICIPATION_INTERRUPTIBLE) {
                  if ((innerMentalState->self.emotion =
                           innerMentalState->self.getEmotion("Confidence"))) {
                    innerMentalState->self.emotion->replyToAgent(innerOrigin);
                  }
                }
              }
            }
          });

          if (bobMentalRep->state == StageType::FOLLOW_THROUGH) {
            if ((mentalState->self.emotion =
                     mentalState->self.getEmotion("Relief"))) {
              mentalState->self.emotion->replyToAgent(origin);
            }
          }
        }
      }
    }
  }
}
