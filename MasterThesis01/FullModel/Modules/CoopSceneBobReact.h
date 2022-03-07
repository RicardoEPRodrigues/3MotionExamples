/*
 * File CoopSceneBobReact.h in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef COOPSCENEBOBREACT_H
#define COOPSCENEBOBREACT_H

#include "TModule.h"

class CoopSceneBobReact : public ThreeMotion::InterpretModule {
 public:
  CoopSceneBobReact();

 protected:
  virtual void _execute() override;

 private:
  std::vector<bool> alreadyFelt;
};

#endif  // COOPSCENEBOBREACT_H
