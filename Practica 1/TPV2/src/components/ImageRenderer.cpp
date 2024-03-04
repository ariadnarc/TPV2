// This file is part of the course TPV2@UCM - Samir Genaim

#include "ImageRenderer.h"

#include "../ecs/Manager.h"
#include "../sdlutils/Texture.h"

ImageRenderer::ImageRenderer(Texture* img) :
	img_(img),
	transform_()
{
}

ImageRenderer::~ImageRenderer()
{
}

void ImageRenderer::initComponent()
{
	transform_ = mngr_->getComponent<Transform>(ent_);
	assert(transform_ != nullptr);
}

void ImageRenderer::render()
{
	SDL_Rect dest = build_sdlrect(transform_->getPos(), transform_->getWidth(), transform_->getHeight());
	img_->render(dest, transform_->getRot());
}