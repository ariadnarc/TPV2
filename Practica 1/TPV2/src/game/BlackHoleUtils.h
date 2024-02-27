#pragma once
#include "BlackHoleFacade.h"
#include "../sdlutils/RandomNumberGenerator.h"

//hereda de facade
class BlackHoleUtils :
    public BlackHoleFacade
{
    ecs::Manager* mngr_;
    RandomNumberGenerator& random_;

public:
    BlackHoleUtils();
    ~BlackHoleUtils() override;
    void create_blackholes(int n) override;
    void remove_all_blackholes() override;
};

