// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"
#include "../components/Transform.h"


class FoodSystem : public ecs::System {
public:
    __SYSID_DECL__(ecs::sys::FOOD);

    FoodSystem();
    ~FoodSystem();

    void initSystem() override;
    void update() override;

    void recieve(const Message&) override;

    void addFood(Vector2D pos);
    void createGrid();

private:
    int FRUITCOLS = 8;
    int FRUITROWS = 6;

    float offset = 25;

};