#pragma once
#include "../components/Transform.h"
#include "../ecs/Component.h"

class Transform;
class Rotation : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::ROTATION);

	Rotation();
	Rotation(float rotSpeed);
	~Rotation();

	void initComponent() override;
	void update() override;

private:
	Transform* myTransform_;
	float rotSpeed_;
};

