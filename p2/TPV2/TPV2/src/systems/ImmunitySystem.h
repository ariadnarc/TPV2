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
    void update() override;
    void recieve(const Message&) override;

    bool getImmunity() { return immunity_; }
private:
    bool immunity_;
    int invulnerabilityTime_;
    int currentTime;
};