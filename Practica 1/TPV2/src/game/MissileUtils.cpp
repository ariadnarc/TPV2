#include "MissileUtils.h"
#include "../ecs/Manager.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/ImageRenderer.h"
#include "../components/Follow.h"
#include "../components/TowardsDestination.h"
#include "../components/PointTowards.h"


MissileUtils::MissileUtils()
	: mngr_(g().getMngr()),	random_(sdlutils().rand())
{
}

MissileUtils::~MissileUtils()
{
}

void MissileUtils::create_missiles(int n)
{
	for (int i = 0; i < n; i++)
	{
		const int corner = random_.nextInt(0, 4);
		int x = 0, y = 0; //para la esquina

		int velX = random_.nextInt(1, 4); // del 1 al 3 para la velocidad

		switch (corner) {
		case 0: break;
		case 1:
			//arriba derecha
			x = sdlutils().width() - 100;
			y = 0;
			break;
		case 2:
			//abajo izquierda
			x = 0;
			y = sdlutils().height() - 100;
			break;
		default:
			//abajo derecha
			x = sdlutils().width() - 100;
			y = sdlutils().height() - 100;
			break;
		}

		auto missile = mngr_->addEntity(ecs::grp::MISSILES);
		mngr_->addComponent<Transform>(missile,
			Vector2D(x, y), // pos
			Vector2D(1, 0), // vel
			50, // w
			50, // h
			0.0f //r
		);

		mngr_->addComponent<ImageRenderer>(missile, &sdlutils().images().at("missile"));
		
		auto fighter = mngr_->getHandler(ecs::hdlr::FIGHTER);
		auto fighterTR = mngr_->getComponent<Transform>(fighter);
		mngr_->addComponent<Follow>(missile, fighterTR->getPos());
		mngr_->addComponent<PointTowards>(missile, fighterTR->getPos());
	}
}

void MissileUtils::remove_missiles()
{
	const auto missiles = mngr_->getEntities(ecs::grp::MISSILES);
	for (auto h : missiles)
		mngr_->setAlive(h, false);
	mngr_->refresh();
}


