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
	initVelocity = velocity;
	this->isHoming = isHoming;
	enemyBullet->SetPosition(pos);
	delayCount = 0;
}

void EnemyBullet::Update(float delayTime) {
	const int timeOver = 0;
	delayCount++;

	if (delayCount >= delayTime) {
		if (delayTime != 0 && velocity.x == initVelocity.x && velocity.y == initVelocity.y && velocity.z == initVelocity.z) {
			velocity /= 5;
		}
		else if (delayTime == 0 && velocity.x != initVelocity.x && velocity.y != initVelocity.y && velocity.z != initVelocity.z) {
			velocity = initVelocity;
		}

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

}

void EnemyBullet::Draw() {
	enemyBullet->Draw();
}

void EnemyBullet::OnCollision() {

}