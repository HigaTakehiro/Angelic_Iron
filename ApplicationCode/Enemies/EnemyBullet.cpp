#include "EnemyBullet.h"

EnemyBullet::EnemyBullet() {

}

EnemyBullet::~EnemyBullet() {
	safe_delete(enemyBullet);
}

void EnemyBullet::Initialize(const Vector3& pos, const Vector3& velocity, bool isHoming) {
	const Vector3 bulletSize = { 2, 2, 2 };

	enemyBullet = Object3d::Create(ModelManager::GetIns()->GetModel("block"));
	enemyBullet->SetScale(bulletSize);
	enemyBullet->SetRotation(Vector3(0, 0, 0));
	this->pos = pos;
	this->velocity = velocity;
	initVelocity = velocity;
	this->isHoming = isHoming;
	enemyBullet->SetPosition(pos);
}

void EnemyBullet::Update() {
	const int32_t timeOver = 0;

	if (--lifeTimer <= timeOver) {
		isDead = true;
	}
	else {
		pos += velocity;
	}

	if (enemyBullet != nullptr) {
		enemyBullet->SetPosition(pos);
		enemyBullet->Update();
	}
}

void EnemyBullet::Draw() {
	enemyBullet->Draw();
}

void EnemyBullet::OnCollision() {

}