#include "GameOverState.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

GameOverState::GameOverState() {}

GameOverState::~GameOverState() {}

void GameOverState::enter()
{
	// pausa el tiempo al entrar al estado
	sdlutils().virtualTimer().pause();


}

void GameOverState::update()
{
	// si se pulsa enter pasas al estado newgame
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_RETURN)) {

		Game::instance()->setState(Game::NEWGAME);

	}

}

void GameOverState::leave()
{
	// reanuda el tiempo al salir del estado
	sdlutils().virtualTimer().resume();
}