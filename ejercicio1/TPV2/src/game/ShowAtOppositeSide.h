#pragma once
#include "PhysicsComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "Container.h"

class ShowAtOppositeSide : public PhysicsComponent
{
public:
	ShowAtOppositeSide() = default;
	~ShowAtOppositeSide() override = default;
	void update(Container* o) override;
};