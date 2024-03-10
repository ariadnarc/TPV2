#pragma once
#include "BlackHoleFacade.h"

namespace ecs {
    class Manager;
}

class RandomNumberGenerator;

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

