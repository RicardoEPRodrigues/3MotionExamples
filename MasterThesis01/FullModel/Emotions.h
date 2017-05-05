/*
 * File Emotions.h in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#ifndef EMOTIONS_H
#define EMOTIONS_H

#include "Emotion.h"

class Confidence : public Divisaction::Emotion {
 public:
  Confidence();
};

class Fear : public Divisaction::Emotion {
 public:
  Fear();
};

class Happiness : public Divisaction::Emotion {
 public:
  Happiness();
};

class Relief : public Divisaction::Emotion {
 public:
  Relief();
};

class Apprehension : public Divisaction::Emotion {
 public:
  Apprehension();
};

class Sadness : public Divisaction::Emotion {
 public:
  Sadness();
};

#endif  // EMOTIONS_H
