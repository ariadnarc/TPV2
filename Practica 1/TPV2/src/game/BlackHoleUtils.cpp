#include "BlackHoleUtils.h"

#include "Game.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/ImageRenderer.h"
#include "../components/Rotation.h"


BlackHoleUtils::BlackHoleUtils()
	: mngr_(g().getMngr()), random_(sdlutils().rand())
{
}

BlackHoleUtils::~BlackHoleUtils()
{
}

void BlackHoleUtils::create_blackholes(int n)
{
	const double alpha = (360.0 / n) * M_PI / 180.0f;
	const int centerx = sdlutils().width() / 2;
	const int centery = sdlutils().height() / 2;

	for (int i = 0; i < n; i++)
	{
		const int radio = random_.nextInt(100, 301);
		const int rotation = random_.nextInt(5, 11);

		int x = centerx + radio * cos(alpha * i);
		int y = centery + radio * sin(alpha * i);
		x -= 50 / 2;
		y -= 50 / 2;
		const auto hole = mngr_->addEntity(ecs::grp::BLACKHOLES);
		mngr_->addComponent<Transform>(hole,
			Vector2D(x, y), // pos
			Vector2D(0, 0), // vel
			50, // w
			50, // h
			0.0f //r
		);
		mngr_->addComponent<ImageRenderer>(hole, &sdlutils().images().at("black_hole"));
		mngr_->addComponent<Rotation>(hole, rotation);
	}
}

void BlackHoleUtils::remove_all_blackholes()
{
	const auto blackholes = mngr_->getEntities(ecs::grp::BLACKHOLES);
	for (auto h : blackholes)
		mngr_->setAlive(h, false);
	mngr_->refresh();
}
