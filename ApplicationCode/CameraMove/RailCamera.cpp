#include "RailCamera.h"
#include "DirectXSetting.h"
#include <sstream>
#include "ExternalFileLoader.h"

using namespace DirectX;

void RailCamera::Initialize(const std::string& fileName)
{
	LoadRailPoint(fileName);
	nowCount_ = 0;
}

void RailCamera::Update() {
	//デバッグ用一時停止
	//if (KeyInput::GetIns()->TriggerKey(DIK_P)) {
	//	isStop_ = !isStop_;
	//}

	if (!isStop_) {
		SplineMove();
	}
	else {
		if (KeyInput::GetIns()->PushKey(DIK_LEFT)) {
			rot_.y -= 1.0f;
		}
		if (KeyInput::GetIns()->PushKey(DIK_RIGHT)) {
			rot_.y += 1.0f;
		}
		if (KeyInput::GetIns()->PushKey(DIK_UP)) {
			rot_.x -= 1.0f;
		}
		if (KeyInput::GetIns()->PushKey(DIK_DOWN)) {
			rot_.x += 1.0f;
		}
	}
	UpdateMatWorld();
}

Vector3 RailCamera::Spline(const std::vector<Vector3>& points, int32_t startIndex, float t) {
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

void RailCamera::SplineMove() {
	//移動にかかる時間
	float maxTime = 1.0f;
	//移動する地点
	Vector3 point;

	if (startIndex_ < movePoints_.moveTime_.size() - 3 && movePoints_.moveTime_[startIndex_] > 0.0f) {
		maxTime = movePoints_.moveTime_[startIndex_];
	}

	nowCount_++;
	elapsedCount_ = nowCount_;
	timeRate_ = elapsedCount_ / maxTime;

	if (timeRate_ >= 1.0f) {
		if (startIndex_ < movePoints_.points_.size() - 3) {
			startIndex_ += 1;
			timeRate_ -= 1.0f;
			nowCount_ = 0;
		}
		else {
			if (isRoop_) {
				startIndex_ = 0;
			}
			isEnd_ = true;
			timeRate_ = 1.0f;
		}
	}
	else {
		Vector3 moveRot;
		moveRot = movePoints_.cameraRot_[startIndex_];
		rot_ = easeIn(rot_, moveRot, timeRate_);
	}

	eye_ = Spline(movePoints_.points_, startIndex_, timeRate_);
	Camera::SetEye(eye_);

}

void RailCamera::UpdateMatWorld() {
	XMMATRIX matRot, matTrans;

	//回転、平行移動行列の計算
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rot_.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rot_.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rot_.y));
	matTrans = XMMatrixTranslation(eye_.x, eye_.y, eye_.z);

	matWorld_ = XMMatrixIdentity();
	matWorld_ *= matRot;
	matWorld_ *= matTrans;

	XMVECTOR forward = { 0, 0, 1 };
	forward = XMVector3TransformNormal(forward, matWorld_);
	target_ = eye_ + forward;
	XMVECTOR up = { 0, 1, 0 };
	up = XMVector3TransformNormal(up, matWorld_);
	Camera::SetTarget(target_);
	Camera::SetUp(XMFLOAT3(up.m128_f32[0], up.m128_f32[1], up.m128_f32[2]));
	Camera::SetMatWorld(matWorld_);
}

void RailCamera::LoadRailPoint(const std::string& fileName)
{
	//ファイルストリーム
	std::stringstream railcameraPointsData;
	railcameraPointsData = ExternalFileLoader::GetIns()->ExternalFileOpen(fileName);

	std::string line;
	Vector3 pos{};
	Vector3 rot{};
	rot = { 0, 0, 0 };
	Vector3 startPos{};
	bool isStart = false;
	bool isEnd = false;
	bool isRoop = false;
	bool isCameraRoop = false;
	bool isPoint = false;
	bool isTime = false;
	bool isRot = false;
	float splineTime = 0;
	int32_t stringCount = 0;
	std::vector<Vector3> points;
	std::vector<Vector3> cameraRots;
	std::vector<float> cameraMoveTimes;

	while (getline(railcameraPointsData, line)) {
		std::istringstream line_stream(line);
		std::string word;
		//半角区切りで文字列を取得
		getline(line_stream, word, ' ');
		if (word == "#") {
			continue;
		}
		if (word == "Start") {
			line_stream >> startPos.x;
			line_stream >> startPos.y;
			line_stream >> startPos.z;
			isStart = true;
		}

		if (word == "Pos") {
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;
			isPoint = true;
		}

		if (word == "End") {
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;
			isEnd = true;
		}

		if (word == "Roop") {
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;
			isRoop = true;
		}

		if (word == "Time") {
			line_stream >> splineTime;
			isTime = true;
		}

		if (word == "Rot") {
			line_stream >> rot.x;
			line_stream >> rot.y;
			line_stream >> rot.z;
			isRot = true;
		}

		if (isStart) {
			points.push_back(startPos);
			points.push_back(startPos);
			cameraMoveTimes.push_back(0);
			isStart = false;
		}
		else if (isEnd) {
			points.push_back(pos);
			points.push_back(pos);
			cameraRots.emplace_back(cameraRots.back());
			cameraMoveTimes.push_back(0);
			isEnd = false;
		}
		else if (isRot) {
			if (cameraRots.size() <= 0) {
				cameraRots.push_back(rot);
			}
			cameraRots.push_back(rot);
			isRot = false;
		}
		else if (isRoop) {
			points.push_back(pos);
			points.push_back(startPos);
			points.push_back(startPos);
			isRoop = false;
			isCameraRoop = true;
		}
		else if (isTime) {
			splineTime *= 60;
			cameraMoveTimes.push_back(splineTime);
			isTime = false;
		}
		else if (isPoint) {
			points.push_back(pos);
		}

		stringCount++;
	}

	movePoints_.points_ = points;
	movePoints_.cameraRot_ = cameraRots;
	movePoints_.moveTime_ = cameraMoveTimes;

	rot_ = cameraRots.front();

}
