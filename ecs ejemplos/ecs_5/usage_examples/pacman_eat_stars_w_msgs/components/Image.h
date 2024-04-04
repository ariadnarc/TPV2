// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class Texture;

struct Image: public ecs::Component {


	Image() :
			tex_() {
	}

	Image(Texture *tex) :
			tex_(tex) {
	}

	virtual ~Image() {
	}

	Texture *tex_;
};

