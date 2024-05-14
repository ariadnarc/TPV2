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
class CollisionSystem;
class RenderSystem;

/// <summary>
/// El método init tiene que crear los sistemas y los estados.
/// El bucle principal tiene que incluir sólo una llamada al update del estado actual
/// y a flush del Manager para enviar mensajes pendientes(si usas el mecanismo de
/// enviar mensajes con delay).
/// El destructor tiene que liberar la memoria de los estados.
/// </summary>

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
	CollisionSystem* collisionSystem;
	RenderSystem* renderSystem;

};