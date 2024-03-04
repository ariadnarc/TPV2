// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "Transform.h"
#include "../ecs/Component.h"

class Texture;

class ImageRenderer : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::IMAGE)

		ImageRenderer(Texture* img);
	~ImageRenderer() override;
	void initComponent() override;
	void render() override;

private:
	Texture* img_;
	Transform* transform_;
};