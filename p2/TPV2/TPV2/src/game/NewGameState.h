#pragma once

#include "GameState.h"

class NewGameState :
	public GameState
{
public:
	NewGameState();
	~NewGameState();

	void update() override;
	void enter() override;
	void leave() override;

private:

};