// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_scancode.h>
#include "Container.h"
#include "InputComponent.h"
#include "../sdlutils/InputHandler.h"
#include <SDL.h>

class FighterCtrl : public InputComponent {
public:
	FighterCtrl();
	virtual ~FighterCtrl() override = default;
	void handleInput(Container* o) override;

private:
	SDL_Scancode up_;
	SDL_Scancode left_;
	SDL_Scancode right_;

	float rotation_ = 5.0f;
	float thrust_ = 0.2f; //empuje
	float speedLimit_ = 3.0f;
};


