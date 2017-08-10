#include "worldholder.h"

#include "DivisactionExtras.h"

#include "Modules/DDelayPerceive.h"
#include "Modules/DPerform.h"
#include "Modules/DSingleActionDecide.h"
#include "Modules/DSingleEmotionReact.h"
#include "Modules/DSingleReplyReact.h"

using namespace Divisaction;

WorldHolder::WorldHolder() {}

std::shared_ptr<DWorldManager> WorldHolder::CreateWorld() {
  DTime::setTimeCalculator(std::make_shared<DChronoTimeCalculator>());

  auto worldManager = std::make_shared<DWorldManager>();
  worldManager->description =
      "This scenario contains 2 agents, Bob and Hanna.\n The agents are near a "
      "rope bridge.";

  auto agentBob = std::make_shared<DAgent>();
  auto agentHanna = std::make_shared<DAgent>();

  agentBob->name = std::string("Bob");
  // Each agent has 4 types of modules that determine how the agent works.
  // The Perceive Modules determine how and when the agent perceives the world.
  // The DelayPerceive only tells the agent about new events after a period of
  // time.
  agentBob->perceiveModules.push_back(std::make_unique<DDelayPerceive>());
  // The Interpret Modules should determine what emotions and
  // actions an agent should perform.
  // A React Module is an Interpret Module that determines the emotion
  // an agent is feeling.
  // The SingleEmotionReact selects the first emotion available and executes
  // it once.
  agentBob->interpretModules.push_back(std::make_unique<DSingleEmotionReact>());
  // A Decision Module is an Interpret Module that determines the action
  // an agent is performing.
  // The SingleActionDecide selects the first action available and executes
  // it once.
  agentBob->interpretModules.push_back(std::make_unique<DSingleActionDecide>());
  // The Perform Modules perform the action and emotions and are also tasked
  // with generating the events the agent will send.
  // The Perform executes the action and emotion previously executed.
  agentBob->performModules.push_back(std::make_unique<DPerform>());

  // Create an action
  // In this case is a Long Walk over a the bridge
  std::shared_ptr<DAction> crossBridge = std::make_shared<DAction>();
  crossBridge->setName("Long Walk");

  auto anticipation = std::make_shared<DTimeProgressiveStage>(
      std::string("starts crossing the bridge"), 4000, 10000);
  crossBridge->setStage(DStageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

  auto followThrough = std::make_shared<DTimeProgressiveStage>(
      std::string("nears the end of the bridge"), 4000, 7000);
  crossBridge->setStage(DStageType::FOLLOW_THROUGH, followThrough);

  auto cancel = std::make_shared<DTimeProgressiveStage>(
      std::string(
          "stopped walking abruptly before reaching the end of the bridge"),
      1000, 3000);
  crossBridge->setStage(DStageType::CANCEL, cancel);
  agentBob->addAvailableAction(crossBridge);

  // Create an Emotion
  std::shared_ptr<DEmotion> confidence = std::make_shared<DEmotion>(
      "Confidence", std::make_shared<DTimeProgressiveStage>(
                        std::string("is confident"), 1500, 2000),
      "winks at ");
  agentBob->addAvailableEmotion(confidence);

  agentHanna->name = std::string("Hanna");
  agentHanna->perceiveModules.push_back(std::make_unique<DDelayPerceive>());
  // The SingleReplyReact selects the first emotion available and executes
  // it when another agent's action changes it's state (when starting for example).
  agentHanna->interpretModules.push_back(std::make_unique<DSingleReplyReact>());
  // You may have noticed the this agent doesn't have a Decision Module, that is
  // ok, all modules are optional, but of course this means that the agent will
  // not choose an action.
  agentHanna->performModules.push_back(std::make_unique<DPerform>());

  // Create an Emotion
  std::shared_ptr<DEmotion> happiness = std::make_shared<DEmotion>(
      "Happiness", std::make_shared<DTimeProgressiveStage>(
                       std::string("is happy"), 1500, 2000),
      "smiles at ");
  agentHanna->addAvailableEmotion(happiness);

  // Every agent needs to be initialized, this is because the mental model needs
  // to be passed to each sub component.
  agentBob->initialize();
  agentHanna->initialize();

  worldManager->agents.push_back(agentBob);
  worldManager->agents.push_back(agentHanna);

  return worldManager;
}
