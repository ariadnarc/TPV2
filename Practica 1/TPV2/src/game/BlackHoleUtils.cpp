#include "BlackHoleUtils.h"

#include "Game.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"

BlackHoleUtils::BlackHoleUtils()
	: mngr_(g().getMngr()), random_(sdlutils().rand())
{
}

BlackHoleUtils::~BlackHoleUtils()
{
}

void BlackHoleUtils::create_blackholes(int n)
{
	for (int i = 0; i < n; i++) {

		auto blackhole = mngr_->addEntity();
		//mngr_->addComponent<Transform>(blackhole, Vector2D(1, 1)); //no se q parametros ponerle a esto
		std::cout << "aaaa" << std::endl;
	}
}

void BlackHoleUtils::remove_all_blackholes()
{
}
