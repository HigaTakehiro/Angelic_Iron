#include "BaseEnemy.h"

const float BaseEnemy::targetReactionTime = 60.0f;

void BaseEnemy::OnCollision()
{
	if (!isDamage_) {
		hp_--;
		isDamage_ = true;
	}
}

void BaseEnemy::BombHitCollision()
{
	hp_ = 0;
	isDamage_ = true;
}

void BaseEnemy::Move() {
	Vector3 enemyPos = enemy_->GetPosition();

	if (movePoints_.size() >= 1) {
		nowTimer_++;
		elapsedTimer_ = nowTimer_ * 2;
		timeRate_ = elapsedTimer_ / maxTime_;
		if (timeRate_ >= 1.0f) {
			if (movedPoint_ < movePoints_.size() - 1) {
				movedPoint_++;
				timeRate_ = 0.0f;
				nowTimer_ = 0;
			}
			else {
				timeRate_ = 1.0f;
			}
		}

		if (movedPoint_ < movePoints_.size() - 1) {
			enemyPos = lerp(movePoints_[movedPoint_], movePoints_[movedPoint_ + 1], timeRate_);
		}
	}

	enemy_->SetPosition(enemyPos);
}

void BaseEnemy::Damage()
{
	//定数
	const DirectX::XMFLOAT4 damageColor = { 0.7f, 0.0f, 0.0f, 1.0f };
	const DirectX::XMFLOAT4 normalColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	//ダメージ処理
	if (isDamage_) {
		damageTimer_++;
		enemy_->SetColor(damageColor);
		//ダメージ処理時間が過ぎたら
		if (damageTimer_ >= damageTime) {
			isDamage_ = false;
			enemy_->SetColor(normalColor);
			damageTimer_ = 0;
		}
	}
}

void BaseEnemy::RockOnPerformance()
{
	if (isTarget_) {
		float spriteRot = 0.0f;
		const float maxSpriteRot = 360.0f;
		const DirectX::XMFLOAT3 reticleColor = { 0.8f, 0.4f, 0.4f };

		if (targetReactionTimer_ <= targetReactionTime) {
			targetReactionTimer_++;
		}
		DirectX::XMVECTOR raticle2D = { enemy_->GetMatWorld().r[3] }; //ワールド座標
		DirectX::XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
		raticle2D = XMVector3TransformCoord(raticle2D, matViewProjectionViewport); //スクリーン座標

		DirectX::XMFLOAT2 spritePos = { raticle2D.m128_f32[0], raticle2D.m128_f32[1] };
		spriteRot = Easing::easeOutBack(targetReactionTimer_, targetReactionTime, maxSpriteRot, spriteRot, 1.0f);

		target_->SetPosition(spritePos);
		target_->SetRotation(spriteRot);
		target_->SetColor(reticleColor);
	}
	else {
		targetReactionTimer_ = 0.0f;
	}
}
