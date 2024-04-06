// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

#include "RunningState.h"
#include "NewRoundState.h"
#include "NewGameState.h"

#include "../systems/PacManSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/FoodSystem.h"
#include "../systems/ImmunitySystem.h"
#include "../systems/CollisionSystem.h"
#include "../systems/RenderSystem.h"

using ecs::Manager;

Game::Game() :
	mngr_(new Manager()), 
	ihdlr(ih()), 
	currentState(nullptr), 
	pausedState(nullptr), 
	runningState(nullptr), 
	newgameState(nullptr), 
	newroundState(nullptr), 
	gameoverState(nullptr) {

}

Game::~Game() {

	//delete de los estados
	delete pausedState;
	delete runningState;
	delete newgameState;
	delete newroundState;
	delete gameoverState;

	//delete del manager
	delete mngr_;

}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("ASTEROIDS", 800, 600,
		"resources/config/pacman.resources.json", "resources/config/pacman.config.json");

	//systems
	pacManSystem = mngr_->addSystem<PacManSystem>();
	//ghostSystem = mngr_->addSystem<GhostSystem>();
	//foodSystem = mngr_->addSystem<FoodSystem>();
	//immunitySystem = mngr_->addSystem<ImmunitySystem>();
	//collisionsSystem = mngr_->addSystem<CollisionsSystem>();
	//renderSystem = mngr_->addSystem<RenderSystem>();

	//gamestates
	newgameState = new NewGameState();
	newroundState = new NewRoundState();
	runningState = new RunningState(pacManSystem, ghostSystem, foodSystem, immunitySystem, collisionsSystem, renderSystem);

	currentState = newgameState;
	newgameState->enter();

}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto& ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		//clear rendering
		sdlutils().clearRenderer();

		// refresh the input handler
		ihdlr.refresh();

		//exit game
		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		//update state
		currentState->update();

		//render
		sdlutils().presentRenderer();


		//envio de mensajes
		mngr_->flushMessagesWithSwap();

		//eliminar entidades muertas
		mngr_->refresh();

		//sleep the process
		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}