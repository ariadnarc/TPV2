
#pragma once
#include "../ecs/System.h"

class Transform;

/// <summary>
/// El método update mueve el PacMan. 
/// Cuando empieza una nueva ronda resetea su posición.
/// Cuando empieza una partida resetea las vidas.
/// </summary>
 
class PacManSystem :
    public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::PACMAN);

    PacManSystem();
    ~PacManSystem() {};

    void initSystem() override;
    void update() override;

    void recieve(const Message&) override;

private:
    Transform* pmTR_;

    //----DATOS DEL PACMAN  
    float speed = 3.0f;

    void resetPos();
};
