#pragma once

#include "../ecs/Component.h"

class Transform;

class Vector2D;

class LookAt : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::LOOKAT)

	LookAt(Vector2D& to_lookAt);
	virtual ~LookAt();
	void initComponent() override;
	void update() override;

private:
	Vector2D& to_lookAt_;
	Transform* tr_;
};