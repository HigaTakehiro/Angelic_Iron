#include "Bomb.h"

using namespace DirectX;

Bomb::Bomb() {

}

Bomb::~Bomb() {
	safe_delete(bullet);
}

void Bomb::Initialize(const Vector3& playerPos, Object3d* target) {
	const Vector3 bulletScale = { 2, 2, 2 };
	const Vector3 bulletRot = { 0, 0, 0 };

	bullet = Object3d::Create(ModelManager::GetIns()->GetModel("bullet"));
	bullet->SetScale(bulletScale);
	bullet->SetRotation(bulletRot);
	bulletPos = playerPos;
	initBulletPos = playerPos;
	targetEnemy = target;
	bullet->SetPosition(bulletPos);
	isUp = true;
}

void Bomb::Update() {
	const float bulletSpeed = 5.0f;
	Vector3 enemyPos = targetEnemy->GetMatWorld().r[3];

	XMVECTOR velocity = {0, 1, 0};
	if (bulletPos.y >= initBulletPos.y + 100.0f) {
		isUp = false;
	}

	if (!isUp) {
		velocity.m128_f32[0] = enemyPos.x - bulletPos.x;
		velocity.m128_f32[1] = enemyPos.y - bulletPos.y;
		velocity.m128_f32[2] = enemyPos.z - bulletPos.z;
	}

	velocity = XMVector3Normalize(velocity) * bulletSpeed;

	bulletPos += velocity;

	bullet->SetPosition(bulletPos);
	bullet->Update();
}

void Bomb::Draw() {
	bullet->Draw();
}

void Bomb::OnCollision() {
	isDead = true;
}