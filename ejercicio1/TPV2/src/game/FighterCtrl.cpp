#include "FighterCtrl.h"
#include "../sdlutils/InputHandler.h"
#include "Container.h"
//literalmente copia pega del movePaddleWithKeyBoard.cpp pero con modificaciones
FighterCtrl::FighterCtrl() : 
	rotLeft_(SDL_SCANCODE_LEFT),
	rotRight_(SDL_SCANCODE_RIGHT),
	rotSpeed_(10.0f)
{
}

FighterCtrl::~FighterCtrl()
{
}

void FighterCtrl::handleInput(Container* o)
{
	auto &ihdlr = ih();

	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(rotLeft_)) {
			o->setRotation(o->getRotation() - rotSpeed_);
		}
		else if (ihdlr.isKeyDown(rotRight_)) {
			o->setRotation(o->getRotation() + rotSpeed_);
		}
	}
}
