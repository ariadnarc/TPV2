#pragma once
#include "../ecs/System.h"

class PacManSystem :
    public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::PACMAN);

    PacManSystem();
    ~PacManSystem();

    void initSystem() override;
    void update() override;
    void recieve(const Message&) override;

private:

    ecs::entity_t pacMan;

    //----DATOS DEL PACMAN  
    int pacmanWidth = 40;
    int pacmanHeight = 40;

    void resetPos();
    void resetLifes();

    void pacManMovement();

};
