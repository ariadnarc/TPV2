#pragma once
#include "GameState.h"

class Transform;

class PacManSystem;
class GhostSystem;
class FoodSystem;
class ImmunitySystem;
class CollisionSystem;
class RenderSystem;


class RunningState :
	public GameState
{

public:

	RunningState(PacManSystem*, GhostSystem*, FoodSystem*,
		ImmunitySystem*, CollisionSystem*, RenderSystem*);
	~RunningState();

	void update() override;
	void enter() override;
	void leave() override;

private:


	PacManSystem* pacManSystem;
	GhostSystem* ghostSystem;
	FoodSystem* foodSystem;
	ImmunitySystem* immunitySystem;
	CollisionSystem* collisionSystem;
	RenderSystem* renderSystem;
};
