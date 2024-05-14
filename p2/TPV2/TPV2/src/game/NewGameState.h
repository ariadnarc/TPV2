#pragma once

#include "../ecs/Component.h"
#include "GameState.h"

class NewGameState :
	public GameState
{
public:
	NewGameState();
	~NewGameState() {};

	void update() override;
	void enter() override;
	void leave() override;

private:
	Texture* msg_;
	SDL_Rect dest_;
};