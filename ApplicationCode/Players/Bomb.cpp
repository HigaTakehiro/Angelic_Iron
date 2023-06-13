#include "Bomb.h"

using namespace DirectX;

Bomb::Bomb() {

}

Bomb::~Bomb() {
	safe_delete(bullet_);
}

void Bomb::Initialize(const Vector3& playerPos, Object3d* target, const XMVECTOR& vector) {
	const Vector3 bulletScale = { 2, 2, 2 };
	const Vector3 bulletRot = { 0, 0, 0 };

	bullet_ = Object3d::Create(ModelManager::GetIns()->GetModel("bullet"));
	bullet_->SetScale(bulletScale);
	bullet_->SetRotation(bulletRot);
	bulletPos_ = playerPos;
	initBulletPos_ = playerPos;
	targetEnemy_ = target;
	vector_ = vector;
	bullet_->SetPosition(bulletPos_);
	isUp_ = true;
}

void Bomb::Update() {
	const float bulletSpeed = 3.0f;
	Vector3 enemyPos = targetEnemy_->GetMatWorld().r[3];

	XMVECTOR velocity = vector_;
	velocity = XMVector3TransformNormal(vector_, Camera::GetMatWorld());
	if (++bombTimer_ > bombTime_) {
		isUp_ = false;
	}

	if (!isUp_) {
		velocity.m128_f32[0] = enemyPos.x - bulletPos_.x;
		velocity.m128_f32[1] = enemyPos.y - bulletPos_.y;
		velocity.m128_f32[2] = enemyPos.z - bulletPos_.z;
		velocity = XMVector3Normalize(velocity);
	}

	velocity = velocity * bulletSpeed;

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