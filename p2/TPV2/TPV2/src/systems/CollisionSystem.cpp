#include "CollisionSystem.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../ecs/Manager.h"
#include "../components/MiracleFruit.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/ImmunitySystem.h"

void CollisionSystem::initSystem()
{
	std::cout << "inicia el sistem CollisionSystem" << std::endl;
}

void CollisionSystem::update()
{
	auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);

	fruitCollision(pacman);
	ghostCollision(pacman);
}

void CollisionSystem::recieve(const Message&)
{
	// collision no recibe nada, solo envia mensajes en fruitCollision(...), ghostCollision(...)
}

void CollisionSystem::fruitCollision(ecs::entity_t pm)
{
	auto pmTr = mngr_->getComponent<Transform>(pm);
	auto fruitGr = mngr_->getEntities(ecs::grp::FRUITS);

	for (int i = 0; i < fruitGr.size(); i++)
	{
		auto frTR = mngr_->getComponent<Transform>(fruitGr[i]);

		//si colisionan los transforms de PACMAN con FRUIT
		if (Collisions::collides(pmTr->pos_, pmTr->getWidth(), pmTr->getHeight(), //object1
			frTR->pos_, frTR->getWidth(), frTR->getHeight()))					  //object2
		{
			//sdlutils().soundEffects().at("eat").play();
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
		auto ghTR = mngr_->getComponent<Transform>(ghostGr[i]);

		//si colisiona PACMAN con GHOST
		if (Collisions::collides(pmTr->pos_, pmTr->getWidth(), pmTr->getHeight(), //obj1
			ghTR->pos_, ghTR->getWidth(), ghTR->getHeight()))					  //obj2
		{
			Message msg;
			msg.id = _m_PACMAN_GHOST_COLLISION;
			//msg.ghost_collision_data.blue = mngr_->getSystem<ImmunitySystem>()->getImmunity();
			msg.ghost_collision_data.ghostToDelete = ghostGr[i];
			mngr_->send(msg);
		}
	}
}
