#include "BaseEnemy.h"

const float BaseEnemy::targetReactionTime = 60.0f;

void BaseEnemy::OnCollision()
{
	hp--;
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
		DirectX::XMVECTOR raticle2D = { enemy->GetMatWorld().r[3] }; //���[���h���W
		DirectX::XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //�r���[�v���W�F�N�V�����r���[�|�[�g�s��
		raticle2D = XMVector3TransformCoord(raticle2D, matViewProjectionViewport); //�X�N���[�����W

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
