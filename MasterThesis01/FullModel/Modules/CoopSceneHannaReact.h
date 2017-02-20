/*
 * File CoopSceneHannaReact.h in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef COOPSCENEHANNAREACT_H
#define COOPSCENEHANNAREACT_H

#include "DModule.h"

class CoopSceneHannaReact : public Divisaction::ReactModule {
 public:
  CoopSceneHannaReact();

 protected:
  virtual void _execute() override;

 private:
  std::vector<bool> alreadyFelt;
};

#endif  // COOPSCENEHANNAREACT_H
