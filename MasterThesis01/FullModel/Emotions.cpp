/*
 * File Emotions.cpp in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "Emotions.h"
#include "Extra/DTimeProgressiveStage.h"

using namespace Divisaction;

Confidence::Confidence()
    : DEmotion("Confidence", std::make_shared<DTimeProgressiveStage>(
                                std::string("is confident"), 1500, 2000),
              "winks at ") {}

Fear::Fear()
    : DEmotion("Fear", std::make_shared<DTimeProgressiveStage>(
                          std::string("is afraid"), 1500, 2000),
              "gives a terrifying look at ") {}

Happiness::Happiness()
    : DEmotion("Happiness", std::make_shared<DTimeProgressiveStage>(
                               std::string("is happy"), 1500, 2000),
              "smiles at ") {}

Relief::Relief()
    : DEmotion("Relief", std::make_shared<DTimeProgressiveStage>(
                            std::string("is relieved"), 1500, 2000),
              "breaths out and looks at ") {}

Apprehension::Apprehension()
    : DEmotion("Apprehension", std::make_shared<DTimeProgressiveStage>(
                                  std::string("is apprehensive"), 1500, 2000),
              "feels somethings is wrong and fears for ") {}

Sadness::Sadness()
    : DEmotion("Sadness", std::make_shared<DTimeProgressiveStage>(
                             std::string("is sad"), 1500, 2000),
              "feels gloomy and discouraged, looking at ") {}
