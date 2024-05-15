#pragma once
#include "../ecs/System.h"
class ImmunitySystem :
    public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::IMMUNITY)

    ImmunitySystem();
    ~ImmunitySystem() {};

    void initSystem() override;
    // Manda mensaje cuando acaba la inmunidad.
    void update() override;
    void recieve(const Message&) override;

    // Devuelve si los fantasmas son azules (true) o no (false). Azules implica que pacman es inmune.
    bool getImmunity() { return blue_; } 
private:
    bool blue_;
    int blueTime_;
    int currentTime;
};