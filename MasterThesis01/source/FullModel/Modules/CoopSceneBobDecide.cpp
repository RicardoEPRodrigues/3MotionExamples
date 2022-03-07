/*
 * File CoopSceneBobDecide.cpp in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "CoopSceneBobDecide.h"

using namespace ThreeMotion;

CoopSceneBobDecide::CoopSceneBobDecide()
    : alreadyActed(false), timer(nullptr) {}

CoopSceneBobDecide::~CoopSceneBobDecide() {}

void CoopSceneBobDecide::_execute() {
  if (auto mentalState = theoryOfMindWeak.lock()) {
    if (!alreadyActed && !mentalState->self.action &&
        mentalState->self.CountActions() > 0) {
      alreadyActed = true;
      // Start walking
      mentalState->self.action = mentalState->self.GetAction("Long Walk");
      // After a while if Hanna is not following, cancel action.
      timer = IfWait(
          8000,
          [this]() {
            //                    if (auto mentalState = theoryOfMindWeak.lock())
            //                    {
            //                        if (mentalState->self.action) {
            //                            mentalState->self.action->cancel();
            //                        }
            //                    }
          },
          [this](milliseconds) {
            if (auto innerMentalState = theoryOfMindWeak.lock()) {
              // If Hanna replied with fear to his walking, then cancel action
              for (auto replyIter = innerMentalState->self.replies.begin();
                   replyIter != innerMentalState->self.replies.end();
                   ++replyIter) {
                if (auto sender = (*replyIter)->sender.lock()) {
                  if (sender->name.compare("Hanna") == 0 &&
                      (*replyIter)->emotion->getName().compare("Fear") == 0) {
                    if (innerMentalState->self.action) {
                      innerMentalState->self.action->Cancel();
                    }
                    return true;
                  }
                }
              }
              return false;

              // If Hanna is following then do not cancel
              //                        OtherMentalRepresentation*
              //                        hannaMentalRep;
              //                        if ((hannaMentalRep =
              //                        mentalState->GetOther("Hanna"))) {
              //                            return
              //                            hannaMentalRep->ActionHasName("Follow");
              //                        }
            }
            return true;
          });
    }
  }
}
