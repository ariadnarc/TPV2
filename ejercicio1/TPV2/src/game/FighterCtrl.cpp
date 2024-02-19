#include "FighterCtrl.h";

//literalmente copia pega del movePaddleWithKeyBoard.cpp pero con modificaciones

FighterCtrl::FighterCtrl() :
	left_(SDL_SCANCODE_LEFT),
	right_(SDL_SCANCODE_RIGHT),
	up_(SDL_SCANCODE_UP)
{
}

void FighterCtrl::handleInput(Container* o)
{
	auto &ihdlr = ih();

	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(left_)) {
			o->setRotation(o->getRotation() - rotation_);
		}
		else if (ihdlr.isKeyDown(right_)) {
			o->setRotation(o->getRotation() + rotation_);
		}
		else if (ihdlr.isKeyDown(up_))
		{
			auto& vel = o->getVel();
			vel = vel + Vector2D(0, -1).rotate(o->getRotation()) * thrust_; //formula del enunciado
			if (vel.getX() > speedLimit_ || vel.getY() > speedLimit_)
				vel = vel.normalize() * speedLimit_;
		}
	}
}
