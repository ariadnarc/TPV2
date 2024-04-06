#include "PacManSystem.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"
#include "../components/Health.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"


PacManSystem::PacManSystem()
{

}

PacManSystem::~PacManSystem()
{
}

void PacManSystem::initSystem()
{
	//creacion del pacMan
	pacMan = mngr_->addEntity();

	//componentes
	auto tr = mngr_->addComponent<Transform>(pacMan);
	tr->setHeight(pacmanHeight);
	tr->setWidth(pacmanWidth);

	resetPos();
	resetLifes();
}

void PacManSystem::update()
{
	//mover el pacman
	pacManMovement();
}

void PacManSystem::recieve(const Message& msg)
{

}

void PacManSystem::pacManMovement()
{
	auto tf = mngr_->getComponent<Transform>(pacMan);

	// ????
}

void PacManSystem::resetPos()
{
	auto tf = mngr_->getComponent<Transform>(pacMan);

	// ???
}

void PacManSystem::resetLifes()
{

}