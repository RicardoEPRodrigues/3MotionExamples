/*
 * File CoopSceneHannaDecide.cpp in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "CoopSceneHannaDecide.h"

using namespace ThreeMotion;

CoopSceneHannaDecide::CoopSceneHannaDecide()
    : InterpretModule(), interval(2000), alreadyActed(false), timer(nullptr) {}

void CoopSceneHannaDecide::_execute() {
  //        if (mentalState->self.EmotionHasName("Fear")) {
  //            return; // Frozen in fear
  //        }
  if (!alreadyActed) {
    if (auto mentalState = theoryOfMindWeak.lock()) {
      if (mentalState->self.EmotionHasName("Fear")) {
        alreadyActed = true;  // Frozen in fear
      } else {
        // Follow Bob if he's walking.
        if (!timer) {
          TOtherMentalState* bobMentalRep;
          if ((bobMentalRep = mentalState->GetOther("Bob"))) {
            if (bobMentalRep->ActionHasName("Long Walk")) {
              timer = Wait(interval, [this]() {
                if (auto innerMentalState = theoryOfMindWeak.lock()) {
                  innerMentalState->self.action =
                      innerMentalState->self.GetAction("Follow");
                  alreadyActed = true;
                }
              });
            }
          }
        }
      }
    }
  }
}
