#include "EnemyBullet.h"

EnemyBullet::EnemyBullet() {

}

EnemyBullet::~EnemyBullet() {
	safe_delete(enemyBullet);
}

void EnemyBullet::Initialize(const Vector3& pos, const Vector3& velocity, bool isHoming) {
	const Vector3 bulletSize = { 2, 2, 2 };

	enemyBullet = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Shot));
	enemyBullet->SetScale(bulletSize);
	enemyBullet->SetRotation(Vector3(0, 0, 0));
	this->pos = pos;
	this->velocity = velocity;
	enemyBullet->SetPosition(pos);
}

void EnemyBullet::Update() {

}

void EnemyBullet::Draw() {

}

void EnemyBullet::OnCollision() {

}