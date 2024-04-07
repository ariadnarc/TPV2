#include "CollisionSystem.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../ecs/Manager.h"

CollisionSystem::CollisionSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::initSystem()
{
}

void CollisionSystem::update()
{
	auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);

	fruitCollision(pacman);
	ghostCollision(pacman);
}

void CollisionSystem::recieve(const Message&)
{
}

void CollisionSystem::fruitCollision(ecs::entity_t pm)
{
	auto pmTr = mngr_->getComponent<Transform>(pm);
	auto fruitGr = mngr_->getEntities(ecs::grp::FRUITS);

	for (int i = 0; i < fruitGr.size(); i++)
	{
		auto frTR = mngr_->getComponent<Transform>(fruitGr[i]);

		//si colisiona pmTR con frTR
		if (Collisions::collides(pmTr->pos_, pmTr->getWidth(), pmTr->getHeight(),
			frTR->pos_, frTR->getWidth(), frTR->getHeight())) 
		{
			std::cout << "colisionFRUTA" << std::endl;
		}
	}
}

void CollisionSystem::ghostCollision(ecs::entity_t pm)
{
	auto pmTr = mngr_->getComponent<Transform>(pm);
	auto ghostGr = mngr_->getEntities(ecs::grp::GHOSTS);

	for (int i = 0; i < ghostGr.size(); i++)
	{
		auto frTR = mngr_->getComponent<Transform>(ghostGr[i]);

		//si colisiona pmTR con frTR
		if (Collisions::collides(pmTr->pos_, pmTr->getWidth(), pmTr->getHeight(),
			frTR->pos_, frTR->getWidth(), frTR->getHeight()))
		{
			std::cout << "collisionGHOST" << std::endl;
		}
	}
}
