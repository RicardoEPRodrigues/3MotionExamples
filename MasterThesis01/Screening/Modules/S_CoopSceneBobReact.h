/*
 * File CoopSceneBobReact.h in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef SCREENING_COOPSCENEBOBREACT_H
#define SCREENING_COOPSCENEBOBREACT_H

#include "DModule.h"

namespace Screening {
class CoopSceneBobReact : public Divisaction::ReactModule {
 public:
  CoopSceneBobReact();

 protected:
  virtual void _execute() override;

 private:
  std::vector<bool> alreadyFelt;
};
}

#endif  // SCREENING_COOPSCENEBOBREACT_H
