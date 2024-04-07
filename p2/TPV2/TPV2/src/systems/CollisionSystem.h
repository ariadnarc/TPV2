#pragma once
#include "../ecs/System.h"

class Transform;

class CollisionSystem : public ecs::System {
public:
    __SYSID_DECL__(ecs::sys::COLLISIONS);

    CollisionSystem();
    ~CollisionSystem();

    void initSystem() override;
    void update() override;

    void recieve(const Message&) override;

    void fruitCollision(ecs::entity_t pacman);
    void ghostCollision(ecs::entity_t pacman);

private:


};