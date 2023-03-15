#include "StraightEnemy.h"

StraightEnemy::~StraightEnemy() {
	safe_delete(enemy);
	safe_delete(target);
}

void StraightEnemy::Initialize(const std::string modelKey, const Vector3& pos, const Vector3& rot) {
	enemy = Object3d::Create(ModelManager::GetIns()->GetModel(modelKey));
	enemy->SetPosition(pos);
	target = Sprite::Create(ImageManager::ImageName::aim, { 0, 0 });
	target->SetSize(XMFLOAT2(100.0f, 100.0f));
	target->SetAnchorPoint({ 0.5f, 0.5f });
	oldPos = pos;
	enemy->SetRotation(rot);
	enemy->SetScale(scale);
	hp = 1;
	shotIntervalTime = 60;
	shotIntervalTimer = 0;
	lifeTime = 240;
	lifeTimer = 0;
	targetReactionTimer = 0;
}

void StraightEnemy::Update()
{
	const int32_t lifeTimeOver = 0;
	//RockOnPerformance();

	if (hp <= 0) {
		DeadPerformance();
	}
	if (++lifeTimer >= lifeTime) {
		isDead = true;
	}

	if (enemy != nullptr && hp > 0) {
		if (pos.x == 0 && pos.y == 0 && pos.z == 0) {
			pos = oldPos;
		}
		Move();
		Attack();
		Damage();
	}

	enemy->Update();
}

void StraightEnemy::Draw()
{
	enemy->Draw();
}

void StraightEnemy::SpriteDraw()
{
	if (isTarget) {
		target->Draw();
	}
}

void StraightEnemy::DeadPerformance()
{
	const float downSpeed = 0.5f;
	const float rotSpeed = 15.0f;
	XMFLOAT3 enemyPos = enemy->GetPosition();
	XMFLOAT3 enemyRot = enemy->GetRotation();
	deadTimer++;
	enemyPos.y -= downSpeed;
	enemyRot.y += rotSpeed;
	enemy->SetPosition(enemyPos);
	enemy->SetRotation(enemyRot);
	if (deadTimer >= deadTime) {
		isDead = true;
	}
}

void StraightEnemy::Attack()
{
	if (++shotIntervalTimer >= shotIntervalTime) {
		const float bulletSpeed = 0.001f;
		XMVECTOR velocity = { 0, 0, 1 };

		velocity = XMVector3TransformNormal(velocity, enemy->GetMatWorld());

		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(enemy->GetMatWorld().r[3], velocity);

		railScene->AddEnemyBullet(std::move(newBullet));
		shotIntervalTimer = 0;
	}
}
