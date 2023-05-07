#include "Bomb.h"

using namespace DirectX;

Bomb::Bomb() {

}

Bomb::~Bomb() {
	safe_delete(bullet_);
}

void Bomb::Initialize(const Vector3& playerPos, Object3d* target) {
	const Vector3 bulletScale = { 2, 2, 2 };
	const Vector3 bulletRot = { 0, 0, 0 };

	bullet_ = Object3d::Create(ModelManager::GetIns()->GetModel("bullet"));
	bullet_->SetScale(bulletScale);
	bullet_->SetRotation(bulletRot);
	bulletPos_ = playerPos;
	initBulletPos_ = playerPos;
	targetEnemy_ = target;
	bullet_->SetPosition(bulletPos_);
	isUp_ = true;
}

void Bomb::Update() {
	const float bulletSpeed = 5.0f;
	Vector3 enemyPos = targetEnemy_->GetMatWorld().r[3];

	XMVECTOR velocity = {0, 1, 0};
	if (bulletPos_.y >= initBulletPos_.y + 100.0f) {
		isUp_ = false;
	}

	if (!isUp_) {
		velocity.m128_f32[0] = enemyPos.x - bulletPos_.x;
		velocity.m128_f32[1] = enemyPos.y - bulletPos_.y;
		velocity.m128_f32[2] = enemyPos.z - bulletPos_.z;
	}

	velocity = XMVector3Normalize(velocity) * bulletSpeed;

	bulletPos_ += velocity;

	bullet_->SetPosition(bulletPos_);
	bullet_->Update();
}

void Bomb::Draw() {
	bullet_->Draw();
}

void Bomb::OnCollision() {
	isDead_ = true;
}