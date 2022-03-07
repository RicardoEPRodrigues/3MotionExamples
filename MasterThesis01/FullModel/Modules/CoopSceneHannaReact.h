/*
 * File CoopSceneHannaReact.h in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef COOPSCENEHANNAREACT_H
#define COOPSCENEHANNAREACT_H

#include "TModule.h"

class CoopSceneHannaReact : public ThreeMotion::InterpretModule {
 public:
  CoopSceneHannaReact();

 protected:
  virtual void _execute() override;

 private:
  std::vector<bool> alreadyFelt;
};

#endif  // COOPSCENEHANNAREACT_H
