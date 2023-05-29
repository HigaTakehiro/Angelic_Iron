#include "SpreadEnemy.h"

SpreadEnemy::~SpreadEnemy()
{
	safe_delete(enemy_);
	safe_delete(target_);
}

void SpreadEnemy::Initialize(const std::string modelKey, const Vector3& pos, const Vector3& rot)
{
	enemy_ = Object3d::Create(ModelManager::GetIns()->GetModel(modelKey));
	enemy_->SetPosition(pos);
	target_ = Sprite::Create((UINT)ImageManager::ImageName::aim, { 0, 0 });
	target_->SetSize(XMFLOAT2(100.0f, 100.0f));
	target_->SetAnchorPoint({ 0.5f, 0.5f });
	oldPos_ = pos;
	enemy_->SetRotation(rot);
	enemy_->SetScale(scale_);
	hp_ = 1;
	shotIntervalTime_ = 60;
	shotIntervalTimer_ = 0;
	lifeTime_ = 240;
	lifeTimer_ = 0;
	targetReactionTimer_ = 0;
}

void SpreadEnemy::Update()
{
	const int32_t lifeTimeOver = 0;

	if (hp_ <= 0) {
		DeadPerformance();
	}
	if (++lifeTimer_ >= lifeTime_) {
		isDead_ = true;
	}

	if (enemy_ != nullptr && hp_ > 0) {
		if (pos_.x == 0 && pos_.y == 0 && pos_.z == 0) {
			pos_ = oldPos_;
		}
		Move();
		Attack();
		Damage();
	}

	enemy_->Update();
}

void SpreadEnemy::Draw()
{
	enemy_->Draw();
}

void SpreadEnemy::SpriteDraw()
{
	if (isTarget_) {
		target_->Draw();
	}
}

void SpreadEnemy::DeadPerformance()
{
	const float downSpeed = 0.5f;
	const float rotSpeed = 15.0f;
	XMFLOAT3 enemyPos = enemy_->GetPosition();
	XMFLOAT3 enemyRot = enemy_->GetRotation();
	deadTimer_++;
	enemyPos.y -= downSpeed;
	enemyRot.y += rotSpeed;
	enemy_->SetPosition(enemyPos);
	enemy_->SetRotation(enemyRot);
	if (deadTimer_ >= deadTime) {
		isScoreItemDrop_ = true;
		isDead_ = true;
	}
}

void SpreadEnemy::Attack()
{
	if (++shotIntervalTimer_ <= shotIntervalTime_) return;
	for (int32_t i = 1; i <= 9; i++) {
		const float bulletSpeed = 0.4f;
		XMVECTOR velocity = { 0, 0, 1 };
		if (i > 0) {
			velocity.m128_f32[1] = -0.5f;
			if (i < 2) velocity.m128_f32[0] = -0.5f;
			else if (i > 2) velocity.m128_f32[0] = 0.5f;
			else velocity.m128_f32[0] = 0;
		}
		if (i > 3) {
			velocity.m128_f32[1] = 0;
			if (i < 5) velocity.m128_f32[0] = -0.5f;
			else if (i > 5) velocity.m128_f32[0] = 0.5f;
			else velocity.m128_f32[0] = 0;
		}
		if (i > 6) {
			velocity.m128_f32[1] = 0.5f;
			if (i < 8) velocity.m128_f32[0] = -0.5f;
			else if (i > 8) velocity.m128_f32[0] = 0.5f;
			else velocity.m128_f32[0] = 0;
		}

		velocity = XMVector3TransformNormal(velocity, enemy_->GetMatWorld());
		velocity *= bulletSpeed;

		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(enemy_->GetMatWorld().r[3], velocity);

		bulletManager_->AddEnemyBullet(std::move(newBullet));
		shotIntervalTimer_ = 0;
	}

}
