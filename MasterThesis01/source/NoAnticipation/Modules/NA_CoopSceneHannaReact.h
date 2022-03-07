/*
 * File CoopSceneHannaReact.h in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef NOANTICIPATION_COOPSCENEHANNAREACT_H
#define NOANTICIPATION_COOPSCENEHANNAREACT_H

#include "TModule.h"

namespace NoAnticipation {
class CoopSceneHannaReact : public ThreeMotion::InterpretModule {
 public:
  CoopSceneHannaReact();

 protected:
  virtual void _execute() override;

 private:
  std::vector<bool> alreadyFelt;
};
}

#endif  // NOANTICIPATION_COOPSCENEHANNAREACT_H
