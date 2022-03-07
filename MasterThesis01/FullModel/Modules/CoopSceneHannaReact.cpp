/*
 * File CoopSceneHannaReact.cpp in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "CoopSceneHannaReact.h"

using namespace ThreeMotion;

CoopSceneHannaReact::CoopSceneHannaReact() {
  alreadyFelt = std::vector<bool>(10);
}

void CoopSceneHannaReact::_execute() {
  if (auto mentalState = theoryOfMindWeak.lock()) {
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
            std::string emotionName;
            if (bobMentalRep->stage == TStageType::ANTICIPATION_INTERRUPTIBLE) {
              emotionName = "Apprehension";
            } else {
              emotionName = "Relief";
            }

            if ((mentalState->self.emotion =
                     mentalState->self.GetEmotion(emotionName))) {
              mentalState->self.emotion->replyToAgent = origin;
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
