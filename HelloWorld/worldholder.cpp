#include "worldholder.h"

#include "DivisactionExtras.h"

#include "Modules/DelayPerceive.h"
#include "Modules/Perform.h"
#include "Modules/SingleActionDecide.h"
#include "Modules/SingleEmotionReact.h"
#include "Modules/SingleReplyReact.h"

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
  // Each agent has 4 types of modules that determine how the agent works.
  // The Perceive Modules determine how and when the agent perceives the world.
  // The DelayPerceive only tells the agent about new events after a period of
  // time.
  agentBob->perceiveModules.push_back(std::make_unique<DelayPerceive>());
  // The React Modules determine the emotion an agent is feeling.
  // The SingleEmotionReact selects the first emotion available once.
  agentBob->reactModules.push_back(std::make_unique<SingleEmotionReact>());
  // The Decision Modules determine the action an agent is performing.
  // The SingleActionDecide selects the first action available once.
  agentBob->decideModules.push_back(std::make_unique<SingleActionDecide>());
  // The Perform Modules perform the action and emotions and are also tasked
  // with generating the events the agent will send.
  // The Perform executes the action and emotion previously executed.
  agentBob->performModules.push_back(std::make_unique<Perform>());

  // Create an action
  // In this case is a Long Walk over a the bridge
  std::shared_ptr<Action> crossBridge = std::make_shared<Action>();
  crossBridge->setName("Long Walk");

  auto anticipation = std::make_shared<TimeProgressiveStage>(
      std::string("starts crossing the bridge"), 4000, 10000);
  crossBridge->setStage(StageType::ANTICIPATION_INTERRUPTIBLE, anticipation);

  auto followThrough = std::make_shared<TimeProgressiveStage>(
      std::string("nears the end of the bridge"), 4000, 7000);
  crossBridge->setStage(StageType::FOLLOW_THROUGH, followThrough);

  auto cancel = std::make_shared<TimeProgressiveStage>(
      std::string(
          "stopped walking abruptly before reaching the end of the bridge"),
      1000, 3000);
  crossBridge->setStage(StageType::CANCEL, cancel);
  agentBob->addAvailableAction(crossBridge);

  // Create an Emotion
  std::shared_ptr<Emotion> confidence = std::make_shared<Emotion>(
      "Confidence", std::make_shared<TimeProgressiveStage>(
                        std::string("is confident"), 1500, 2000),
      "winks at ");
  agentBob->addAvailableEmotion(confidence);

  agentHanna->perceiveModules.push_back(std::make_unique<DelayPerceive>());
  // The SingleReplyReact selects the first action available once.
  agentHanna->reactModules.push_back(std::make_unique<SingleReplyReact>());
  agentHanna->name = std::string("Hanna");
  // You may have noticed the this agent doesn't have a Decision Module, that is
  // ok, all modules are optional, but of course this means that the agent will
  // not choose an action.
  agentHanna->performModules.push_back(std::make_unique<Perform>());

  // Create an Emotion
  std::shared_ptr<Emotion> happiness = std::make_shared<Emotion>(
      "Happiness", std::make_shared<TimeProgressiveStage>(
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
