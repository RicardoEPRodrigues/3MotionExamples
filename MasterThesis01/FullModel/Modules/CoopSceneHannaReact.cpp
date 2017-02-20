/*
 * File CoopSceneHannaReact.cpp in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "CoopSceneHannaReact.h"

using namespace Divisaction;

CoopSceneHannaReact::CoopSceneHannaReact() {
  alreadyFelt = std::vector<bool>(10);
}

void CoopSceneHannaReact::_execute() {
  if (auto mentalState = mentalStateWeak.lock()) {
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

    OtherMentalRepresentation* bobMentalRep;
    if ((bobMentalRep = mentalState->getOther("Bob"))) {
      if (bobMentalRep->updateAction && bobMentalRep->updateEmotion &&
          bobMentalRep->action && bobMentalRep->emotion) {
        bobMentalRep->updateAction = false;
        bobMentalRep->updateEmotion = false;
        if (auto self = mentalState->self.agent.lock()) {
          if (auto origin = bobMentalRep->agent.lock()) {
            std::string emotionName;
            if (bobMentalRep->state == StageType::ANTICIPATION_INTERRUPTIBLE) {
              emotionName = "Apprehension";
              //                                emotionName = "Fear";
            } else {
              emotionName = "Relief";
            }

            if ((mentalState->self.emotion =
                     mentalState->self.getEmotion(emotionName))) {
              mentalState->self.emotion->replyToAgent(origin);
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
