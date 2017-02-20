#ifndef WORLDHOLDER_H
#define WORLDHOLDER_H

#include "Divisaction.h"

class WorldHolder
{
private:
    WorldHolder();
public:
    static std::shared_ptr<class Divisaction::WorldManager> CreateWorld();
};

#endif // WORLDHOLDER_H
