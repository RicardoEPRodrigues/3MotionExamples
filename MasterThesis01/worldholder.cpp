#include "worldholder.h"

#include "DivisactionExtras.h"

#include "Modules/DelayPerceive.h"
#include "Modules/Perform.h"

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

using namespace Divisaction;
using namespace std;

WorldHolder::WorldHolder() {}

shared_ptr<WorldManager> WorldHolder::CreateWorld(SceneType type) {
  Time::setTimeCalculator(new ChronoTimeCalculator());

  auto worldManager = make_shared<WorldManager>();
  worldManager->description =
      "This scenario contains 2 agents, Bob and Hanna.\n The agents are near a "
      "rope bridge.";

  auto agentBob = make_shared<Agent>();
  auto agentHanna = make_shared<Agent>();
  agentBob->name = string("Bob");
  agentBob->addAvailableEmotion(make_shared<Confidence>());
  agentBob->addAvailableEmotion(make_shared<Fear>());
  agentBob->addAvailableEmotion(make_shared<Happiness>());
  agentBob->addAvailableEmotion(make_shared<Relief>());
  agentBob->addAvailableEmotion(make_shared<Apprehension>());
  agentBob->addAvailableEmotion(make_shared<Sadness>());

  agentHanna->name = string("Hanna");
  agentHanna->addAvailableEmotion(make_shared<Confidence>());
  agentHanna->addAvailableEmotion(make_shared<Fear>());
  agentHanna->addAvailableEmotion(make_shared<Happiness>());
  agentHanna->addAvailableEmotion(make_shared<Relief>());
  agentHanna->addAvailableEmotion(make_shared<Apprehension>());
  agentHanna->addAvailableEmotion(make_shared<Sadness>());

  agentBob->perceiveModules.push_back(make_unique<DelayPerceive>());
  agentHanna->perceiveModules.push_back(make_unique<DelayPerceive>());
  agentBob->performModules.push_back(make_unique<Perform>());
  agentHanna->performModules.push_back(make_unique<Perform>());

  switch (type) {
    case SceneType::NO_ANTICIPATION:
      agentBob->interpretModules.push_back(
          make_unique<NoAnticipation::CoopSceneBobReact>());
      agentBob->interpretModules.push_back(make_unique<CoopSceneBobDecide>());
      agentBob->addAvailableAction(make_shared<NoAnticipation::LongWalk>());
      agentBob->addAvailableAction(
          make_shared<NoAnticipation::Follow>(agentHanna));
      agentHanna->interpretModules.push_back(
          make_unique<NoAnticipation::CoopSceneHannaReact>());
      agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaDecide>());
      agentHanna->addAvailableAction(make_shared<NoAnticipation::LongWalk>());
      agentHanna->addAvailableAction(
          make_shared<NoAnticipation::Follow>(agentBob));
      break;
    case SceneType::SCREENING:
      agentBob->interpretModules.push_back(
          make_unique<Screening::CoopSceneBobReact>());
      agentBob->interpretModules.push_back(make_unique<CoopSceneBobDecide>());
      agentBob->addAvailableAction(make_shared<Screening::LongWalk>());
      agentBob->addAvailableAction(make_shared<Screening::Follow>(agentHanna));
      agentHanna->interpretModules.push_back(
          make_unique<Screening::CoopSceneHannaReact>());
      agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaDecide>());
      agentHanna->addAvailableAction(make_shared<Screening::LongWalk>());
      agentHanna->addAvailableAction(make_shared<Screening::Follow>(agentBob));
      break;
    case SceneType::FULL_MODEL:
    default:
      agentBob->interpretModules.push_back(make_unique<CoopSceneBobReact>());
      agentBob->interpretModules.push_back(make_unique<CoopSceneBobDecide>());
      agentBob->addAvailableAction(make_shared<LongWalk>());
      agentBob->addAvailableAction(make_shared<Follow>(agentHanna));
      agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaReact>());
      agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaDecide>());
      agentHanna->addAvailableAction(make_shared<LongWalk>());
      agentHanna->addAvailableAction(make_shared<Follow>(agentBob));
      break;
  }

  agentBob->initialize();
  worldManager->agents.push_back(agentBob);
  agentHanna->initialize();
  worldManager->agents.push_back(agentHanna);

  return worldManager;
}

shared_ptr<WorldManager> WorldHolder::CreateWorldCoop() {
  Time::setTimeCalculator(new ChronoTimeCalculator());

  auto worldManager = make_shared<WorldManager>();
  worldManager->description =
      "This scenario contains 2 agents, Bob and Hanna.\n The agents are near a "
      "rope bridge.";

  auto agentBob = make_shared<Agent>();
  auto agentHanna = make_shared<Agent>();
  agentBob->name = string("Bob");
  agentBob->perceiveModules.push_back(make_unique<DelayPerceive>());
  agentBob->interpretModules.push_back(make_unique<CoopSceneBobReact>());
  agentBob->interpretModules.push_back(make_unique<CoopSceneBobDecide>());
  agentBob->performModules.push_back(make_unique<Perform>());
  agentBob->addAvailableAction(make_shared<LongWalk>());
  agentBob->addAvailableAction(make_shared<Follow>(agentHanna));
  agentBob->addAvailableEmotion(make_shared<Confidence>());
  agentBob->addAvailableEmotion(make_shared<Fear>());
  agentBob->addAvailableEmotion(make_shared<Happiness>());
  agentBob->addAvailableEmotion(make_shared<Relief>());
  agentBob->addAvailableEmotion(make_shared<Apprehension>());
  agentBob->addAvailableEmotion(make_shared<Sadness>());
  agentBob->initialize();
  worldManager->agents.push_back(agentBob);

  agentHanna->name = string("Hanna");
  agentHanna->perceiveModules.push_back(make_unique<DelayPerceive>());
  agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaReact>());
  agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaDecide>());
  agentHanna->performModules.push_back(make_unique<Perform>());
  agentHanna->addAvailableAction(make_shared<LongWalk>());
  agentHanna->addAvailableAction(make_shared<Follow>(agentBob));
  agentHanna->addAvailableEmotion(make_shared<Confidence>());
  agentHanna->addAvailableEmotion(make_shared<Fear>());
  agentHanna->addAvailableEmotion(make_shared<Happiness>());
  agentHanna->addAvailableEmotion(make_shared<Relief>());
  agentHanna->addAvailableEmotion(make_shared<Apprehension>());
  agentHanna->addAvailableEmotion(make_shared<Sadness>());
  agentHanna->initialize();
  worldManager->agents.push_back(agentHanna);

  return worldManager;
}

shared_ptr<WorldManager> WorldHolder::CreateWorldCoopNoAnticipation() {
  Time::setTimeCalculator(new ChronoTimeCalculator());

  auto worldManager = make_shared<WorldManager>();
  worldManager->description =
      "This scenario contains 2 agents, Bob and Hanna.\n The agents are near a "
      "rope bridge.";

  auto agentBob = make_shared<Agent>();
  auto agentHanna = make_shared<Agent>();
  agentBob->name = string("Bob");
  agentBob->perceiveModules.push_back(make_unique<DelayPerceive>());
  agentBob->interpretModules.push_back(
      make_unique<NoAnticipation::CoopSceneBobReact>());
  agentBob->interpretModules.push_back(make_unique<CoopSceneBobDecide>());
  agentBob->performModules.push_back(make_unique<Perform>());
  agentBob->addAvailableAction(make_shared<NoAnticipation::LongWalk>());
  agentBob->addAvailableAction(make_shared<NoAnticipation::Follow>(agentHanna));
  agentBob->addAvailableEmotion(make_shared<Confidence>());
  agentBob->addAvailableEmotion(make_shared<Fear>());
  agentBob->addAvailableEmotion(make_shared<Happiness>());
  agentBob->addAvailableEmotion(make_shared<Relief>());
  agentBob->addAvailableEmotion(make_shared<Apprehension>());
  agentBob->addAvailableEmotion(make_shared<Sadness>());
  agentBob->initialize();
  worldManager->agents.push_back(agentBob);

  agentHanna->name = string("Hanna");
  agentHanna->perceiveModules.push_back(make_unique<DelayPerceive>());
  agentHanna->interpretModules.push_back(
      make_unique<NoAnticipation::CoopSceneHannaReact>());
  agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaDecide>());
  agentHanna->performModules.push_back(make_unique<Perform>());
  agentHanna->addAvailableAction(make_shared<NoAnticipation::LongWalk>());
  agentHanna->addAvailableAction(make_shared<NoAnticipation::Follow>(agentBob));
  agentHanna->addAvailableEmotion(make_shared<Confidence>());
  agentHanna->addAvailableEmotion(make_shared<Fear>());
  agentHanna->addAvailableEmotion(make_shared<Happiness>());
  agentHanna->addAvailableEmotion(make_shared<Relief>());
  agentHanna->addAvailableEmotion(make_shared<Apprehension>());
  agentHanna->addAvailableEmotion(make_shared<Sadness>());
  agentHanna->initialize();
  worldManager->agents.push_back(agentHanna);

  return worldManager;
}

shared_ptr<WorldManager> WorldHolder::CreateWorldCoopScreening() {
  Time::setTimeCalculator(new ChronoTimeCalculator());

  auto worldManager = make_shared<WorldManager>();
  worldManager->description =
      "This scenario contains 2 agents, Bob and Hanna.\n The agents are near a "
      "rope bridge.";

  auto agentBob = make_shared<Agent>();
  auto agentHanna = make_shared<Agent>();
  agentBob->name = string("Bob");
  agentBob->perceiveModules.push_back(make_unique<DelayPerceive>());
  agentBob->interpretModules.push_back(make_unique<Screening::CoopSceneBobReact>());
  agentBob->interpretModules.push_back(make_unique<CoopSceneBobDecide>());
  agentBob->performModules.push_back(make_unique<Perform>());
  agentBob->addAvailableAction(make_shared<Screening::LongWalk>());
  agentBob->addAvailableAction(make_shared<Screening::Follow>(agentHanna));
  agentBob->addAvailableEmotion(make_shared<Confidence>());
  agentBob->addAvailableEmotion(make_shared<Fear>());
  agentBob->addAvailableEmotion(make_shared<Happiness>());
  agentBob->addAvailableEmotion(make_shared<Relief>());
  agentBob->addAvailableEmotion(make_shared<Apprehension>());
  agentBob->addAvailableEmotion(make_shared<Sadness>());
  agentBob->initialize();
  worldManager->agents.push_back(agentBob);

  agentHanna->name = string("Hanna");
  agentHanna->perceiveModules.push_back(make_unique<DelayPerceive>());
  agentHanna->interpretModules.push_back(
      make_unique<Screening::CoopSceneHannaReact>());
  agentHanna->interpretModules.push_back(make_unique<CoopSceneHannaDecide>());
  agentHanna->performModules.push_back(make_unique<Perform>());
  agentHanna->addAvailableAction(make_shared<Screening::LongWalk>());
  agentHanna->addAvailableAction(make_shared<Screening::Follow>(agentBob));
  agentHanna->addAvailableEmotion(make_shared<Confidence>());
  agentHanna->addAvailableEmotion(make_shared<Fear>());
  agentHanna->addAvailableEmotion(make_shared<Happiness>());
  agentHanna->addAvailableEmotion(make_shared<Relief>());
  agentHanna->addAvailableEmotion(make_shared<Apprehension>());
  agentHanna->addAvailableEmotion(make_shared<Sadness>());
  agentHanna->initialize();
  worldManager->agents.push_back(agentHanna);

  return worldManager;
}
