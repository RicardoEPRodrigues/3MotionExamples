/*
 * File CoopSceneBobReact.h in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef SCREENING_COOPSCENEBOBREACT_H
#define SCREENING_COOPSCENEBOBREACT_H

#include "TModule.h"

namespace Screening {
class CoopSceneBobReact : public ThreeMotion::InterpretModule {
 public:
  CoopSceneBobReact();

 protected:
  virtual void _execute() override;

 private:
  std::vector<bool> alreadyFelt;
};
}

#endif  // SCREENING_COOPSCENEBOBREACT_H
