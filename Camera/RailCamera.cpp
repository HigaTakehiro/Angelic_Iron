#include "RailCamera.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <sysinfoapi.h>

void RailCamera::Initialize(const Vector3& eye, const Vector3& rot, const std::vector<Vector3>& points, const float& maxTime) {
	this->eye = eye;
	this->rot = rot;
	this->points = points;
	this->maxTime = maxTime;
	startTime = GetTickCount64();
}

void RailCamera::Update() {
	nowCount = GetTickCount64();
	elapsedCount = nowCount - startTime;
	float elapsedTime = static_cast<float> (elapsedCount) / 1000000.0f;

	timeRate = elapsedCount / maxTime;

	if (timeRate >= 1.0f) {
		if (startIndex < points.size() - 3) {
			startIndex += 1;
			timeRate -= 1.0f;
			startTime = GetTickCount64();
		}
		else {
			startIndex = 0;
			timeRate = 1.0f;
		}
	}

	eye = Spline(points, startIndex, timeRate) * -1.0f;
}

Vector3 RailCamera::Spline(const std::vector<Vector3>& points, const int& startIndex, const float& t) {
	int n = points.size() - 2;

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