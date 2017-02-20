/*
 * File Emotions.cpp in project Divisaction
 *
 * Copyright (C) Ricardo Rodrigues 2016 - All Rights Reserved
 */
#include "Emotions.h"
#include "Extra/TimeProgressiveStage.h"

using namespace Divisaction;

Confidence::Confidence()
    : Emotion("Confidence", std::make_shared<TimeProgressiveStage>(
                                std::string("is confident"), 1500, 2000),
              "winks at ") {}

Fear::Fear()
    : Emotion("Fear", std::make_shared<TimeProgressiveStage>(
                          std::string("is afraid"), 1500, 2000),
              "gives a terrifying look at ") {}

Happiness::Happiness()
    : Emotion("Happiness", std::make_shared<TimeProgressiveStage>(
                               std::string("is happy"), 1500, 2000),
              "smiles at ") {}

Relief::Relief()
    : Emotion("Relief", std::make_shared<TimeProgressiveStage>(
                            std::string("is relieved"), 1500, 2000),
              "breaths out and looks at ") {}

Apprehension::Apprehension()
    : Emotion("Apprehension", std::make_shared<TimeProgressiveStage>(
                                  std::string("is apprehensive"), 1500, 2000),
              "feels somethings is wrong and fears for ") {}

Sadness::Sadness()
    : Emotion("Sadness", std::make_shared<TimeProgressiveStage>(
                             std::string("is sad"), 1500, 2000),
              "feels gloomy and discouraged, looking at ") {}
