#include "HomingEnemy.h"

HomingEnemy::~HomingEnemy()
{
	safe_delete(enemy);
	safe_delete(target);
}

void HomingEnemy::Initialize(const ModelManager::ModelName modelName, const Vector3& pos, const Vector3& rot)
{
	enemy = Object3d::Create(ModelManager::GetIns()->GetModel(modelName));
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

void HomingEnemy::Update()
{
	const int32_t lifeTimeOver = 0;

	RockOnPerformance();

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
	}

	enemy->Update();

}

void HomingEnemy::Draw()
{
	enemy->Draw();
}

void HomingEnemy::SpriteDraw()
{
	if (isTarget) {
		target->Draw();
	}
}

void HomingEnemy::DeadPerformance() {
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

void HomingEnemy::Move()
{
	XMFLOAT3 enemyPos = enemy->GetPosition();
	if (lifeTimer <= 180.0f) {
		enemyPos.z += 0.01f;
	}
	else {
		enemyPos.x += 1.5f;
	}
	enemy->SetPosition(enemyPos);
}

void HomingEnemy::Attack()
{
	if (++shotIntervalTimer >= shotIntervalTime) {
		const float bulletSpeed = 2.0f;
		Vector3 playerWPos = player->GetPlayerObject()->GetMatWorld().r[3];
		Vector3 enemyWPos = enemy->GetMatWorld().r[3];
		XMVECTOR velocity = { 0, 0, 1 };
		XMVECTOR vector = { playerWPos.x - enemyWPos.x, playerWPos.y - enemyWPos.y, playerWPos.z - enemyWPos.z };
		vector = XMVector3Normalize(vector);
		velocity = vector * bulletSpeed;

		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(enemy->GetMatWorld().r[3], velocity);

		railScene->AddEnemyBullet(std::move(newBullet));
		shotIntervalTimer = 0;
	}
}