#pragma once
#include "MissileFacade.h"
#include "../ecs/ecs.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../sdlutils/SDLUtils.h"

class MissileUtils :
    public MissileFacade
{
private:
    ecs::Manager* mngr_;
    RandomNumberGenerator& random_; //para que salga de una esquina random

    int width_ = sdlutils().width();
    int height_ = sdlutils().height();

public:
    MissileUtils();
    ~MissileUtils() override;
    void create_missiles(int n) override;
    void remove_missiles() override;
};

