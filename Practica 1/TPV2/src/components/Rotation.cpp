#include "Rotation.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

Rotation::Rotation() : myTransform_(nullptr)
{
}

Rotation::Rotation(float rotSpeed) : rotSpeed_(rotSpeed)
{
}



Rotation::~Rotation()
{
}

void Rotation::initComponent()
{
	myTransform_ = mngr_->getComponent<Transform>(ent_);
	assert(myTransform_ != nullptr);
}

void Rotation::update()
{
	myTransform_->setRot(myTransform_->getRot() + rotSpeed_);
}
