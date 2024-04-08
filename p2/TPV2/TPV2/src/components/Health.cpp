#include "Health.h"

#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"

HealthComponent::HealthComponent(Texture* tex) :
	tex_(tex),
	scale_(0.5),
	offset_(tex_->width()* scale_),
	iniX_(3),
	iniY_(10),
	lifes_(3)
{
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::render()
{
	Vector2D pos;
	for (int i = 0; i < lifes_; i++) {
		pos.set(iniX_ + (offset_ * i), iniY_);
		tex_->render(build_sdlrect(pos, tex_->width() * scale_, tex_->height() * scale_));
	}
}