#include "ImmunitySystem.h"

#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

ImmunitySystem::ImmunitySystem() :
	blue_(false),
	blueTime_(10000),
	currentTime()
{
}

void ImmunitySystem::initSystem()
{
	std::cout << "inicia el sistem ImmunitySystem" << std::endl;
}

void ImmunitySystem::update()
{
	if (blue_ &&															// si el pacman es inmune
		sdlutils().currRealTime() >= currentTime + blueTime_)				// y pasan 10 seg
	{
		blue_ = false;														// fantasmas vuelven a ser rojos

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
		blue_ = true; // azules
		currentTime = sdlutils().currRealTime(); // guardamos tiempo desde que se vuelven azules
		break;

	default:
		break;
	}
}