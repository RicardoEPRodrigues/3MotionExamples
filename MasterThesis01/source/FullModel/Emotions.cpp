/*
 * File Emotions.cpp in project ThreeMotion
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "Emotions.h"
#include "Extra/TTimeProgressiveStage.h"

using namespace ThreeMotion;

Confidence::Confidence()
    : TEmotion("Confidence", std::make_shared<TTimeProgressiveStage>(
                                std::string("is confident"), 1500, 2000),
              "winks at ") {}

Fear::Fear()
    : TEmotion("Fear", std::make_shared<TTimeProgressiveStage>(
                          std::string("is afraid"), 1500, 2000),
              "gives a terrifying look at ") {}

Happiness::Happiness()
    : TEmotion("Happiness", std::make_shared<TTimeProgressiveStage>(
                               std::string("is happy"), 1500, 2000),
              "smiles at ") {}

Relief::Relief()
    : TEmotion("Relief", std::make_shared<TTimeProgressiveStage>(
                            std::string("is relieved"), 1500, 2000),
              "breaths out and looks at ") {}

Apprehension::Apprehension()
    : TEmotion("Apprehension", std::make_shared<TTimeProgressiveStage>(
                                  std::string("is apprehensive"), 1500, 2000),
              "feels somethings is wrong and fears for ") {}

Sadness::Sadness()
    : TEmotion("Sadness", std::make_shared<TTimeProgressiveStage>(
                             std::string("is sad"), 1500, 2000),
              "feels gloomy and discouraged, looking at ") {}
