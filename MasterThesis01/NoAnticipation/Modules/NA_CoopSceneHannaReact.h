/*
 * File CoopSceneHannaReact.h in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef NOANTICIPATION_COOPSCENEHANNAREACT_H
#define NOANTICIPATION_COOPSCENEHANNAREACT_H

#include "DModule.h"

namespace NoAnticipation {
class CoopSceneHannaReact : public Divisaction::ReactModule {
 public:
  CoopSceneHannaReact();

 protected:
  virtual void _execute() override;

 private:
  std::vector<bool> alreadyFelt;
};
}

#endif  // NOANTICIPATION_COOPSCENEHANNAREACT_H
