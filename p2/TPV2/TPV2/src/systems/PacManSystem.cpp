// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

PacManSystem::PacManSystem() :
	pmTR_(nullptr) {
}

void PacManSystem::initSystem() {
	std::cout << "inicia el sistem PacManSystem" << std::endl;

	auto pacman = mngr_->addEntity();
	mngr_->setHandler(ecs::hdlr::PACMAN, pacman);

	mngr_->addComponent<HealthComponent>(pacman, &sdlutils().images().at("heart"));

	pmTR_ = mngr_->addComponent<Transform>(pacman);
	auto s = 50.0f;
	auto x = ((sdlutils().width() - s) / 2.0f) - 20;
	auto y = (sdlutils().height() - s) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

	mngr_->addComponent<ImageWithFrames>(pacman, &sdlutils().images().at("spriteSheet"), 8, 8, 0, 0, 1024 / 8, 1024 / 8, 0, 0, 1, 4);
}

void PacManSystem::update() {

	auto& ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			pmTR_->rot_ += 90;

			// also rotate the PacMan so it looks in the same
			// direction where it moves
			pmTR_->getVel() = pmTR_->getVel().rotate(90);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left

			pmTR_->rot_ -= 90;
			// also rotate the PacMan so it looks in the same
			// direction where it moves

			pmTR_->getVel() = pmTR_->getVel().rotate(-90);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed

			// empieza a moverse con la rotacion que tenga en el momento
			pmTR_->getVel().set(0, -speed);
			pmTR_->getVel() = pmTR_->getVel().rotate(pmTR_->rot_);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) {

			// si pulsas downarrow se deja de mover
			pmTR_->getVel().set(0, 0);
		}
		sdlutils().soundEffects().at("chomp").play();
	}

	// move the pacman
	pmTR_->pos_ = pmTR_->pos_ + pmTR_->vel_;

	// check left/right borders
	if (pmTR_->pos_.getX() < 0) {
		pmTR_->pos_.setX(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	}
	else if (pmTR_->pos_.getX() + pmTR_->width_ > sdlutils().width()) {
		pmTR_->pos_.setX(sdlutils().width() - pmTR_->width_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (pmTR_->pos_.getY() < 0) {
		pmTR_->pos_.setY(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	}
	else if (pmTR_->pos_.getY() + pmTR_->height_ > sdlutils().height()) {
		pmTR_->pos_.setY(sdlutils().height() - pmTR_->height_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}

}

void PacManSystem::recieve(const Message& msg)
{
	auto health = mngr_->getComponent<HealthComponent>(mngr_->getHandler(ecs::hdlr::PACMAN));
	switch (msg.id)
	{
	case _m_PACMAN_GHOST_COLLISION:

		sdlutils().soundEffects().at("death").play();

		if (!msg.ghost_collision_data.blue) // si el ghost no es blue
		{
			health->setLifes(health->getLifes() - 1); //resta vida al pacman

			Message msg;
			if (health->getLifes() < 1) // si tenemos menos que 1 vida
			{
				msg.id = _m_GAME_OVER;				//acaba el juego
				mngr_->send(msg);

				Game::instance()->setState(Game::State::GAMEOVER);
			}
			else // si tenemos 1 o mas vidas
			{
				msg.id = _m_ROUND_OVER; //acaba ronda -> pasa al estado de new round state
				mngr_->send(msg);

				Game::instance()->setState(Game::State::NEWROUND);
			}

			std::cout << health->getLifes() << std::endl;
		}

		break;

	case _m_ROUND_START:
		std::cout << "PacmanSystem recibe _m_ROUND_START" << std::endl;
		resetPos();
		break;

	case _m_NEW_GAME:
		health->setLifes(3);
		break;

	default:
		break;
	}
}

void PacManSystem::resetPos()
{
	auto s = 50.0f;
	auto x = ((sdlutils().width() - s) / 2.0f) - 20;
	auto y = (sdlutils().height() - s) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
}
