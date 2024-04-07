#include "CollisionSystem.h"

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
	fruitCollision();
	ghostCollision();
}

void CollisionSystem::recieve(const Message&)
{
}

void CollisionSystem::fruitCollision()
{
}

void CollisionSystem::ghostCollision()
{
}
