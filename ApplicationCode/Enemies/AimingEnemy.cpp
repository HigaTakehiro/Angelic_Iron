#include "AimingEnemy.h"

AimingEnemy::~AimingEnemy()
{
	safe_delete(enemy_);
	safe_delete(target_);
}

void AimingEnemy::Initialize(const std::string modelKey, const Vector3& pos, const Vector3& rot)
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

void AimingEnemy::Update()
{
	//RockOnPerformance();

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

void AimingEnemy::Draw()
{
	enemy_->Draw();
}

void AimingEnemy::SpriteDraw()
{
	if (isTarget_) {
		target_->Draw();
	}
}

void AimingEnemy::DeadPerformance() {
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
		isDead_ = true;
	}
}

void AimingEnemy::Attack()
{
	if (++shotIntervalTimer_ >= shotIntervalTime_) {
		const float bulletSpeed = 2.0f;
		Vector3 playerWPos = player_->GetPlayerObject()->GetMatWorld().r[3];
		Vector3 enemyWPos = enemy_->GetMatWorld().r[3];
		XMVECTOR velocity = { 0, 0, 1 };
		XMVECTOR vector = { playerWPos.x - enemyWPos.x, playerWPos.y - enemyWPos.y, playerWPos.z - enemyWPos.z };
		vector = XMVector3Normalize(vector);
		velocity = vector * bulletSpeed;

		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(enemy_->GetMatWorld().r[3], velocity);

		railScene_->AddEnemyBullet(std::move(newBullet));
		shotIntervalTimer_ = 0;
	}
}