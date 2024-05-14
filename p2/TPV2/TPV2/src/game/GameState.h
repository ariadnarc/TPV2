#pragma once
#include "../sdlutils/SDLUtils.h"

class GameState
{
public:
	virtual void update() = 0;
	virtual void enter() = 0;
	virtual void leave() = 0;
};
