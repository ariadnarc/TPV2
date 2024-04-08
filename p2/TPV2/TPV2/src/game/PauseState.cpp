#include "PauseState.h"

#include "../sdlutils/SDLUtils.h"
#include "../ecs/messages.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"
#include "../ecs/Manager.h"

PauseState::PauseState() :
	msg_(&sdlutils().msgs().at("Pause"))
{
	float x = (sdlutils().width() - msg_->width()) / 2;
	float y = (sdlutils().height() - msg_->height()) / 2;
	dest_ = build_sdlrect(x, y, msg_->width(), msg_->height());
}

PauseState::~PauseState() {}

void PauseState::enter()
{
	// pausa el tiempo al entrar al estado
	sdlutils().virtualTimer().pause();

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