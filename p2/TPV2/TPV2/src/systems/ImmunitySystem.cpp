#include "ImmunitySystem.h"

#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

ImmunitySystem::ImmunitySystem() :
	invulnerability_(false),
	invulnerabilityTime_(10000),
	currentTime()
{
}

ImmunitySystem::~ImmunitySystem()
{
}

void ImmunitySystem::initSystem()
{
}

void ImmunitySystem::update()
{
	if (invulnerability_ && sdlutils().currRealTime() >= currentTime + invulnerabilityTime_)
	{
		invulnerability_ = false;
		Message msg;
		msg.id = _m_IMMUNITY_END;
		mngr_->send(msg);
	}
}

void ImmunitySystem::recieve(const Message& msg)
{
	switch (msg.id)
	{
	case _m_IMMUNITY_START:
		invulnerability_ = true;
		currentTime = sdlutils().currRealTime();
		break;
	default:
		break;
	}
}