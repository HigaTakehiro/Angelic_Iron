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
	accel_ = 1.0f;
	isUp_ = true;
}

void Bomb::Update() {
	const float bulletSpeed = 3.0f;
	Vector3 enemyPos = targetEnemy_->GetMatWorld().r[3];

	accel_ = bulletSpeed * bulletSpeed;
	float halfLength = enemyPos.x - bulletPos_.x;
	if (halfLength < 0) {
		halfLength *= -1;
	}
	if (halfLength < -(enemyPos.y - bulletPos_.y)) {
		halfLength = -(enemyPos.y - bulletPos_.y);
	}
	if (halfLength < -(enemyPos.z - bulletPos_.z)) {
		halfLength = -(enemyPos.z - bulletPos_.z);
	}
	accel_ /= (halfLength / 2);

	XMVECTOR toTarget;
	toTarget.m128_f32[0] = enemyPos.x - bulletPos_.x;
	toTarget.m128_f32[1] = enemyPos.y - bulletPos_.y;
	toTarget.m128_f32[2] = enemyPos.z - bulletPos_.z;

	XMVECTOR velocity = vector_;
	XMVECTOR vn = XMVector3TransformNormal(velocity, Camera::GetMatWorld());
	XMVECTOR dot = XMVector3Dot(toTarget, vn);
	Vector3 centripetalAccel = toTarget - (vn * dot);
	float centripetalAccelLength = centripetalAccel.length();
	if (centripetalAccelLength > 1.0f) {
		centripetalAccel /= centripetalAccelLength;
	}
	XMVECTOR force;
	force.m128_f32[0] = centripetalAccel.x * bulletSpeed;
	force.m128_f32[1] = centripetalAccel.y * bulletSpeed;
	force.m128_f32[2] = centripetalAccel.z * bulletSpeed;
	force += vn * accel_;
	force -= XMVector3Normalize(force);
	velocity += force;

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