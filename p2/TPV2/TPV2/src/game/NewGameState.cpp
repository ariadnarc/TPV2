#include "NewGameState.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"


NewGameState::NewGameState()
{
	
}

NewGameState::~NewGameState()
{

}

void NewGameState::update()
{
	if (ih().keyDownEvent()) {

		//cambiar al estado newRound
		Game::instance()->setState(Game::NEWROUND);
	}
}

void NewGameState::enter()
{
	//pausa el tiempo
	sdlutils().virtualTimer().pause();
}

void NewGameState::leave()
{
	sdlutils().virtualTimer().resume(); //reanuda el tiempo
}