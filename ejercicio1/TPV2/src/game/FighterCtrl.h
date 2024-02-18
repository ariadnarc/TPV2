// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "InputComponent.h"

#include <SDL.h>

class FighterCtrl : public InputComponent {
public:
	FighterCtrl();
	virtual ~FighterCtrl();

	inline void setKeys(SDL_Scancode rotRight, SDL_Scancode rotLeft) {
		rotLeft_ = rotLeft;
		rotRight_ = rotRight;
	}

	inline void setSpeed(float speed) {
		rotSpeed_ = speed;
	}

	void handleInput(Container* o) override;

private:
	SDL_Scancode rotRight_;
	SDL_Scancode rotLeft_;

	float rotSpeed_;
};


