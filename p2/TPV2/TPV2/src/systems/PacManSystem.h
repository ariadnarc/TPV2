
#pragma once
#include "../ecs/System.h"

class Transform;

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
    Transform* pmTR_;

    ecs::entity_t pacMan;

    //----DATOS DEL PACMAN  
    int pacmanWidth = 40;
    int pacmanHeight = 40;
    float speed = 3.0f;

    void resetPos();
    void resetLifes();

};
