#ifndef WORLDHOLDER_H
#define WORLDHOLDER_H

#include "ThreeMotion.h"

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

    static std::shared_ptr<class ThreeMotion::TWorldManager> CreateWorld(SceneType type);

    static std::shared_ptr<class ThreeMotion::TWorldManager> CreateWorldCoop();
    static std::shared_ptr<class ThreeMotion::TWorldManager> CreateWorldCoopNoAnticipation();
    static std::shared_ptr<class ThreeMotion::TWorldManager> CreateWorldCoopScreening();
};

#endif // WORLDHOLDER_H
