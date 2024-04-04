// This file is part of the course TPV2@UCM - Samir Genaim

#include "PaddleAICtrl.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

PaddleAICtrl::PaddleAICtrl() :
		tr_(nullptr), ballTr_(nullptr) {
}

PaddleAICtrl::~PaddleAICtrl() {
}

void PaddleAICtrl::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);

	auto mngr = ent_->getMngr();
	ballTr_ = mngr->getHandler(ecs::hdlr::BALL)->getComponent<Transform>();
	assert(ballTr_ != nullptr);

}

void PaddleAICtrl::update() {

	auto &vel = tr_->getVel();
	auto &pos = tr_->getPos();
	auto height = tr_->getHeight();

	if (ballComingTowardsPaddle(pos)) {
		float diff = (ballTr_->getPos().getY() + ballTr_->getHeight() / 2.0f)
				- (pos.getY() + height / 2.0f);
		if (abs(diff) < 10) {
			vel.setY(0.0f);
		} else {
			vel.setY(
					(diff > 0.0f ? 1.0f : -1.0f) * 1.0f
							* ballTr_->getVel().magnitude());
		}
	} else {
		float diff = (sdlutils().height() / 2.0f)
				- (pos.getY() + height / 2.0f);
		if (abs(diff) < 10) {
			vel.setY(0.0);
		} else {
			vel.setY((diff > 0 ? 1 : -1) * 5.0f);
		}
	}
}

bool PaddleAICtrl::ballComingTowardsPaddle(const Vector2D &pos) {

	return (pos.getX() < ballTr_->getPos().getX()
			&& ballTr_->getVel().getX() < 0)
			|| (pos.getX() > ballTr_->getPos().getX()
					&& ballTr_->getVel().getX() > 0);
}
