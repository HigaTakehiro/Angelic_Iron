#include "Collision.h"

Collision* Collision::GetIns()
{
	static Collision instance;
	return &instance;
}

bool Collision::OBJSphereCollision(Object3d* object1, Object3d* object2, float objScale1, float objScale2) {
	object1Pos = object1->GetMatWorld().r[3];

	object2Pos = object2->GetMatWorld().r[3];

	objectPosTotal = (object2Pos.x - object1Pos.x) * (object2Pos.x - object1Pos.x) + (object2Pos.y - object1Pos.y) * (object2Pos.y - object1Pos.y) + (object2Pos.z - object1Pos.z) * (object2Pos.z - object1Pos.z);
	objectScaleTotal = (objScale1 + objScale2) * (objScale1 + objScale2);

	if (!(objectPosTotal <= objectScaleTotal)) return false;

	return true;
}