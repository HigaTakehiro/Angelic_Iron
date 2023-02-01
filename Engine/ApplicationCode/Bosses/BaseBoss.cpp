#include "BaseBoss.h"

using namespace DirectX;

const int32_t BaseBoss::damageTime = 20;
const XMFLOAT4 BaseBoss::damageColor = { 1.0f, 0.3f, 0.3f, 1.0f };
const int BaseBoss::deadHP = 0;

void BaseBoss::OnCollision()
{
	hp--;
	isDamage = true;
}

void BaseBoss::DamageReaction()
{
	if (isDamage) {
		damageTimer++;
		boss->SetColor({ 1.0f, 0.3f, 0.3f, 1.0f });
	}

	if (damageTimer >= damageTime) {
		isDamage = false;
		damageTimer = 0;
		boss->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	}
}
