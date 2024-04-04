// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"

#include "Container.h"
#include "GameManager.h"
#include "GameCtrl.h"
#include "ImageRenderer.h"
#include "SimpleMove.h"
#include "FighterCtrl.h"
#include "ShowAtOppositeSide.h"
#include "DeAcceleration.h"

Game::Game() :
	fighter_(nullptr)
		//gm_(nullptr), //
		//leftPaddle_(nullptr), //
		//rightPaddle_(nullptr), //
		//ball_(nullptr) 
		{
}

Game::~Game() {
	// delete all game objects
	for (GameObject *o : objs_) {
		delete o;
	}
}

void Game::init() {

	// initialize the SDL singleton
	SDLUtils::init("Pacman", 800, 600,
			"resources/config/resources.json");

	//crear manager (mirar repo de paula)
	//mngr_ = new Manager();


	//añadir sistemas
	// to dooo
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		for (auto &o : objs_) {
			o->handleInput();
		}

		// update
		for (auto &o : objs_) {
			o->update();
		}

		//checkCollisions();

		sdlutils().clearRenderer();

		// render
		for (auto &o : objs_) {
			o->render();
		}

		sdlutils().presentRenderer();
		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

