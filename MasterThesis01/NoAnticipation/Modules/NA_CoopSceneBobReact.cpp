/*
 * File CoopSceneBobReact.cpp in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "NA_CoopSceneBobReact.h"

using namespace Divisaction;

NoAnticipation::CoopSceneBobReact::CoopSceneBobReact() {
  alreadyFelt = std::vector<bool>(10);
}

void NoAnticipation::CoopSceneBobReact::_execute() {
  if (auto mentalState = mentalStateWeak.lock()) {
    if (!alreadyFelt[0]) {
      mentalState->self.emotion = mentalState->self.getEmotion("Confidence");
      alreadyFelt[0] = true;
    }
    if (!alreadyFelt[1] && mentalState->self.actionHasName("Long Walk") &&
        mentalState->self.actionInStage(DStageType::FOLLOW_THROUGH)) {
      mentalState->self.emotion = mentalState->self.getEmotion("Happiness");
      alreadyFelt[1] = true;
    }
    if (!alreadyFelt[2] && mentalState->self.actionHasName("Long Walk") &&
        mentalState->self.actionInStage(DStageType::CANCEL)) {
      mentalState->self.emotion = mentalState->self.getEmotion("Sadness");
      alreadyFelt[2] = true;
    }

    DOtherMentalState* hannaMentalRep;
    if ((hannaMentalRep = mentalState->getOther("Hanna"))) {
      if (hannaMentalRep->updateAction && hannaMentalRep->updateEmotion &&
          hannaMentalRep->action && hannaMentalRep->emotion) {
        hannaMentalRep->updateAction = false;
        hannaMentalRep->updateEmotion = false;
        if (auto self = mentalState->self.agent.lock()) {
          if (auto origin = hannaMentalRep->agent.lock()) {
            if (hannaMentalRep->stage == DStageType::FOLLOW_THROUGH) {
              if ((mentalState->self.emotion =
                       mentalState->self.getEmotion("Happiness"))) {
                mentalState->self.emotion->replyToAgent(origin);
              }
            }
          }
        }
      }
    }
  }
}
