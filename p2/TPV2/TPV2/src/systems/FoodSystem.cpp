// This file is part of the course TPV2@UCM - Samir Genaim

#include "FoodSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/ImageWithFrames.h"


FoodSystem::FoodSystem()
{
}

FoodSystem::~FoodSystem()
{
}

void FoodSystem::initSystem()
{
	std::cout << "inicia el sistem food" << std::endl;
	createGrid();

}

void FoodSystem::update()
{
}

void FoodSystem::recieve(const Message&)
{
}

void FoodSystem::addFood(Vector2D pos)
{
	//crea 1 entidad de fruta
	auto fruit = mngr_->addEntity(ecs::grp::FRUITS);
	mngr_->addComponent<Transform>(fruit, pos, Vector2D(0,0), 50, 50, 0); //pos_(), vel_(), width_(), height_(), rot_()
	mngr_->addComponent<ImageWithFrames>(fruit, &sdlutils().images().at("spriteSheet"), 8, 8, 0, 0, 1024 / 8, 1024 / 8, 1, 4, 1, 1);
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


