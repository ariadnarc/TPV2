#include "CollisionSystem.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../ecs/Manager.h"
#include "../components/MiracleFruit.h"

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
			Message msg;
			msg.id = _m_PACMAN_FOOD_COLLISION;
			msg.fruit_collision_data.isMilagrosa = mngr_->hasComponent<MiracleFruit>(fruitGr[i]);
			msg.fruit_collision_data.fruitToDelete = fruitGr[i];
			//tododododo
			mngr_->send(msg);
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
			Message msg;
			msg.id = _m_PACMAN_GHOST_COLLISION;
			msg.ghost_collision_data.ghostToDelete = ghostGr[i];
	
			mngr_->send(msg);

			auto a = mngr_->hasComponent<MiracleFruit>(ghostGr[i]);
			if (a) 
			{
				Message msg;
				msg.id = _m_IMMUNITY_START;
		
				mngr_->send(msg);
			}
		}
	}
}
