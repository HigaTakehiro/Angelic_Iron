#include "PlayerBullet.h"

const float PlayerBullet::bulletSpeed = 5.0f;

PlayerBullet::PlayerBullet() {

}

PlayerBullet::~PlayerBullet() {
	safe_delete(bullet_);
}

void PlayerBullet::Initialize(const Vector3& pos, const Vector3& velocity, Object3d* target) {
	const Vector3 bulletSize = { 1.0f, 1.0f, 1.0f };

	bullet_ = Object3d::Create(ModelManager::GetIns()->GetModel("bullet"));
	bullet_->SetScale(bulletSize);
	bullet_->SetRotation(Vector3(0, 0, 0));
	pos_ = pos;
	velocity_ = velocity;
	bullet_->SetPosition(pos_);
	bullet_->SetObjType((int32_t)Object3d::OBJType::Player | (int32_t)Object3d::OBJType::Bullet);
	bullet_->SetHitRadius(2.0f);
	bullet_->SetColType(Object3d::CollisionType::Sphere);

	if (target != nullptr) {
		target_ = target;
		isHoming_ = true;
	}
}

void PlayerBullet::Update() {
	const int32_t timeOver = 0;
	const int32_t noObjType = -1;
	if (target_) {
		if (target_->GetObjType() <= noObjType) {
			isHoming_ = false;
		}
	}

	if (--lifeTimer_ <= timeOver) {
		isDead_ = true;
	}
	else if (target_ != nullptr && isHoming_){
		velocity_ = target_->GetMatWorld().r[3] - pos_;
		velocity_ = velocity_.normalize();
		pos_ += velocity_ * bulletSpeed;
	}
	else {
		pos_ += velocity_ * bulletSpeed;
	}

	if (bullet_->GetIsHit()) {
		OnCollision();
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
