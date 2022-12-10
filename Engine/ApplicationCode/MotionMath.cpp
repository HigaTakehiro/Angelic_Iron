#include "MotionMath.h"

MotionMath* MotionMath::GetIns()
{
	static MotionMath instance;
	return &instance;
}

Vector3 MotionMath::CircularMotion(const Vector3& centerPos, const Vector3& rotPos, float angle, float length, Axis axis) {
	float radius = angle * 3.14f / 180.0f;
	Vector3 pos = rotPos;

	if (axis == X) {
		pos.y = centerPos.y + length * cos(radius);
		pos.z = centerPos.z + length * sin(radius);
		return pos;
	}
	else if (axis == Y) {
		pos.x = centerPos.x + length * cos(radius);
		pos.z = centerPos.z + length * sin(radius);
		return pos;
	}
	else if (axis == Z) {
		pos.x = centerPos.x + length * sin(radius);
		pos.y = centerPos.y + length * cos(radius);
		return pos;
	}
}