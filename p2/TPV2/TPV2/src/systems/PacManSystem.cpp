// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

PacManSystem::PacManSystem() :
	pmTR_(nullptr) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	std::cout << "inicia el sistem del pacoman" << std::endl;

	// create the PacMan entity
	//
	auto pacman = mngr_->addEntity();
	float healthImageScale = 0.35;

	int fils = 8;
	int cols = 8;

	int pacmanWidth = 40;
	int pacmanHeight = 40;

	//aniadir componentes
	auto trasnformCmp = mngr_->addComponent<Transform>(pacMan);
	auto imgF_Cmp = mngr_->addComponent<ImageWithFrames>(pacMan, "spriteSheet", fils, cols);
	//auto healthCmp = mngr_->addComponent<Health>(pacMan, "heart", healthImageScale);

	//healthCmp->setLifes(3);

	trasnformCmp->setHeight(pacmanHeight);
	trasnformCmp->setWidth(pacmanWidth);

	trasnformCmp->getPos().set((sdlutils().width() - pacmanWidth) / 2,
		(sdlutils().height() - pacmanHeight) / 2);
	/*
	mngr_->setHandler(ecs::hdlr::PACMAN, pacman);

	pmTR_ = mngr_->addComponent<Transform>(pacman);
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

	mngr_->addComponent<ImageWithFrames>(pacman, &sdlutils().images().at("pacman"), 8, 8, 0, 0, 1024/8, 1024/8, 0, 0, 1, 4);
	//mngr_->addComponent<Image>(pacman, &sdlutils().images().at("pacman"));
	*/
}


void PacManSystem::update() {

	auto& ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT) && !right) { // rotate right
			pmTR_->rot_ += 90;

			// also rotate the PacMan so it looks in the same
			// direction where it moves
			pmTR_->getVel() = pmTR_->getVel().rotate(90);
			right = true;
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT) && !left) { // rotate left
			
			pmTR_->rot_ -= 90;
			// also rotate the PacMan so it looks in the same
			// direction where it moves

			pmTR_->getVel() = pmTR_->getVel().rotate(-90);
			left = true;
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed

			// empieza a moverse con la rotacion que tenga en el momento
			pmTR_->getVel().set(0, - speed);
			pmTR_->getVel() = pmTR_->getVel().rotate(pmTR_->rot_);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { 

			// si pulsas downarrow se deja de mover
			pmTR_->getVel().set(0, 0);
		}


		if (ih().isKeyUp(SDL_SCANCODE_RIGHT)) {
			right = false;
		}
		if (ih().isKeyUp(SDL_SCANCODE_LEFT)) {
			left = false;
		}

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

	auto imgF_Cmp = mngr_->getComponent<ImageWithFrames>(pacMan);



	if ((imgF_Cmp->lastFrame + imgF_Cmp->frameTime) < sdlutils().virtualTimer().currTime()) {

		imgF_Cmp->lastFrame = sdlutils().virtualTimer().currTime();
		imgF_Cmp->currentFrame++;
		if (imgF_Cmp->currentFrame > imgF_Cmp->lastIndex) {
			imgF_Cmp->currentFrame = imgF_Cmp->firstIndex;
		}
	}
}

void PacManSystem::recieve(const Message& msg)
{
	if (msg.id == _m_ROUND_START) {
		//nueva ronda, resetear posicion

	}
	else if (msg.id == _m_NEW_GAME) {
		//nueva partida resetear vidas

	}
}

void PacManSystem::resetPos()
{
	auto pmTR_ = mngr_->getComponent<Transform>(pacMan);

	pmTR_->getPos().set((sdlutils().width() - pacmanWidth) / 2,
		(sdlutils().height() - pacmanHeight) / 2);

	//resetea la velocidad y la rotacion
	pmTR_->vel_.set(0, 0);
	pmTR_->rot_ = 0;
}

void PacManSystem::resetLifes()
{
	//esto pa cuando tengamos el health component
}
