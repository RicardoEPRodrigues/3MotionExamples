/*
 * File CoopSceneBobDecide.cpp in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "CoopSceneBobDecide.h"

using namespace Divisaction;

CoopSceneBobDecide::CoopSceneBobDecide()
    : alreadyActed(false), timer(nullptr) {}

CoopSceneBobDecide::~CoopSceneBobDecide() {}

void CoopSceneBobDecide::_execute() {
  if (auto mentalState = mentalStateWeak.lock()) {
    if (!alreadyActed && !mentalState->self.action &&
        mentalState->self.countActions() > 0) {
      alreadyActed = true;
      // Start walking
      mentalState->self.action = mentalState->self.getAction("Long Walk");
      // After a while if Hanna is not following, cancel action.
      timer = ifWait(
          8000,
          [this]() {
            //                    if (auto mentalState = mentalStateWeak.lock())
            //                    {
            //                        if (mentalState->self.action) {
            //                            mentalState->self.action->cancel();
            //                        }
            //                    }
          },
          [this](milliseconds) {
            if (auto innerMentalState = mentalStateWeak.lock()) {
              // If Hanna replied with fear to his walking, then cancel action
              for (auto replyIter = innerMentalState->self.replies.begin();
                   replyIter != innerMentalState->self.replies.end();
                   ++replyIter) {
                if (auto sender = (*replyIter)->sender.lock()) {
                  if (sender->name.compare("Hanna") == 0 &&
                      (*replyIter)->emotion->getName().compare("Fear") == 0) {
                    if (innerMentalState->self.action) {
                      innerMentalState->self.action->cancel();
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
              //                        mentalState->getOther("Hanna"))) {
              //                            return
              //                            hannaMentalRep->actionHasName("Follow");
              //                        }
            }
            return true;
          });
    }
  }
}
