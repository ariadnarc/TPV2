// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL.h>

#include "../ecs/Component.h"

class ImageWithFrames;

struct MiracleFruit : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::MIRACLEFRUIT)

	MiracleFruit();
	virtual ~MiracleFruit();
	void initComponent() override;
	void update() override;

	float miracleFreq;
	float miracleTime;
	float lastUpdate;
	
	bool milagros;
	ImageWithFrames* img;

};