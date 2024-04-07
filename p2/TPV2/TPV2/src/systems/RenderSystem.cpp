
// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"
#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

constexpr Uint32 FRAME_DURATION = 100;

RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	//drawFruits();
	drawPacMan();
	std::cout << "a" << std::endl;
}


void RenderSystem::drawPacMan() {
	auto e = mngr_->getHandler(ecs::hdlr::PACMAN);
	mngr_->getComponent<ImageWithFrames>(e)->render();
}

