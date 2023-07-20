#include "PlayerBullet.h"

PlayerBullet::PlayerBullet() {

}

PlayerBullet::~PlayerBullet() {
	safe_delete(bullet_);
}

void PlayerBullet::Initialize(const Vector3& pos, const Vector3& velocity) {
	const Vector3 bulletSize = { 1.0f, 1.0f, 1.0f };

	bullet_ = Object3d::Create(ModelManager::GetIns()->GetModel("bullet"));
	bullet_->SetScale(bulletSize);
	bullet_->SetRotation(Vector3(0, 0, 0));
	pos_ = pos;
	velocity_ = velocity;
	bullet_->SetPosition(pos_);
	bullet_->SetObjType(Object3d::OBJType::PlayerBullet);
	bullet_->SetColType(Object3d::CollisionType::Sphere);
}

void PlayerBullet::Update() {
	const int32_t timeOver = 0;
	if (--lifeTimer_ <= timeOver) {
		isDead_ = true;
	}
	else {
		pos_ += velocity_;
	}

	if (bullet_ != nullptr) {
		bullet_->SetPosition(pos_);
		bullet_->Update();
	}
}

void PlayerBullet::Draw() {
	bullet_->Draw();
}

void PlayerBullet::OnCollision() {
	isDead_ = true;
}
