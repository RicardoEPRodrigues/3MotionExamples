#ifndef WORLDHOLDER_H
#define WORLDHOLDER_H

#include "Divisaction.h"
#include "DivisactionExtras.h"

#include "Modules/CoopSceneBobDecide.h"
#include "Modules/CoopSceneBobReact.h"
#include "Modules/CoopSceneHannaDecide.h"
#include "Modules/CoopSceneHannaReact.h"
#include "Modules/DelayPerceive.h"
#include "Modules/Perform.h"

class WorldHolder
{
private:
    WorldHolder();
public:
    static std::shared_ptr<class Divisaction::WorldManager> CreateWorld();
};

#endif // WORLDHOLDER_H
