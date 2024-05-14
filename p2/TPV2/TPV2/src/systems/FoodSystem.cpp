// This file is part of the course TPV2@UCM - Samir Genaim

#include "FoodSystem.h"
#include "ImmunitySystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/MiracleFruit.h"
#include "../components/ImageWithFrames.h"
#include "../ecs/Entity.h"

void FoodSystem::initSystem()
{
	std::cout << "inicia el sistem FoodSystem" << std::endl;
	createGrid();
}

void FoodSystem::update()
{
	std::vector<ecs::entity_t> fruits = mngr_->getEntities(ecs::grp::FRUITS);
	if (fruits.size() <= 0) {
		Message msg;
		msg.id = _m_GAME_OVER;
		mngr_->send(msg);

		// Sonido victoria
		//sdlutils().soundEffects().at("won").play();
	}

	for (auto& e : mngr_->getEntities(ecs::grp::FRUITS)) {
		auto mf = mngr_->getComponent<MiracleFruit>(e);
		if (mf != nullptr) {
			mf->update();
		}
	}
}

void FoodSystem::recieve(const Message& msg)
{
	switch (msg.id)
	{
	case _m_PACMAN_FOOD_COLLISION:
		std::cout << "FoodSystem recibe _m_PACMAN_FOOD_COLLISION" << std::endl;

		mngr_->setAlive(msg.fruit_collision_data.fruitToDelete, false); // destruye fruta

		if (msg.fruit_collision_data.isMilagrosa &&						// si fruta colisionada es milagrosa
			!mngr_->getSystem<ImmunitySystem>()->getImmunity())			// y el pacman es vulnerable (no inmune)
		{
			Message msg1;
			msg1.id = _m_IMMUNITY_START;								// mandamos a GHOST que el pacman es inmune
			mngr_->send(msg1);
		}
		break;
		 
	}
}

void FoodSystem::addFood(Vector2D pos)
{
	// CREA ENTIDAD FRUTA
	auto fruit = mngr_->addEntity(ecs::grp::FRUITS);
	mngr_->addComponent<Transform>(fruit, pos, Vector2D(0,0), 50, 50, 0); //pos_(), vel_(), width_(), height_(), rot_()
	mngr_->addComponent<ImageWithFrames>(fruit, &sdlutils().images().at("spriteSheet"), 8, 8, 0, 0, 1024 / 8, 1024 / 8, 1, 4, 1, 1);
	
	// MILAGROSA - probabilidad del 0.1
	if (sdlutils().rand().nextInt(0, 10) == 0)
	{
		mngr_->addComponent<MiracleFruit>(fruit);
	}
}

void FoodSystem::createGrid()
{
	for (int i = 0; i < FRUITCOLS; i++) 
	{
		for (int j = 0; j < FRUITROWS; j++) 
		{
			addFood(Vector2D(sdlutils().width() / FRUITCOLS * i + offset,
							sdlutils().height() / FRUITROWS * j + offset));
		}
	}
}


