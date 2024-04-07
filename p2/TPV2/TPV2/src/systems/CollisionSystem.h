#pragma once
#include "../ecs/System.h"


class CollisionSystem : public ecs::System {
public:
    __SYSID_DECL__(ecs::sys::COLLISIONS);

    CollisionSystem();
    ~CollisionSystem();

    void initSystem() override;
    void update() override;

    void recieve(const Message&) override;

private:


};