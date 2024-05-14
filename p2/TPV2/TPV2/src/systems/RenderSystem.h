
// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class Image;
class HealthComponent;
class ImageWithFrames;
class Texture;
class Transform;

class RenderSystem : public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::RENDER)

		RenderSystem() {};
	virtual ~RenderSystem() {};

	void initSystem() override;
	void update() override;
private:

	void drawPacMan();
	void drawFruits();
	void drawGhosts();
	void drawHealth();
	//ari el draw es inutil lo he quitao
};
