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
	targetEnemy_ = target;
	velocity_ = XMVector3TransformNormal(vector, Camera::GetMatWorld());
	bullet_->SetPosition(bulletPos_);
	bullet_->SetObjType((int32_t)Object3d::OBJType::Bomb);
	bullet_->SetColType(Object3d::CollisionType::Sphere);
}

void Bomb::Update() {
	const float bulletSpeed = 10.0f;
	const float maxAccel = bulletSpeed * bulletSpeed / 500.0f;
	const float damping = 0.2f;
	const float propulsion = bulletSpeed * damping;
	Vector3 enemyPos = targetEnemy_->GetMatWorld().r[3];

	if (lifeTimer_++ >= lifeTime) {
		isDead_ = true;
	}
	if (bullet_->GetIsBombHit()) {
		OnCollision();
	}

	Vector3 toTarget = enemyPos - bulletPos_;
	Vector3 normalVel = velocity_.normalize();
	float dot = toTarget.dot(normalVel);
	Vector3 accel = toTarget - (normalVel * dot);
	float accelLength = accel.length();
	if (accelLength > 1.0f) {
		accel /= accelLength;
	}
	Vector3 force = accel * maxAccel;
	force += normalVel * propulsion;
	force -= velocity_ * damping;
	velocity_ += force;
	if (coercionAttackTimer_++ >= coercionAttackTime) {
		velocity_ += toTarget.normalize();
	}

	bulletPos_ += velocity_;

	bullet_->SetPosition(bulletPos_);
	bullet_->Update();
}

void Bomb::Draw() {
	bullet_->Draw();
}

void Bomb::OnCollision() {
	isDead_ = true;
}