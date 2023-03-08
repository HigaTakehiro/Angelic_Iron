#include "BaseEnemy.h"

const float BaseEnemy::targetReactionTime = 60.0f;

void BaseEnemy::OnCollision()
{
	hp--;
}

void BaseEnemy::Move() {
	Vector3 enemyPos = enemy->GetPosition();

	if (movePoints.size() >= 1) {
		nowTimer++;
		elapsedTimer = nowTimer * 2;
		timeRate = elapsedTimer / maxTime;
		if (timeRate >= 1.0f) {
			if (movedPoint < movePoints.size() - 1) {
				movedPoint++;
				timeRate = 0.0f;
				nowTimer = 0;
			}
			else {
				timeRate = 1.0f;
			}
		}

		if (movedPoint < movePoints.size() - 1) {
			enemyPos = lerp(movePoints[movedPoint], movePoints[movedPoint + 1], timeRate);
		}
	}

	enemy->SetPosition(enemyPos);
}

void BaseEnemy::RockOnPerformance()
{
	if (isTarget) {
		float spriteRot = 0.0f;
		const float maxSpriteRot = 360.0f;
		const DirectX::XMFLOAT3 reticleColor = { 0.8f, 0.4f, 0.4f };

		if (targetReactionTimer <= targetReactionTime) {
			targetReactionTimer++;
		}
		DirectX::XMVECTOR raticle2D = { enemy->GetMatWorld().r[3] }; //ワールド座標
		DirectX::XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
		raticle2D = XMVector3TransformCoord(raticle2D, matViewProjectionViewport); //スクリーン座標

		DirectX::XMFLOAT2 spritePos = { raticle2D.m128_f32[0], raticle2D.m128_f32[1] };
		spriteRot = Easing::easeOutBack(targetReactionTimer, targetReactionTime, maxSpriteRot, spriteRot, 1.0f);

		target->SetPosition(spritePos);
		target->SetRotation(spriteRot);
		target->SetColor(reticleColor);
	}
	else {
		targetReactionTimer = 0.0f;
	}
}
