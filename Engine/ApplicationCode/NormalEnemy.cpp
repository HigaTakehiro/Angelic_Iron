#include "NormalEnemy.h"

void NormalEnemy::Initialize(const ModelManager::ModelName modelName, const Vector3& pos, const Vector3& scale) {
	enemy = Object3d::Create(ModelManager::GetIns()->GetModel(modelName));
	enemy->SetPosition(pos);
	target = Sprite::Create(ImageManager::ImageName::aim, { 0, 0 });
	target->SetSize(XMFLOAT2(100.0f, 100.0f));
	target->SetAnchorPoint({ 0.5f, 0.5f });
	oldPos = pos;
	enemy->SetScale(scale);
	delayTimer = 0.0f;
	hp = 1;
	shotIntervalTime = 60;
	shotIntervalTimer = 0;
	lifeTime = 240;
	lifeTimer = 0;
	targetReactionTimer = 0;
}

void NormalEnemy::Update(const Vector3& playerPos, const int delayTime)
{
	const int32_t lifeTimeOver = 0;

	delayTimer++;

	if (hp <= 0 || ++lifeTimer >= lifeTime) {
		isDead = true;
	}

	if (isTarget) {
		int spriteRot = 0;
		const float maxSpriteRot = 360.0f;
		if (targetReactionTimer >= targetReactionTime) {
			targetReactionTimer++;
		}
		XMVECTOR raticle2D = { enemy->GetMatWorld().r[3] }; //���[���h���W
		XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //�r���[�v���W�F�N�V�����r���[�|�[�g�s��
		raticle2D = XMVector3TransformCoord(raticle2D, matViewProjectionViewport); //�X�N���[�����W

		DirectX::XMFLOAT2 spritePos = { raticle2D.m128_f32[0], raticle2D.m128_f32[1] };
		spriteRot = Easing::GetIns()->easeOutBack(targetReactionTimer, targetReactionTime, maxSpriteRot, spriteRot, 1);

		target->SetPosition(spritePos);
		target->SetRotation(spriteRot);
	}
	else {
		targetReactionTimer = 0;
	}

	if (delayTimer >= delayTime) {

		if (--lifeTimer <= lifeTimeOver) {
			isDead = true;
			lifeTimer = 0;
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

void NormalEnemy::Draw()
{
	enemy->Draw();
}

void NormalEnemy::SpriteDraw()
{
	target->Draw();
}

void NormalEnemy::Finalize()
{
	safe_delete(enemy);
	safe_delete(target);
}

void NormalEnemy::Move()
{
	Vector3 nowPos = { enemy->GetPosition().x, enemy->GetPosition().y, enemy->GetPosition().z };
	nowPos.y += 0.1f;
	enemy->SetPosition(nowPos);
}

void NormalEnemy::Attack()
{
	if (++shotIntervalTimer >= shotIntervalTime) {
		const float bulletSpeed = 0.001f;
		XMVECTOR velocity = { 0, 0, 1 };

		velocity = MatCalc::GetIns()->VecDivided(velocity, enemy->GetMatWorld());

		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(enemy->GetMatWorld().r[3], velocity);

		railScene->AddEnemyBullet(std::move(newBullet));
		shotIntervalTimer = shotIntervalTime;
	}
}