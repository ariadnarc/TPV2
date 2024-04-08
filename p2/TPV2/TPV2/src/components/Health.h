
#pragma once
#include "../ecs/Component.h"

class Texture;

struct HealthComponent :
    public ecs::Component
{
public:
    __CMPID_DECL__(ecs::cmp::HEALTH)

        HealthComponent(Texture* tex);
    ~HealthComponent();

    void render() override;

    void setLifes(int n) { lifes_ = n; }
    int getLifes() { return lifes_; }
private:
    Texture* tex_;

    int iniX_;
    int iniY_;
    int lifes_;
    float scale_;
    float offset_;
};
