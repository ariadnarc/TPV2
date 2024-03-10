#pragma once
#include "MissileFacade.h"

namespace ecs {
    class Manager;
}

class RandomNumberGenerator;

class MissileUtils :
    public MissileFacade
{
private:
    ecs::Manager* mngr_;
    RandomNumberGenerator& random_; //para que salga de una esquina random

public:
    MissileUtils();
    ~MissileUtils() override;
    void create_missiles(int n) override;
    void remove_missiles() override;
};

