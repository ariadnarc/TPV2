
// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"
#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../components/Health.h"

constexpr Uint32 FRAME_DURATION = 100;

void RenderSystem::initSystem() {
	std::cout << "inicia el sistem RenderSystem" << std::endl;
}

void RenderSystem::update() 
{
	drawFruits();
	drawPacMan();
	drawGhosts();
	drawHealth();
}

void RenderSystem::drawPacMan() 
{
	auto e = mngr_->getHandler(ecs::hdlr::PACMAN);
	mngr_->getComponent<ImageWithFrames>(e)->render();
}

void RenderSystem::drawFruits() 
{
	auto fruitGroup = mngr_->getEntities(ecs::grp::FRUITS);
	//por cada elemento en fruitGroup se hace el render
	for (auto & elem : fruitGroup) {
		mngr_->getComponent<ImageWithFrames>(elem)->render();
	}
}

void RenderSystem::drawGhosts()
{
	auto ghostGroup = mngr_->getEntities(ecs::grp::GHOSTS);
	//por cada elemento en ghostGroup se hace el render
	for (auto& elem : ghostGroup) {
		mngr_->getComponent<ImageWithFrames>(elem)->render();
	}
}

void RenderSystem::drawHealth()
{
	auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto health = mngr_->getComponent<HealthComponent>(pacman);
	health->render();
}

