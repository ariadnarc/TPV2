#include "NewRoundState.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Manager.h"
#include "../ecs/messages.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"

NewRoundState::NewRoundState() :
	msg_(&sdlutils().msgs().at("PressEnter"))
{
	float x = (sdlutils().width() - msg_->width()) / 2;
	float y = (sdlutils().height() - msg_->height()) / 2;
	dest_ = build_sdlrect(x, y, msg_->width(), msg_->height());
}

void NewRoundState::update()
{
	if (ih().isKeyDown(SDL_SCANCODE_RETURN)) {
		Message msg;
		msg.id = _m_ROUND_START;
		Game::instance()->getMngr()->send(msg, true);
		Game::instance()->setState(Game::RUNNING);
	}
	msg_->render(dest_);
}

void NewRoundState::enter()
{
	std::cout << "Estado: NEWROUNDSTATE" << std::endl;
	sdlutils().virtualTimer().pause();
}

void NewRoundState::leave()
{
	sdlutils().virtualTimer().resume();
}
