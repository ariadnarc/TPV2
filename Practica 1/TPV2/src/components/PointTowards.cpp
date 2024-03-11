#include "PointTowards.h"

#include <cmath>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

PointTowards::PointTowards(Vector2D& to_point) :
	to_point_(to_point), //
	tr_(nullptr) {
}

PointTowards::~PointTowards() {
}

void PointTowards::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void PointTowards::update() {
	
	auto pos = tr_->getPos();

	auto vel = to_point_ - pos; // creates velocity vector with direction to fighter

	tr_->setRot(Vector2D(0, -1).angle(vel)); // assigns rotation with the angle of the velocity vector created
}