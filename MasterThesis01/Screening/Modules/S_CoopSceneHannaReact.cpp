/*
 * File CoopSceneHannaReact.cpp in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "S_CoopSceneHannaReact.h"

using namespace ThreeMotion;

Screening::CoopSceneHannaReact::CoopSceneHannaReact() {
  alreadyFelt = std::vector<bool>(10);
}

void Screening::CoopSceneHannaReact::_execute() {
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
        if (auto origin = bobMentalRep->agent.lock()) {
          Wait(4000, [this, bobMentalRep]() {
            if (std::shared_ptr<TTheoryOfMind> innerMentalState =
                    theoryOfMindWeak.lock()) {
              if (auto innerOrigin = bobMentalRep->agent.lock()) {
                if (bobMentalRep->stage ==
                    TStageType::ANTICIPATION_INTERRUPTIBLE) {
                  if ((innerMentalState->self.emotion =
                           innerMentalState->self.GetEmotion("Confidence"))) {
                    innerMentalState->self.emotion->replyToAgent = innerOrigin;
                  }
                }
              }
            }
          });

          if (bobMentalRep->stage == TStageType::FOLLOW_THROUGH) {
            if ((mentalState->self.emotion =
                     mentalState->self.GetEmotion("Relief"))) {
              mentalState->self.emotion->replyToAgent = origin;
            }
          }
        }
      }
    }
  }
}
