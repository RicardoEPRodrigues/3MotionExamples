#ifndef WORLDHOLDER_H
#define WORLDHOLDER_H

#include "Divisaction.h"

class WorldHolder
{
private:
    WorldHolder();
public:
    enum SceneType {
        FULL_MODEL,
        NO_ANTICIPATION,
        SCREENING
    };

    static std::shared_ptr<class Divisaction::WorldManager> CreateWorld(SceneType type);

    static std::shared_ptr<class Divisaction::WorldManager> CreateWorldCoop();
    static std::shared_ptr<class Divisaction::WorldManager> CreateWorldCoopNoAnticipation();
    static std::shared_ptr<class Divisaction::WorldManager> CreateWorldCoopScreening();
};

#endif // WORLDHOLDER_H
