/*
 * File CoopSceneBobReact.h in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef NOANTICIPATION_COOPSCENEBOBREACT_H
#define NOANTICIPATION_COOPSCENEBOBREACT_H

#include "TModule.h"

namespace NoAnticipation {
class CoopSceneBobReact : public ThreeMotion::InterpretModule {
 public:
  CoopSceneBobReact();

 protected:
  virtual void _execute() override;

 private:
  std::vector<bool> alreadyFelt;
};
}

#endif  // NOANTICIPATION_COOPSCENEBOBREACT_H
