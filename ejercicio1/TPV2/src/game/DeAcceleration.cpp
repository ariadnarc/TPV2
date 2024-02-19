#include "DeAcceleration.h"

void DeAcceleration::update(Container* o)
{
	auto& vel = o->getVel();
	vel = vel * deAcceleration_; //ira multiplicando la velocidad para q vaya frenanding
}
