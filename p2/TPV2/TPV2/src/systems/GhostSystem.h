#pragma once
#include "../ecs/System.h"

class Vector2D;

class GhostSystem : public ecs::System {
public:
    __SYSID_DECL__(ecs::sys::GHOST);

    GhostSystem();
    ~GhostSystem();

    void initSystem() override;
    void update() override;

    void recieve(const Message&) override;

    void addGhost();

private:
    int esquina;

    int genTime = 5000;
    int lastTimeGenerated = 0;

    bool pcImmune;
};