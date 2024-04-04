// This file is part of the course TPV2@UCM - Samir Genaim

#include "PaddleMouseCtrl.h"

#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"

PaddleMouseCtrl::PaddleMouseCtrl() :
		tr_(nullptr) {
}

PaddleMouseCtrl::~PaddleMouseCtrl() {
}

void PaddleMouseCtrl::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void PaddleMouseCtrl::update() {
	auto &ihdlr = ih();

	auto &pos = tr_->getPos();

	if (ihdlr.mouseMotionEvent()) {
		pos.setY(ihdlr.getMousePos().second);
	}
}
