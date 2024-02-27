#include "BlackHoleUtils.h"

#include "Game.h"
#include "../sdlutils/SDLUtils.h"

BlackHoleUtils::BlackHoleUtils()
	: mngr_(g().getMngr()), random_(sdlutils().rand())
{
}

BlackHoleUtils::~BlackHoleUtils()
{
}

void BlackHoleUtils::create_blackholes(int n)
{
}

void BlackHoleUtils::remove_all_blackholes()
{
}
