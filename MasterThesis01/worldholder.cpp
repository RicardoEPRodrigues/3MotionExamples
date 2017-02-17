#include "worldholder.h"

using namespace Divisaction;

WorldHolder::WorldHolder() {}

std::shared_ptr<WorldManager> WorldHolder::CreateWorld() {
  Time::setTimeCalculator(new ChronoTimeCalculator());

  auto worldManager = std::make_shared<WorldManager>();
  worldManager->description =
      "This scenario contains 2 agents, Bob and Hanna.\n The agents are near a "
      "rope bridge.";

  auto agentBob = std::make_shared<Agent>();
  auto agentHanna = std::make_shared<Agent>();
  agentBob->name = std::string("Bob");
  agentBob->perceiveModules.push_back(std::make_unique<DelayPerceive>());
  agentBob->reactModules.push_back(std::make_unique<CoopSceneBobReact>());
  agentBob->decideModules.push_back(std::make_unique<CoopSceneBobDecide>());
  agentBob->performModules.push_back(std::make_unique<Perform>());
  agentBob->addAvailableAction(std::make_shared<LongWalk>());
  agentBob->addAvailableAction(std::make_shared<Follow>(agentHanna));
  agentBob->addAvailableEmotion(std::make_shared<Confidence>());
  agentBob->addAvailableEmotion(std::make_shared<Fear>());
  agentBob->addAvailableEmotion(std::make_shared<Happiness>());
  agentBob->addAvailableEmotion(std::make_shared<Relief>());
  agentBob->addAvailableEmotion(std::make_shared<Apprehension>());
  agentBob->addAvailableEmotion(std::make_shared<Sadness>());
  agentBob->initialize();
  worldManager->agents.push_back(agentBob);

  agentHanna->name = std::string("Hanna");
  agentHanna->perceiveModules.push_back(std::make_unique<DelayPerceive>());
  agentHanna->reactModules.push_back(std::make_unique<CoopSceneHannaReact>());
  agentHanna->decideModules.push_back(std::make_unique<CoopSceneHannaDecide>());
  agentHanna->performModules.push_back(std::make_unique<Perform>());
  agentHanna->addAvailableAction(std::make_shared<LongWalk>());
  agentHanna->addAvailableAction(std::make_shared<Follow>(agentBob));
  agentHanna->addAvailableEmotion(std::make_shared<Confidence>());
  agentHanna->addAvailableEmotion(std::make_shared<Fear>());
  agentHanna->addAvailableEmotion(std::make_shared<Happiness>());
  agentHanna->addAvailableEmotion(std::make_shared<Relief>());
  agentHanna->addAvailableEmotion(std::make_shared<Apprehension>());
  agentHanna->addAvailableEmotion(std::make_shared<Sadness>());
  agentHanna->initialize();
  worldManager->agents.push_back(agentHanna);

  return worldManager;
}
