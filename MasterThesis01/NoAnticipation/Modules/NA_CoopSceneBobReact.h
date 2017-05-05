/*
 * File CoopSceneBobReact.h in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef NOANTICIPATION_COOPSCENEBOBREACT_H
#define NOANTICIPATION_COOPSCENEBOBREACT_H

#include "DModule.h"

namespace NoAnticipation {
class CoopSceneBobReact : public Divisaction::InterpretModule {
 public:
  CoopSceneBobReact();

 protected:
  virtual void _execute() override;

 private:
  std::vector<bool> alreadyFelt;
};
}

#endif  // NOANTICIPATION_COOPSCENEBOBREACT_H
