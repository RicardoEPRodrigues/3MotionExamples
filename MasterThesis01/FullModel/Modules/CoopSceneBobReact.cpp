/*
 * File CoopSceneBobReact.cpp in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "CoopSceneBobReact.h"

using namespace ThreeMotion;

CoopSceneBobReact::CoopSceneBobReact() { alreadyFelt = std::vector<bool>(10); }

void CoopSceneBobReact::_execute() {
  if (auto mentalState = theoryOfMindWeak.lock()) {
    if (!alreadyFelt[0]) {
      mentalState->self.emotion = mentalState->self.GetEmotion("Confidence");
      alreadyFelt[0] = true;
    }
    if (!alreadyFelt[1] && mentalState->self.ActionHasName("Long Walk") &&
        mentalState->self.IsActionInStage(TStageType::FOLLOW_THROUGH)) {
      mentalState->self.emotion = mentalState->self.GetEmotion("Happiness");
      alreadyFelt[1] = true;
    }
    if (!alreadyFelt[2] && mentalState->self.ActionHasName("Long Walk") &&
        mentalState->self.IsActionInStage(TStageType::CANCEL)) {
      mentalState->self.emotion = mentalState->self.GetEmotion("Sadness");
      alreadyFelt[2] = true;
    }

    TOtherMentalState* hannaMentalRep;
    if ((hannaMentalRep = mentalState->GetOther("Hanna"))) {
      if (hannaMentalRep->UpdateAction && hannaMentalRep->UpdateEmotion &&
          hannaMentalRep->action && hannaMentalRep->emotion) {
        hannaMentalRep->UpdateAction = false;
        hannaMentalRep->UpdateEmotion = false;
        if (auto self = mentalState->self.agent.lock()) {
          if (auto origin = hannaMentalRep->agent.lock()) {
            std::string emotionName;
            if (hannaMentalRep->stage ==
                TStageType::ANTICIPATION_INTERRUPTIBLE) {
              emotionName = "Confidence";
            } else {
              emotionName = "Happiness";
            }

            mentalState->self.emotion = mentalState->self.GetEmotion(emotionName);
            mentalState->self.emotion->replyToAgent = origin;
          }
        }
      }
    }
  }
}
