/*
 * File Emotions.h in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef EMOTIONS_H
#define EMOTIONS_H

#include "TEmotion.h"

class Confidence : public ThreeMotion::TEmotion {
 public:
  Confidence();
};

class Fear : public ThreeMotion::TEmotion {
 public:
  Fear();
};

class Happiness : public ThreeMotion::TEmotion {
 public:
  Happiness();
};

class Relief : public ThreeMotion::TEmotion {
 public:
  Relief();
};

class Apprehension : public ThreeMotion::TEmotion {
 public:
  Apprehension();
};

class Sadness : public ThreeMotion::TEmotion {
 public:
  Sadness();
};

#endif  // EMOTIONS_H
