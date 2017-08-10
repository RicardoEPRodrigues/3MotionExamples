/*
 * File Emotions.h in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef EMOTIONS_H
#define EMOTIONS_H

#include "DEmotion.h"

class Confidence : public Divisaction::DEmotion {
 public:
  Confidence();
};

class Fear : public Divisaction::DEmotion {
 public:
  Fear();
};

class Happiness : public Divisaction::DEmotion {
 public:
  Happiness();
};

class Relief : public Divisaction::DEmotion {
 public:
  Relief();
};

class Apprehension : public Divisaction::DEmotion {
 public:
  Apprehension();
};

class Sadness : public Divisaction::DEmotion {
 public:
  Sadness();
};

#endif  // EMOTIONS_H
