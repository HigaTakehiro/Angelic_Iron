#include "BaseScene.h"

bool BaseScene::IsMouseHitSprite(DirectX::XMFLOAT2 mousePos, DirectX::XMFLOAT2 spritePos, float spriteWidth, float spriteHeight)
{
	float spriteSizeX = spriteWidth / 2.0f;
	float spriteSizeY = spriteHeight / 2.0f;

	DirectX::XMFLOAT2 spriteUpperLeft = { spritePos.x - spriteSizeX, spritePos.y - spriteSizeY };
	DirectX::XMFLOAT2 spriteLowerRight = { spritePos.x + spriteSizeX, spritePos.y + spriteSizeY };

	return spriteUpperLeft.x <= mousePos.x && spriteLowerRight.x >= mousePos.x && spriteUpperLeft.y <= mousePos.y && spriteLowerRight.y >= mousePos.y;
}

BaseScene::ScoreNumber BaseScene::JudgeDigitNumber(int32_t score, int32_t digit)
{
	if (score >= 1000000) {
		return nine;
	}

	int32_t num = (score / (int32_t)pow(10, digit)) % 10;

	return (ScoreNumber)(64 * num);
}