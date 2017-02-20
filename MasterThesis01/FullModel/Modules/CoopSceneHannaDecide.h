/*
 * File CoopSceneHannaDecide.h in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef COOPSCENEHANNADECIDE_H
#define COOPSCENEHANNADECIDE_H

#include "DModule.h"
#include "Time.h"

class CoopSceneHannaDecide : public Divisaction::DecideModule {
 public:
  CoopSceneHannaDecide();

 protected:
  virtual void _execute() override;

  Divisaction::milliseconds interval;

 private:
  bool alreadyActed;

  std::shared_ptr<Divisaction::DTimer> timer;
};

#endif  // COOPSCENEHANNADECIDE_H
