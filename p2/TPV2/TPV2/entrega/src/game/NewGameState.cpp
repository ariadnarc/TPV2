#include "NewGameState.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/messages.h"
#include "../ecs/Entity.h"
#include "Game.h"


NewGameState::NewGameState() :
	msg_(&sdlutils().msgs().at("PressAnyKey"))
{
	float x = (sdlutils().width() - msg_->width()) / 2;
	float y = (sdlutils().height() - msg_->height()) / 2;
	dest_ = build_sdlrect(x, y, msg_->width(), msg_->height());

	sdlutils().soundEffects().at("intro").play();
}

NewGameState::~NewGameState()
{

}

void NewGameState::update()
{
	if (ih().keyDownEvent()) {
		Message newGameMsg;
		newGameMsg.id = _m_NEW_GAME;

		Game::instance()->getMngr()->send(newGameMsg);
		Game::instance()->setState(Game::NEWROUND);

		//cambiar al estado newRound
	}
	msg_->render(dest_);
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