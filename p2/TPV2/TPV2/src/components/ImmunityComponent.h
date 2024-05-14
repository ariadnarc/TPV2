#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

//No hay cpp
class ImmunityComponent : public ecs::Component
{
	__CMPID_DECL__(ecs::cmp::IMMUNITY);

	ImmunityComponent(bool inmune = false) : 
		inmune_(inmune) {};

	virtual ~ImmunityComponent() {};

	void setInmune(bool inmune) { inmune_ = inmune; };
	bool getImmunity() { return inmune_; }

	bool inmune_;
};