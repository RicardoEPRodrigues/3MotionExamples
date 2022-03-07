/*
 * File CoopSceneHannaReact.h in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef SCREENING_COOPSCENEHANNAREACT_H
#define SCREENING_COOPSCENEHANNAREACT_H

#include "TModule.h"

namespace Screening {
class CoopSceneHannaReact : public ThreeMotion::InterpretModule {
 public:
  CoopSceneHannaReact();

 protected:
  virtual void _execute() override;

 private:
  std::vector<bool> alreadyFelt;
};
}

#endif  // SCREENING_COOPSCENEHANNAREACT_H
