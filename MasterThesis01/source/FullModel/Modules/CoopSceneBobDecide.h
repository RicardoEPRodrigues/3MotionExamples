/*
 * File CoopSceneBobDecide.h in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef COOPSCENEBOBDECIDE_H
#define COOPSCENEBOBDECIDE_H

#include "TModule.h"

class CoopSceneBobDecide : public ThreeMotion::InterpretModule {
 public:
  CoopSceneBobDecide();

  virtual ~CoopSceneBobDecide();

 protected:
  virtual void _execute();

 private:
  bool alreadyActed;
  std::shared_ptr<ThreeMotion::TTimer> timer;
};

#endif  // COOPSCENEBOBDECIDE_H
