#include "SphereAndSphere.h"
#include "Vector3.h"

bool SphereAndSphere::HitTest(Object3d* obj1, Object3d* obj2)
{
	Vector3 objPos1 = obj1->GetPosition();
	Vector3 objPos2 = obj2->GetPosition();
	float objRadius1 = obj1->GetScale().x;
	float objRadius2 = obj2->GetScale().x;

	return ((objPos2.x - objPos1.x) * (objPos2.x - objPos1.x)) + ((objPos2.y - objPos1.y) * (objPos2.y - objPos1.y)) + ((objPos2.z - objPos1.z) * (objPos2.z - objPos1.z)) <= ((objRadius1 + objRadius2) * (objRadius1 + objRadius2));
}
