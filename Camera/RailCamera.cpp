#include "RailCamera.h"
#include "DirectXCommon.h"

void RailCamera::Initialize(const Vector3& eye, const Vector3& rot, const std::vector<Vector3>& points, const float& maxTime) {
	this->eye = eye;
	initPos = eye;
	this->rot = rot;
	initRot = rot;
	this->points = points;
	this->maxTime = maxTime;
	startTime = GetTickCount64();
}

void RailCamera::Update() {
	if (KeyInput::GetIns()->TriggerKey(DIK_P)) {
		if (isStop) {
			isStop = false;
		}
		else {
			isStop = true;
		}
	}

	if (isStop) {
		SplineMove();
	}
	else {
		if (KeyInput::GetIns()->PushKey(DIK_LEFT)) {
			rot.y -= 1.0f;
		}
		if (KeyInput::GetIns()->PushKey(DIK_RIGHT)) {
			rot.y += 1.0f;
		}
		if (KeyInput::GetIns()->PushKey(DIK_UP)) {
			rot.x -= 1.0f;
		}
		if (KeyInput::GetIns()->PushKey(DIK_DOWN)) {
			rot.x += 1.0f;
		}
	}
	UpdateMatWorld();
	Camera::SetEye(eye);
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

void RailCamera::SplineMove() {
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
	else {
		Vector3 distance;
		float xRot, yRot;
		distance = Vector3(points[startIndex + 1].x - eye.x, points[startIndex + 1].y - eye.y, points[startIndex + 1].z - eye.z);
		xRot = -(atan2(distance.y, sqrtf(pow(distance.z, 2)) + pow(distance.x, 2)) * 180.0f / 3.14f);
		yRot = (atan2(distance.x, distance.z) * 180.0f / 3.14f);
		if (rot.x < xRot) {
			rot.x += 0.1f;
		}
		else if (rot.x > xRot) {
			rot.x -= 0.1f;
		}

		if (rot.y < yRot) {
			rot.y += 0.1f;
		}
		else if (rot.y > yRot) {
			rot.y -= 0.1f;
		}
	}

	eye = Spline(points, startIndex, timeRate);
}

void RailCamera::UpdateMatWorld() {
	XMMATRIX matRot, matTrans;

	//‰ñ“]A•½sˆÚ“®s—ñ‚ÌŒvŽZ
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rot.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rot.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rot.y));
	matTrans = XMMatrixTranslation(eye.x, eye.y, eye.z);

	matWorld = XMMatrixIdentity();
	matWorld *= matRot;
	matWorld *= matTrans;

	XMVECTOR forward = { 0, 0, 1 };
	forward = MatCalc::GetIns()->VecDivided(forward, matWorld);
	target = eye + forward;
	XMVECTOR up = { 0, 1, 0 };
	up = MatCalc::GetIns()->VecDivided(up, matWorld);
	Camera::SetTarget(target);
	Camera::SetUp(XMFLOAT3(up.m128_f32[0], up.m128_f32[1], up.m128_f32[2]));
	Camera::SetMatWorld(matWorld);
}

void RailCamera::Reset() {
	eye = initPos;
	rot = initRot;
	startIndex = 1;
	startTime = GetTickCount64();
}