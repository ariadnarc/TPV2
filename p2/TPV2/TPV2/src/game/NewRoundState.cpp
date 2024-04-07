#include "NewRoundState.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"

NewRoundState::NewRoundState()
{
}

NewRoundState::~NewRoundState()
{
}

void NewRoundState::update()
{
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_RETURN)) {

		Game::instance()->setState(Game::RUNNING);

		
	}
}

void NewRoundState::enter()
{
	sdlutils().virtualTimer().pause();
}

void NewRoundState::leave()
{
	sdlutils().virtualTimer().resume();
}
