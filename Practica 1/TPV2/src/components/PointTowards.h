#pragma once

#include "../ecs/Component.h"
class Transform;

class Vector2D;

class PointTowards : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::POINTTOWARDS)

	PointTowards(Vector2D& to_point);
	virtual ~PointTowards();
	void initComponent() override;
	void update() override;

private:
	Vector2D& to_point_;
	Transform* tr_;
};