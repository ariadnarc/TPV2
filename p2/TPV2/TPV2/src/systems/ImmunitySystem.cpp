#include "ImmunitySystem.h"

#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

ImmunitySystem::ImmunitySystem() :
	immunity_(false),
	invulnerabilityTime_(10000),
	currentTime()
{
}

void ImmunitySystem::initSystem()
{
	std::cout << "inicia el sistem ImmunitySystem" << std::endl;
}

void ImmunitySystem::update()
{
	if (immunity_ &&															// si el pacman es inmune
		sdlutils().currRealTime() >= currentTime + invulnerabilityTime_)		// y pasan 10 seg
	{
		immunity_ = false;														// pacman se vuelve vulnerable

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
		std::cout << "ImmunitySystem recibe _m_IMMUNITY_START" << std::endl;
		immunity_ = true;
		currentTime = sdlutils().currRealTime();
		break;

	default:
		break;
	}
}