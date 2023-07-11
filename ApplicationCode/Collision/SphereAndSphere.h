#pragma once
#include "BaseCollision.h"
#include "SphereShape.h"

class SphereAndSphere : public BaseCollision
{
	bool CollisionCheck(const SphereShape& shape1, const SphereShape& shape2);
};

