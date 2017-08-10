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

    static std::shared_ptr<class Divisaction::DWorldManager> CreateWorld(SceneType type);

    static std::shared_ptr<class Divisaction::DWorldManager> CreateWorldCoop();
    static std::shared_ptr<class Divisaction::DWorldManager> CreateWorldCoopNoAnticipation();
    static std::shared_ptr<class Divisaction::DWorldManager> CreateWorldCoopScreening();
};

#endif // WORLDHOLDER_H
