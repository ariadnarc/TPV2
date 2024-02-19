#pragma once
#include "PhysicsComponent.h"
#include "Container.h"

//desacelera el caza automáticamente en cada iteración del juego ?¿¿?
class DeAcceleration : public PhysicsComponent
{
public:
	DeAcceleration() = default;
	~DeAcceleration() override = default;
	void update(Container* o) override;

private:
	float deAcceleration_ = 0.995f;
};

