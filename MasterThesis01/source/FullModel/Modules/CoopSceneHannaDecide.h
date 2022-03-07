/*
 * File CoopSceneHannaDecide.h in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef COOPSCENEHANNADECIDE_H
#define COOPSCENEHANNADECIDE_H

#include "TModule.h"
#include "TTime.h"

class CoopSceneHannaDecide : public ThreeMotion::InterpretModule {
 public:
  CoopSceneHannaDecide();

 protected:
  virtual void _execute() override;

  ThreeMotion::milliseconds interval;

 private:
  bool alreadyActed;

  std::shared_ptr<ThreeMotion::TTimer> timer;
};

#endif  // COOPSCENEHANNADECIDE_H
