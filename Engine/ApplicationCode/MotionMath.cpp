#include "MotionMath.h"

MotionMath* MotionMath::GetIns()
{
	static MotionMath instance;
	return &instance;
}

Vector3 MotionMath::CircularMotion(const Vector3& centerPos, const Vector3& rotPos, float angle, float length, Axis axis) {
	float radius = angle * 3.14f / 180.0f;
	float addX, addY, addZ;
	Vector3 pos = rotPos;

	if (axis == X) {
		addZ = cos(radius) * length;
		addY = sin(radius) * length;
		pos.z += addZ;
		pos.y += addY;
		return pos;
	}
	else if (axis == Y) {
		addX = cos(radius) * length;
		addZ = sin(radius) * length;
		pos.x += addX;
		pos.z += addZ;
		return pos;
	}
	else if (axis == Z) {
		addX = cos(radius) * length;
		addY = sin(radius) * length;
		pos.x += addX;
		pos.y += addY;
		return pos;
	}
}