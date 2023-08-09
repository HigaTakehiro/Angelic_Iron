#include "StraightEnemy.h"

StraightEnemy::~StraightEnemy() {
	safe_delete(enemy_);
	safe_delete(target_);
}

void StraightEnemy::Initialize(const std::string modelKey, const Vector3& pos, const Vector3& rot) {
	enemy_ = Object3d::Create(ModelManager::GetIns()->GetModel(modelKey));
	enemy_->SetPosition(pos);
	target_ = Sprite::Create((UINT)ImageManager::ImageName::aim, { 0, 0 });
	target_->SetSize(XMFLOAT2(100.0f, 100.0f));
	target_->SetAnchorPoint({ 0.5f, 0.5f });
	oldPos_ = pos;
	enemy_->SetRotation(rot);
	enemy_->SetScale(scale_);
	enemy_->SetObjType((int32_t)Object3d::OBJType::Enemy);
	enemy_->SetColType(Object3d::CollisionType::Sphere);
	hp_ = 1;
	shotIntervalTime_ = 60;
	shotIntervalTimer_ = 0;
	lifeTime_ = 240;
	lifeTimer_ = 0;
	targetReactionTimer_ = 0;
}

void StraightEnemy::Update()
{
	const int32_t lifeTimeOver = 0;

	if (hp_ <= 0) {
		DeadPerformance();
	}
	if (++lifeTimer_ >= lifeTime_) {
		isDead_ = true;
	}
	if (enemy_->GetIsHit()) {
		OnCollision();
	}
	if (enemy_->GetIsBombHit()) {
		BombHitCollision();
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

void StraightEnemy::Draw()
{
	enemy_->Draw();
}

void StraightEnemy::SpriteDraw()
{
	if (isTarget_) {
		target_->Draw();
	}
}

void StraightEnemy::DeadPerformance()
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

void StraightEnemy::Attack()
{
	if (++shotIntervalTimer_ >= shotIntervalTime_) {
		const float bulletSpeed = 0.01f;
		XMVECTOR velocity = { 0, 0, 1 };

		velocity = XMVector3TransformNormal(velocity, enemy_->GetMatWorld());

		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(enemy_->GetMatWorld().r[3], velocity);

		bulletManager_->AddEnemyBullet(std::move(newBullet));
		shotIntervalTimer_ = 0;
	}
}
