#include "MotionMath.h"

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

	return pos;
}

Vector3 MotionMath::Spline(const std::vector<Vector3>& points, int32_t startIndex, float t) {
	int32_t n = (int32_t)points.size() - 2;

	if (startIndex > n) return points[n];
	if (startIndex < 1) return points[1];

	Vector3 p0 = points[startIndex - 1];
	Vector3 p1 = points[startIndex];
	Vector3 p2 = points[startIndex + 1];
	Vector3 p3 = points[startIndex + 2];

	Vector3 time1 = (p1 * 2.0f) + (-p0 + p2) * t;
	Vector3 time2 = ((p0 * 2.0f) - (p1 * 5.0f) + (p2 * 4.0f) - p3) * (t * t);
	Vector3 time3 = (-p0 + (p1 * 3.0f) - (p2 * 3.0f) + p3) * (t * t * t);

	Vector3 position = (time1 + time2 + time3);
	position = position / 2.0f;

	return position;
}

Vector3 MotionMath::Leap(const Vector3& startPos, const Vector3& endPos, const float timeRate)
{
	return startPos * (1.0f - timeRate) + endPos * timeRate;
}
