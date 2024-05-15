#pragma once
#include "../ecs/System.h"

class Transform;

class CollisionSystem : public ecs::System {
public:
    __SYSID_DECL__(ecs::sys::COLLISIONS);

    CollisionSystem() {};
    ~CollisionSystem() {};

    void initSystem() override;
    // Checkea las colisiones de frutas y fantasmas con el pacman en cada update.
    void update() override;

    // CollisionSystem no recibe nada, solo envia mensajes en fruitCollision(...), ghostCollision(...)
    void recieve(const Message&) override;

    // Envia mensaje _m_PACMAN_FOOD_COLLISION si detecta la colision con el pacman.
    void fruitCollision(ecs::entity_t pacman);
    // Envia mensaje _m_PACMAN_GHOST_COLLISION si detecta la colision con el pacman.
    void ghostCollision(ecs::entity_t pacman);

private:


};