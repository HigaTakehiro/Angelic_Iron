#include "BulletCase.h"

BulletCase::~BulletCase()
{
	safe_delete(bulletCase);
}

void BulletCase::Initialize(const Vector3& pos, const Vector3& velocity, const Vector3& rot)
{
	const Vector3 bulletCaseSize = { 0.2f, 0.2f, 0.2f };

	bulletCase = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::BulletCase));
	bulletCase->SetScale(bulletCaseSize);
	bulletCase->SetRotation(rot);
	this->pos = pos;
	bulletCase->SetPosition(this->pos);
	this->velocity = velocity;
	delayCount = 0;
}

void BulletCase::Update(const float delayTime)
{
	const int timeOver = 0;
	delayCount++;

	if (delayCount >= delayTime) {
		if (--lifeTimer <= timeOver) {
			isDead = true;
		}
		else {
			velocity.y -= 0.2f;
			pos += velocity;
		}

		if (bulletCase != nullptr) {
			bulletCase->SetPosition(pos);
			bulletCase->Update();
		}

		delayCount = 0;
	}
}

void BulletCase::Draw()
{
	bulletCase->Draw();
}
