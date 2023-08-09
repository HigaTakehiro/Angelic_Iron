#include "EnemyBullet.h"

EnemyBullet::EnemyBullet() {

}

EnemyBullet::~EnemyBullet() {
	safe_delete(enemyBullet_);
	//safe_delete(playerObj_);
}

void EnemyBullet::Initialize(const Vector3& pos, const Vector3& velocity, Object3d* playerObj) {
	const Vector3 bulletSize = { 2, 2, 2 };

	enemyBullet_ = Object3d::Create(ModelManager::GetIns()->GetModel("block"));
	enemyBullet_->SetScale(bulletSize);
	enemyBullet_->SetRotation(Vector3(0, 0, 0));
	pos_ = pos;
	velocity_ = velocity;
	initVelocity_ = velocity;
	if (playerObj != nullptr) {
		playerObj_ = playerObj;
		isHoming_ = true;
	}
	enemyBullet_->SetPosition(pos_);
	enemyBullet_->SetObjType((int32_t)Object3d::OBJType::Bullet | (int32_t)Object3d::OBJType::Enemy);
	enemyBullet_->SetColType(Object3d::CollisionType::Sphere);
}

void EnemyBullet::Update() {
	const int32_t timeOver = 0;

	if (isHoming_ && --homingTimer_ > timeOver) {
		const float bulletSpeed = 2.0f;
		Vector3 playerWPos = playerObj_->GetMatWorld().r[3];
		Vector3 bulletPos = enemyBullet_->GetMatWorld().r[3];
		Vector3 vector = playerWPos - bulletPos;
		vector.normalize();
		velocity_ = vector * bulletSpeed;
	}

	if (--lifeTimer_ <= timeOver) {
		isDead_ = true;
	}
	else {
		pos_ += velocity_;
	}

	if (enemyBullet_->GetIsHit()) {
		OnCollision();
	}

	if (enemyBullet_ != nullptr) {
		enemyBullet_->SetPosition(pos_);
		enemyBullet_->Update();
	}
}

void EnemyBullet::Draw() {
	enemyBullet_->Draw();
}

void EnemyBullet::OnCollision() {

}