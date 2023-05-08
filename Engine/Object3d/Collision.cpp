#include "Collision.h"

Collision* Collision::GetIns()
{
	static Collision instance;
	return &instance;
}

bool Collision::OBJSphereCollision(Object3d* object1, Object3d* object2, float objScale1, float objScale2) {
	object1Pos_ = object1->GetMatWorld().r[3];

	object2Pos_ = object2->GetMatWorld().r[3];

	objectPosTotal_ = (object2Pos_.x - object1Pos_.x) * (object2Pos_.x - object1Pos_.x) + (object2Pos_.y - object1Pos_.y) * (object2Pos_.y - object1Pos_.y) + (object2Pos_.z - object1Pos_.z) * (object2Pos_.z - object1Pos_.z);
	objectScaleTotal_ = (objScale1 + objScale2) * (objScale1 + objScale2);

	if (!(objectPosTotal_ <= objectScaleTotal_)) return false;

	return true;
}