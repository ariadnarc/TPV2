// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_scancode.h>
#include "Container.h"
#include "InputComponent.h"
#include <SDL.h>

class FighterCtrl : public InputComponent {
public:
	FighterCtrl();
	virtual ~FighterCtrl() override = default;
	void handleInput(Container* o) override;

private:
	SDL_Scancode rotRight_;
	SDL_Scancode rotLeft_;

	float rotSpeed_;
};


