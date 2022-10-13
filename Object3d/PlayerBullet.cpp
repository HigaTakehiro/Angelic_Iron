#include "PlayerBullet.h"

PlayerBullet::PlayerBullet() {

}

PlayerBullet::~PlayerBullet() {
	safe_delete(bullet);
}

void PlayerBullet::Initialize(const Vector3& pos, const Vector3& velocity) {
	const Vector3 bulletSize = { 2, 2, 2 };

	bullet = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Shot));
	bullet->SetScale(bulletSize);
	bullet->SetRotation(Vector3(0, 0, 0));
	this->pos = pos;
	this->velocity = velocity;
	bullet->SetPosition(pos);
}

void PlayerBullet::Update() {
	const int timeOver = 0;

	if (--lifeTimer <= timeOver) {
		isDead = true;
	}
	else {
		pos += velocity;
	}

	if (bullet != nullptr) {
		bullet->SetPosition(pos);
		bullet->Update();
	}
}

void PlayerBullet::Draw() {
	bullet->Draw();
}

void PlayerBullet::OnCollision() {
	isDead = true;
}
