/*
 * File CoopSceneBobReact.cpp in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "CoopSceneBobReact.h"

using namespace Divisaction;

CoopSceneBobReact::CoopSceneBobReact() { alreadyFelt = std::vector<bool>(10); }

void CoopSceneBobReact::_execute() {
  if (auto mentalState = mentalStateWeak.lock()) {
    if (!alreadyFelt[0]) {
      mentalState->self.emotion = mentalState->self.getEmotion("Confidence");
      alreadyFelt[0] = true;
    }
    if (!alreadyFelt[1] && mentalState->self.actionHasName("Long Walk") &&
        mentalState->self.actionInStage(StageType::FOLLOW_THROUGH)) {
      mentalState->self.emotion = mentalState->self.getEmotion("Happiness");
      alreadyFelt[1] = true;
    }
    if (!alreadyFelt[2] && mentalState->self.actionHasName("Long Walk") &&
        mentalState->self.actionInStage(StageType::CANCEL)) {
      mentalState->self.emotion = mentalState->self.getEmotion("Sadness");
      alreadyFelt[2] = true;
    }

    OtherMentalRepresentation* hannaMentalRep;
    if ((hannaMentalRep = mentalState->getOther("Hanna"))) {
      if (hannaMentalRep->updateAction && hannaMentalRep->updateEmotion &&
          hannaMentalRep->action && hannaMentalRep->emotion) {
        hannaMentalRep->updateAction = false;
        hannaMentalRep->updateEmotion = false;
        if (auto self = mentalState->self.agent.lock()) {
          if (auto origin = hannaMentalRep->agent.lock()) {
            std::string emotionName;
            if (hannaMentalRep->state ==
                StageType::ANTICIPATION_INTERRUPTIBLE) {
              emotionName = "Confidence";
            } else {
              emotionName = "Happiness";
            }

            mentalState->self.emotion =
                mentalState->self.getEmotion(emotionName);
            mentalState->self.emotion->replyToAgent(origin);
          }
        }
      }
    }
  }
}
