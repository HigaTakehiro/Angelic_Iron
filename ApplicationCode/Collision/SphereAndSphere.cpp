#include "SphereAndSphere.h"
#include <math.h>

bool SphereAndSphere::CollisionCheck(const SphereShape& shape1, const SphereShape& shape2)
{
	Vector3 shapePos1 = shape1.GetPos();
	Vector3 shapePos2 = shape2.GetPos();

	return (shapePos2.x - shapePos1.x) * (shapePos2.x - shapePos1.x) + (shapePos2.y - shapePos1.y) * (shapePos2.y - shapePos1.y) + (shapePos2.z - shapePos1.z) * (shapePos2.z - shapePos1.z) <= (shape2.GetRadius() - shape1.GetRadius()) * (shape2.GetRadius() - shape1.GetRadius());
}