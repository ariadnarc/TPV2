
// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

struct Image;
struct HealthComponent;
struct ImageWithFrames;
class Texture;
struct Transform;

class RenderSystem : public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::RENDER)

		RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;
private:

	void drawPacMan();
	void drawFruits();
	//ari el draw es inutil lo he quitao
};
