#include "PlayerBullet.h"

PlayerBullet::PlayerBullet() {

}

PlayerBullet::~PlayerBullet() {
	safe_delete(bullet);
}

void PlayerBullet::Initialize(const Vector3& pos, const Vector3& velocity) {
	const Vector3 bulletSize = { 1.0f, 1.0f, 1.0f };

	bullet = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Bullet));
	bullet->SetScale(bulletSize);
	bullet->SetRotation(Vector3(0, 0, 0));
	this->pos = pos;
	this->velocity = velocity;
	bullet->SetPosition(pos);
	delayCount = 0;
}

void PlayerBullet::Update(const float delayTime) {
	const int timeOver = 0;
	delayCount++;

	if (delayCount >= delayTime) {
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

		delayCount = 0;
	}
	
}

void PlayerBullet::Draw() {
	bullet->Draw();
}

void PlayerBullet::OnCollision() {
	isDead = true;
}
