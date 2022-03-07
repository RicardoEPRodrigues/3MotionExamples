#include "worldholder.h"

#include "Extra/TChronoTimeCalculator.h"

#include "Modules/DDelayPerceive.h"
#include "Modules/DPerform.h"

#include "FullModel/Actions.h"
#include "FullModel/Emotions.h"
#include "FullModel/Modules/CoopSceneBobDecide.h"
#include "FullModel/Modules/CoopSceneBobReact.h"
#include "FullModel/Modules/CoopSceneHannaDecide.h"
#include "FullModel/Modules/CoopSceneHannaReact.h"

#include "NoAnticipation/Modules/NA_CoopSceneBobReact.h"
#include "NoAnticipation/Modules/NA_CoopSceneHannaReact.h"
#include "NoAnticipation/NA_Actions.h"

#include "Screening/Modules/S_CoopSceneBobReact.h"
#include "Screening/Modules/S_CoopSceneHannaReact.h"
#include "Screening/S_Actions.h"

using namespace ThreeMotion;
using namespace std;

WorldHolder::WorldHolder() {}

shared_ptr<TWorldManager> WorldHolder::CreateWorld(SceneType type) {
  TTime::SetTimeCalculator(std::make_shared<TChronoTimeCalculator>());

  auto worldManager = make_shared<TWorldManager>();
  worldManager->description =
      "This scenario contains 2 agents, Bob and Hanna.\n The agents are near a "
      "rope bridge.";

  auto agentBob = make_shared<TAgent>();
  auto agentHanna = make_shared<TAgent>();
  agentBob->name = string("Bob");
  agentBob->AddAvailableEmotion(make_shared<Confidence>());
  agentBob->AddAvailableEmotion(make_shared<Fear>());
  agentBob->AddAvailableEmotion(make_shared<Happiness>());
  agentBob->AddAvailableEmotion(make_shared<Relief>());
  agentBob->AddAvailableEmotion(make_shared<Apprehension>());
  agentBob->AddAvailableEmotion(make_shared<Sadness>());

  agentHanna->name = string("Hanna");
  agentHanna->AddAvailableEmotion(make_shared<Confidence>());
  agentHanna->AddAvailableEmotion(make_shared<Fear>());
  agentHanna->AddAvailableEmotion(make_shared<Happiness>());
  agentHanna->AddAvailableEmotion(make_shared<Relief>());
  agentHanna->AddAvailableEmotion(make_shared<Apprehension>());
  agentHanna->AddAvailableEmotion(make_shared<Sadness>());

  agentBob->perceiveModules.push_back(make_unique<DDelayPerceive>());
  agentHanna->perceiveModules.push_back(make_unique<DDelayPerceive>());
  agentBob->performModules.push_back(make_unique<DPerform>());
  agentHanna->performModules.push_back(make_unique<DPerform>());

  switch (type) {
    case SceneType::NO_ANTICIPATION:
      agentBob->interpretModules.push_back(
          make_unique<NoAnticipation::CoopSceneBobReact>());
      agentBob->interpretModules.push_back(make_unique<CoopSceneBobDecide>());
      agentBob->AddAvailableAction(make_shared<NoAnticipation::LongWalk>());
      agentBob->AddAvailableAction(
          make_shared<NoAnticipation::Follow>(agentHanna));
      agentHanna->interpretModules.push_back(
          make_unique<NoAnticipation::CoopSceneHannaReact>());
      agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaDecide>());
      agentHanna->AddAvailableAction(make_shared<NoAnticipation::LongWalk>());
      agentHanna->AddAvailableAction(
          make_shared<NoAnticipation::Follow>(agentBob));
      break;
    case SceneType::SCREENING:
      agentBob->interpretModules.push_back(
          make_unique<Screening::CoopSceneBobReact>());
      agentBob->interpretModules.push_back(make_unique<CoopSceneBobDecide>());
      agentBob->AddAvailableAction(make_shared<Screening::LongWalk>());
      agentBob->AddAvailableAction(make_shared<Screening::Follow>(agentHanna));
      agentHanna->interpretModules.push_back(
          make_unique<Screening::CoopSceneHannaReact>());
      agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaDecide>());
      agentHanna->AddAvailableAction(make_shared<Screening::LongWalk>());
      agentHanna->AddAvailableAction(make_shared<Screening::Follow>(agentBob));
      break;
    case SceneType::FULL_MODEL:
    default:
      agentBob->interpretModules.push_back(make_unique<CoopSceneBobReact>());
      agentBob->interpretModules.push_back(make_unique<CoopSceneBobDecide>());
      agentBob->AddAvailableAction(make_shared<LongWalk>());
      agentBob->AddAvailableAction(make_shared<Follow>(agentHanna));
      agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaReact>());
      agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaDecide>());
      agentHanna->AddAvailableAction(make_shared<LongWalk>());
      agentHanna->AddAvailableAction(make_shared<Follow>(agentBob));
      break;
  }

  agentBob->Initialize();
  worldManager->agents.push_back(agentBob);
  agentHanna->Initialize();
  worldManager->agents.push_back(agentHanna);

  return worldManager;
}

shared_ptr<TWorldManager> WorldHolder::CreateWorldCoop() {
  TTime::SetTimeCalculator(std::make_shared<TChronoTimeCalculator>());

  auto worldManager = make_shared<TWorldManager>();
  worldManager->description =
      "This scenario contains 2 agents, Bob and Hanna.\n The agents are near a "
      "rope bridge.";

  auto agentBob = make_shared<TAgent>();
  auto agentHanna = make_shared<TAgent>();
  agentBob->name = string("Bob");
  agentBob->perceiveModules.push_back(make_unique<DDelayPerceive>());
  agentBob->interpretModules.push_back(make_unique<CoopSceneBobReact>());
  agentBob->interpretModules.push_back(make_unique<CoopSceneBobDecide>());
  agentBob->performModules.push_back(make_unique<DPerform>());
  agentBob->AddAvailableAction(make_shared<LongWalk>());
  agentBob->AddAvailableAction(make_shared<Follow>(agentHanna));
  agentBob->AddAvailableEmotion(make_shared<Confidence>());
  agentBob->AddAvailableEmotion(make_shared<Fear>());
  agentBob->AddAvailableEmotion(make_shared<Happiness>());
  agentBob->AddAvailableEmotion(make_shared<Relief>());
  agentBob->AddAvailableEmotion(make_shared<Apprehension>());
  agentBob->AddAvailableEmotion(make_shared<Sadness>());
  agentBob->Initialize();
  worldManager->agents.push_back(agentBob);

  agentHanna->name = string("Hanna");
  agentHanna->perceiveModules.push_back(make_unique<DDelayPerceive>());
  agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaReact>());
  agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaDecide>());
  agentHanna->performModules.push_back(make_unique<DPerform>());
  agentHanna->AddAvailableAction(make_shared<LongWalk>());
  agentHanna->AddAvailableAction(make_shared<Follow>(agentBob));
  agentHanna->AddAvailableEmotion(make_shared<Confidence>());
  agentHanna->AddAvailableEmotion(make_shared<Fear>());
  agentHanna->AddAvailableEmotion(make_shared<Happiness>());
  agentHanna->AddAvailableEmotion(make_shared<Relief>());
  agentHanna->AddAvailableEmotion(make_shared<Apprehension>());
  agentHanna->AddAvailableEmotion(make_shared<Sadness>());
  agentHanna->Initialize();
  worldManager->agents.push_back(agentHanna);

  return worldManager;
}

shared_ptr<TWorldManager> WorldHolder::CreateWorldCoopNoAnticipation() {
  TTime::SetTimeCalculator(make_shared<TChronoTimeCalculator>());

  auto worldManager = make_shared<TWorldManager>();
  worldManager->description =
      "This scenario contains 2 agents, Bob and Hanna.\n The agents are near a "
      "rope bridge.";

  auto agentBob = make_shared<TAgent>();
  auto agentHanna = make_shared<TAgent>();
  agentBob->name = string("Bob");
  agentBob->perceiveModules.push_back(make_unique<DDelayPerceive>());
  agentBob->interpretModules.push_back(
      make_unique<NoAnticipation::CoopSceneBobReact>());
  agentBob->interpretModules.push_back(make_unique<CoopSceneBobDecide>());
  agentBob->performModules.push_back(make_unique<DPerform>());
  agentBob->AddAvailableAction(make_shared<NoAnticipation::LongWalk>());
  agentBob->AddAvailableAction(make_shared<NoAnticipation::Follow>(agentHanna));
  agentBob->AddAvailableEmotion(make_shared<Confidence>());
  agentBob->AddAvailableEmotion(make_shared<Fear>());
  agentBob->AddAvailableEmotion(make_shared<Happiness>());
  agentBob->AddAvailableEmotion(make_shared<Relief>());
  agentBob->AddAvailableEmotion(make_shared<Apprehension>());
  agentBob->AddAvailableEmotion(make_shared<Sadness>());
  agentBob->Initialize();
  worldManager->agents.push_back(agentBob);

  agentHanna->name = string("Hanna");
  agentHanna->perceiveModules.push_back(make_unique<DDelayPerceive>());
  agentHanna->interpretModules.push_back(
      make_unique<NoAnticipation::CoopSceneHannaReact>());
  agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaDecide>());
  agentHanna->performModules.push_back(make_unique<DPerform>());
  agentHanna->AddAvailableAction(make_shared<NoAnticipation::LongWalk>());
  agentHanna->AddAvailableAction(make_shared<NoAnticipation::Follow>(agentBob));
  agentHanna->AddAvailableEmotion(make_shared<Confidence>());
  agentHanna->AddAvailableEmotion(make_shared<Fear>());
  agentHanna->AddAvailableEmotion(make_shared<Happiness>());
  agentHanna->AddAvailableEmotion(make_shared<Relief>());
  agentHanna->AddAvailableEmotion(make_shared<Apprehension>());
  agentHanna->AddAvailableEmotion(make_shared<Sadness>());
  agentHanna->Initialize();
  worldManager->agents.push_back(agentHanna);

  return worldManager;
}

shared_ptr<TWorldManager> WorldHolder::CreateWorldCoopScreening() {
  TTime::SetTimeCalculator(make_shared<TChronoTimeCalculator>());

  auto worldManager = make_shared<TWorldManager>();
  worldManager->description =
      "This scenario contains 2 agents, Bob and Hanna.\n The agents are near a "
      "rope bridge.";

  auto agentBob = make_shared<TAgent>();
  auto agentHanna = make_shared<TAgent>();
  agentBob->name = string("Bob");
  agentBob->perceiveModules.push_back(make_unique<DDelayPerceive>());
  agentBob->interpretModules.push_back(make_unique<Screening::CoopSceneBobReact>());
  agentBob->interpretModules.push_back(make_unique<CoopSceneBobDecide>());
  agentBob->performModules.push_back(make_unique<DPerform>());
  agentBob->AddAvailableAction(make_shared<Screening::LongWalk>());
  agentBob->AddAvailableAction(make_shared<Screening::Follow>(agentHanna));
  agentBob->AddAvailableEmotion(make_shared<Confidence>());
  agentBob->AddAvailableEmotion(make_shared<Fear>());
  agentBob->AddAvailableEmotion(make_shared<Happiness>());
  agentBob->AddAvailableEmotion(make_shared<Relief>());
  agentBob->AddAvailableEmotion(make_shared<Apprehension>());
  agentBob->AddAvailableEmotion(make_shared<Sadness>());
  agentBob->Initialize();
  worldManager->agents.push_back(agentBob);

  agentHanna->name = string("Hanna");
  agentHanna->perceiveModules.push_back(make_unique<DDelayPerceive>());
  agentHanna->interpretModules.push_back(
      make_unique<Screening::CoopSceneHannaReact>());
  agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaDecide>());
  agentHanna->performModules.push_back(make_unique<DPerform>());
  agentHanna->AddAvailableAction(make_shared<Screening::LongWalk>());
  agentHanna->AddAvailableAction(make_shared<Screening::Follow>(agentBob));
  agentHanna->AddAvailableEmotion(make_shared<Confidence>());
  agentHanna->AddAvailableEmotion(make_shared<Fear>());
  agentHanna->AddAvailableEmotion(make_shared<Happiness>());
  agentHanna->AddAvailableEmotion(make_shared<Relief>());
  agentHanna->AddAvailableEmotion(make_shared<Apprehension>());
  agentHanna->AddAvailableEmotion(make_shared<Sadness>());
  agentHanna->Initialize();
  worldManager->agents.push_back(agentHanna);

  return worldManager;
}
