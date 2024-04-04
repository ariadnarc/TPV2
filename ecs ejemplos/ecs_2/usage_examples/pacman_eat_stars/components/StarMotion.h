// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "../ecs/Component.h"

class Transform;
class StarMotion: public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_STARMOTION
	//
	__CMPID_DECL__(ecs::cmp::STARMOTION)

	StarMotion();
	virtual ~StarMotion();
	void initComponent() override;
	void update() override;

private:
	Transform *tr_;
	Uint32 lastUpdate_;
};

