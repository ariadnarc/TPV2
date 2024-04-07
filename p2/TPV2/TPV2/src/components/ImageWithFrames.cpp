#include "ImageWithFrames.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "Transform.h"

ImageWithFrames::ImageWithFrames(std::string id, int fils, int cols)
	:fils(fils), cols(cols)
{
	myTexture = &sdlutils().images().at(id);

	frameWidth = myTexture->width() / cols;
	frameHeight = myTexture->height() / fils;
}

ImageWithFrames::~ImageWithFrames() {
}

void ImageWithFrames::initComponent() {
	myTransform = mngr_->getComponent<Transform>(ent_);
}

void ImageWithFrames::update() {
	if ((lastFrame + frameTime) < sdlutils().virtualTimer().currTime()) {
		lastFrame = sdlutils().virtualTimer().currTime();
		currentFrame = (currentFrame + 1) % (fils * cols);
	}
}

void ImageWithFrames::render() {
	myTexture->render(build_sdlrect((currentFrame % cols) * frameWidth, (currentFrame / cols) * frameHeight, frameWidth, frameHeight),
		build_sdlrect(myTransform->getPos(), myTransform->getWidth(), myTransform->getHeight()), myTransform->getRot());

}
