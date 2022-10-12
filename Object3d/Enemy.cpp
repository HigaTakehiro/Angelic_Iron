#include "Enemy.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <wrl.h>

using namespace std;

Enemy::Enemy() {

}

Enemy::~Enemy() {
	delete enemy;
}

void Enemy::Initialize(const string& modelName, const Vector3& pos, const Vector3& rot, const Vector3& scale, const string& style) {
	enemy = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Enemy));
	enemy->SetPosition(pos);
	oldPos = pos;
	enemy->SetRotation(rot);
	enemy->SetScale(scale);
	type = stringToEnemyStyle(style);
	moveSpeed = 0.2f;
}

void Enemy::Update() {
	if (enemy != nullptr) {
		if (pos.x == 0 && pos.y == 0 && pos.z == 0) {
			pos = oldPos;
		}
		EnemyAction();
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
	Enemy::EnemyStyle style = EnemyStyle::STOP_PTAG;
	if (type == "STOP_PTAG") {
		style = EnemyStyle::STOP_PTAG;
	}
	else if (type == "STOP_STR") {
		style = EnemyStyle::STOP_STR;
	}
	else if (type == "UDMOVE_PTAG") {
		style = EnemyStyle::UDMOVE_PTAG;
	}
	else if (type == "UDMOVE_STR") {
		style = EnemyStyle::UDMOVE_STR;
	}
	else if (type == "LRMOVE_PTAG") {
		style = EnemyStyle::LRMOVE_PTAG;
	}
	else if (type == "LRMOVE_STR") {
		style = EnemyStyle::LRMOVE_STR;
	}

	return style;
}

void Enemy::EnemyAction() {
	const float overPosY = 40.0f;
	const float overPosX = 10.0f;

	if (type == EnemyStyle::UDMOVE_PTAG || type == EnemyStyle::UDMOVE_STR) {
		if (pos.y >= oldPos.y + overPosY || pos.y <= oldPos.y - overPosY) {
			moveSpeed *= -1.0f;
		}
		pos.y += moveSpeed;
	}
	if (type == EnemyStyle::LRMOVE_PTAG || type == EnemyStyle::LRMOVE_STR) {
		if (pos.x >= oldPos.x + overPosX || pos.x <= oldPos.y - overPosY) {
			moveSpeed * -1.0f;
		}
		pos.x += moveSpeed;
	}

	enemy->SetPosition(pos);
}