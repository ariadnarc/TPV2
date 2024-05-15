
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
	// Llama a los draws en cada update.
	void update() override;
private:
	// Llama al render de ImageWithFrames de la entidad.
	void drawPacMan();
	// Llama al render de ImageWithFrames de la entidad.
	void drawFruits();
	// Llama al render de ImageWithFrames de la entidad.
	void drawGhosts();
	// Llama al render de ImageWithFrames de la entidad.
	void drawHealth();

};
