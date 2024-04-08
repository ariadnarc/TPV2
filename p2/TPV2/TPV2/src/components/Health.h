#pragma once
#include "../ecs/Component.h"
#include <iostream>

class Texture;

class Health :
    public ecs::Component
{
public:
    __CMPID_DECL__(ecs::cmp::HEALTH);

    Health(std::string name, float scale);
    ~Health();

    void render() override;

    int getCurrentLifes() { return currentLifes; }

    void decreaseLifes(int n = 1) { currentLifes -= n; }

    void resetLifes() { currentLifes = maxLifes; }

    void setLifes(int n) { currentLifes = n; }

    //private: ahora es public

    Texture* healthTexture;
    int maxLifes = 3;
    int currentLifes = 0;

    int initialY = 10;
    int initialX = 3;

    float offSetX;
    float scale = 0.35;
};
