#include "BaseBoss.h"

using namespace DirectX;

const int32_t BaseBoss::damageTime = 20;
const XMFLOAT4 BaseBoss::damageColor = { 1.0f, 0.3f, 0.3f, 1.0f };
const int32_t BaseBoss::deadHP = 0;

void BaseBoss::OnCollision()
{
	hp_--;
	isDamage_ = true;
}

void BaseBoss::DamageReaction()
{
	if (isDamage_) {
		damageTimer_++;
		boss_->SetColor({ 1.0f, 0.3f, 0.3f, 1.0f });
	}

	if (damageTimer_ >= damageTime) {
		isDamage_ = false;
		damageTimer_ = 0;
		boss_->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	}
}
