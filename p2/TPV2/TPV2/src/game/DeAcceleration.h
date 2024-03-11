#pragma once
#include "PhysicsComponent.h"
#include "Container.h"

//desacelera el caza autom�ticamente en cada iteraci�n del juego ?��?
class DeAcceleration : public PhysicsComponent
{
public:
	DeAcceleration() = default;
	~DeAcceleration() override = default;
	void update(Container* o) override;

private:
	float deAcceleration_ = 0.995f;
};

