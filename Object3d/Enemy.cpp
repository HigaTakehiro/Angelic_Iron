#include "Enemy.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <wrl.h>

using namespace std;

void Enemy::Initialize(const string& modelName, const Vector3& pos, const Vector3& rot, const Vector3& scale) {
	enemy = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Enemy));
	enemy->SetPosition(pos);
	oldPos = pos;
	enemy->SetRotation(rot);
	enemy->SetScale(scale);
	//this->type = stringToEnemyStyle(type);
}

void Enemy::Update() {
	if (enemy != nullptr) {
		//EnemyAction();
		enemy->Update();
	}
}

void Enemy::Draw() {
	enemy->Draw();
}

void Enemy::OnCollision() {
	isDead = true;
}

Enemy::EnemyStyle Enemy::stringToEnemyStyle(const string& type) {
	Enemy::EnemyStyle style;
	if (type == "STOP_PTAG") {
		style = STOP_PTAG;
	}
	else if (type == "STOP_STR") {
		style = STOP_STR;
	}
	else if (type == "UDMOVE_PTAG") {
		style = UDMOVE_PTAG;
	}
	else if (type == "UDMOVE_STR") {
		style = UDMOVE_STR;
	}
	else if (type == "LRMOVE_PTAG") {
		style = LRMOVE_PTAG;
	}
	else if (type == "LRMOVE_STR") {
		style = LRMOVE_STR;
	}

	return style;
}

void Enemy::EnemyAction() {
	float moveSpeed = 0.2f;
	const float overPosY = 40.0f;
	const float overPosX = 10.0f;

	if (type == UDMOVE_PTAG || type == UDMOVE_STR) {
		//if (pos.y >= oldPos.y + overPosY || pos.y <= oldPos.y - overPosY) {
		//	moveSpeed *= -1.0f;
		//}
		pos.y += moveSpeed;
	}
	if (type == LRMOVE_PTAG || type == LRMOVE_STR) {
		//if (pos.x >= oldPos.x + overPosX || pos.x <= oldPos.y - overPosY) {
		//	moveSpeed * -1.0f;
		//}
		pos.x += moveSpeed;
	}

	enemy->SetPosition(pos);
}