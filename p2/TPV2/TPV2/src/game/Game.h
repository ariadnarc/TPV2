// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>
#include "../utils/Singleton.h"
#include "GameState.h"

namespace ecs {
	class Manager;
}

class InputHandler;

class PacManSystem;
class GhostSystem;
class FoodSystem;
class ImmunitySystem;
class CollisionsSystem;
class RenderSystem;



class Game : public Singleton<Game> {
	friend Singleton<Game>;
	Game();
public:

	enum State {
		RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER
	};

	virtual ~Game();
	void init();
	void start();

	inline ecs::Manager* getMngr() {
		return mngr_;
	}

	inline void setState(State s) {
		GameState* new_state = nullptr;
		switch (s) {
		case RUNNING:
			new_state = runningState;
			break;
		case PAUSED:
			new_state = pausedState;
			break;
		case NEWGAME:
			new_state = newgameState;
			break;
		case NEWROUND:
			new_state = newroundState;
			break;
		case GAMEOVER:
			new_state = gameoverState;
			break;
		default:
			break;
		}

		currentState->leave();
		currentState = new_state;
		currentState->enter();
	}
private:

	ecs::Manager* mngr_;
	InputHandler& ihdlr;

	GameState* currentState;
	GameState* pausedState;
	GameState* runningState;
	GameState* newgameState;
	GameState* newroundState;
	GameState* gameoverState;


	PacManSystem* pacManSystem;
	GhostSystem* ghostSystem;
	FoodSystem* foodSystem;
	ImmunitySystem* immunitySystem;
	CollisionsSystem* collisionsSystem;
	RenderSystem* renderSystem;

};