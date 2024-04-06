#pragma once
#include "GameState.h"

class NewRoundState :
	public GameState
{
public:
	NewRoundState();
	~NewRoundState();

	void update() override;
	void enter() override;
	void leave() override;

private:
};