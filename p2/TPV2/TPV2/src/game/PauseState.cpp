#include "PauseState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

PauseState::PauseState()
{
	
}

PauseState::~PauseState() {}

void PauseState::enter()
{
	// pausa el tiempo al entrar al estado
	sdlutils().virtualTimer().pause();

	//sdlutils().soundEffects().at("chomp").pauseChannel();

}

void PauseState::update()
{
	// si se pulsa cualquier tecla cambia a estado running
	if (ih().keyDownEvent()) {
		Game::instance()->setState(Game::RUNNING);
	}

}

void PauseState::leave()
{
	// reanuda el tiempo al salir del estado
	sdlutils().virtualTimer().resume();
}