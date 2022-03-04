#ifndef WORLDHOLDER_H
#define WORLDHOLDER_H

#include "ThreeMotion.h"

class WorldHolder
{
private:
    WorldHolder();
public:
    static std::shared_ptr<ThreeMotion::TWorldManager> CreateWorld();
};

#endif // WORLDHOLDER_H
