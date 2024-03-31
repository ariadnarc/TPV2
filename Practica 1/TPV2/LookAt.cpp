#include "LookAt.h"

#include <cmath>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

LookAt::LookAt(Vector2D& to_lookAt) :
	to_lookAt_(to_lookAt), //
	tr_(nullptr) {

}

LookAt::~LookAt() {
}

void LookAt::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}