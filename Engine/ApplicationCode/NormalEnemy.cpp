#include "NormalEnemy.h"

StraightEnemy::~StraightEnemy() {
	safe_delete(enemy);
	safe_delete(target);
}

void StraightEnemy::Initialize(const ModelManager::ModelName modelName, const Vector3& pos, const Vector3& rot) {
	enemy = Object3d::Create(ModelManager::GetIns()->GetModel(modelName));
	enemy->SetPosition(pos);
	target = Sprite::Create(ImageManager::ImageName::aim, { 0, 0 });
	target->SetSize(XMFLOAT2(100.0f, 100.0f));
	target->SetAnchorPoint({ 0.5f, 0.5f });
	oldPos = pos;
	enemy->SetRotation(rot);
	enemy->SetScale(scale);
	delayTimer = 0.0f;
	hp = 1;
	shotIntervalTime = 60;
	shotIntervalTimer = 0;
	lifeTime = 240;
	lifeTimer = 0;
	targetReactionTimer = 0;
}

void StraightEnemy::Update(const int delayTime)
{
	const int32_t lifeTimeOver = 0;

	delayTimer++;

	if (isTarget) {
		int spriteRot = 0;
		const float maxSpriteRot = 360.0f;
		if (targetReactionTimer <= targetReactionTime) {
			targetReactionTimer++;
		}
		XMVECTOR raticle2D = { enemy->GetMatWorld().r[3] }; //ワールド座標
		XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
		raticle2D = XMVector3TransformCoord(raticle2D, matViewProjectionViewport); //スクリーン座標

		DirectX::XMFLOAT2 spritePos = { raticle2D.m128_f32[0], raticle2D.m128_f32[1] };
		spriteRot = Easing::GetIns()->easeOutBack(targetReactionTimer, targetReactionTime, maxSpriteRot, spriteRot, 1);

		target->SetPosition(spritePos);
		target->SetRotation(spriteRot);
	}
	else {
		targetReactionTimer = 0;
	}

	if (delayTimer >= delayTime) {

		if (hp <= 0 || ++lifeTimer >= lifeTime) {
			isDead = true;
		}

		if (enemy != nullptr) {
			if (pos.x == 0 && pos.y == 0 && pos.z == 0) {
				pos = oldPos;
			}
			Move();
			Attack();
		}

		enemy->Update();
		delayTimer = 0;
	}
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

void StraightEnemy::Move()
{
	Vector3 nowPos = { enemy->GetPosition().x, enemy->GetPosition().y, enemy->GetPosition().z };
	if (lifeTimer <= 180.0f) {
		nowPos.z += 0.01f;
	}
	else {
		nowPos.x -= 1.5f;
	}
	enemy->SetPosition(nowPos);
}

void StraightEnemy::Attack()
{
	if (++shotIntervalTimer >= shotIntervalTime) {
		const float bulletSpeed = 0.001f;
		XMVECTOR velocity = { 0, 0, 1 };

		velocity = MatCalc::GetIns()->VecDivided(velocity, enemy->GetMatWorld());

		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(enemy->GetMatWorld().r[3], velocity);

		railScene->AddEnemyBullet(std::move(newBullet));
		shotIntervalTimer = 0;
	}
}
