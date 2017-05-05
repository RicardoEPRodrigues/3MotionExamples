/*
 * File CoopSceneBobDecide.h in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef COOPSCENEBOBDECIDE_H
#define COOPSCENEBOBDECIDE_H

#include "DModule.h"

class CoopSceneBobDecide : public Divisaction::InterpretModule {
 public:
  CoopSceneBobDecide();

  virtual ~CoopSceneBobDecide();

 protected:
  virtual void _execute();

 private:
  bool alreadyActed;
  std::shared_ptr<Divisaction::DTimer> timer;
};

#endif  // COOPSCENEBOBDECIDE_H
