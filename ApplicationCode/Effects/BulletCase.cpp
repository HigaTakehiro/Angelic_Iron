#include "BulletCase.h"

BulletCase::~BulletCase()
{
	safe_delete(bulletCase_);
}

void BulletCase::Initialize(const Vector3& pos, const Vector3& velocity, const Vector3& rot)
{
	const Vector3 bulletCaseSize = { 0.2f, 0.2f, 0.2f };

	bulletCase_ = Object3d::Create(ModelManager::GetIns()->GetModel("bulletCase"));
	bulletCase_->SetScale(bulletCaseSize);
	bulletCase_->SetRotation(rot);
	pos_ = pos;
	bulletCase_->SetPosition(pos_);
	this->velocity_ = velocity;
}

void BulletCase::Update()
{
	const int32_t timeOver = 0;

	if (--lifeTimer_ <= timeOver) {
		isDead_ = true;
	}
	else {
		velocity_.y -= 0.2f;
		pos_ += velocity_;
	}

	if (bulletCase_ != nullptr) {
		bulletCase_->SetPosition(pos_);
		bulletCase_->Update();
	}
}

void BulletCase::Draw()
{
	bulletCase_->Draw();
}
