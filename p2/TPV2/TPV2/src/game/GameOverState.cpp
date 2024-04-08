#include "GameOverState.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/messages.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"
#include "../ecs/Manager.h"

GameOverState::GameOverState() {}

GameOverState::~GameOverState() {}

GameOverState::GameOverState() :
	msg_(&sdlutils().msgs().at("GameOver"))
{
	float x = (sdlutils().width() - msg_->width()) / 2;
	float y = (sdlutils().height() - msg_->height()) / 2;
	dest_ = build_sdlrect(x, y, msg_->width(), msg_->height());
}

void GameOverState::update()
{
	if (ih().keyDownEvent()) {
		Game::instance()->setState(Game::State::NEWGAME);
	}
	msg_->render(dest_);

}

void GameOverState::leave()
{
	// reanuda el tiempo al salir del estado
	sdlutils().virtualTimer().resume();
}