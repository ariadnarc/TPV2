// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_stdinc.h>
#include "../utils/Singleton.h"

class Networking;
class LittleWolf;

class Game : public Singleton<Game>{
	friend Singleton<Game>;
	Game();
public:
	virtual ~Game();
	bool init(char* host, Uint16 port);
	void start();

	Networking& getNet() 
	{
		return *net_;
	}

	LittleWolf& getLW() 
	{
		return *lw_;
	}

private:
	LittleWolf* lw_;
	Networking* net_;
};

