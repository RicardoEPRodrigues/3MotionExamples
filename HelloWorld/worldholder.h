#ifndef WORLDHOLDER_H
#define WORLDHOLDER_H

#include "Divisaction.h"

class WorldHolder
{
private:
    WorldHolder();
public:
    static std::shared_ptr<Divisaction::DWorldManager> CreateWorld();
};

#endif // WORLDHOLDER_H
