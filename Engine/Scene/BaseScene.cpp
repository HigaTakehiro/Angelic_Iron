#include "BaseScene.h"

int32_t BaseScene::sceneChangeTime = 60;
int32_t BaseScene::sceneChangeTimer = 0;
bool BaseScene::isSceneChangeStart = false;
bool BaseScene::isSceneChange = false;
bool BaseScene::isSceneChangeComplete = false;
Sprite* BaseScene::sceneChangeEffects[] = {};
XMFLOAT2 BaseScene::sceneChangeEffectsPos[] = {};

void BaseScene::SceneChangeInitialize()
{
	const float sceneChangeEffectInitPosX = 1280.0;
	const float sceneChangeShiftX = 100.0f;
	const float sceneChangeShiftY = 72.0f;

	for (int i = 0; i < 10; i++) {
		if (sceneChangeEffectsPos[i].x == 0.0f) {
			sceneChangeEffectsPos[i].x = sceneChangeEffectInitPosX + sceneChangeShiftX * i;
			sceneChangeEffectsPos[i].y = sceneChangeShiftY * i;
			sceneChangeEffects[i] = Sprite::Create(ImageManager::SceneChangeBar, sceneChangeEffectsPos[i]);
			isSceneChangeComplete = false;
		}
	}

	isSceneChangeStart = false;
	isSceneChange = false;
}

bool BaseScene::IsMouseHitSprite(DirectX::XMFLOAT2 mousePos, DirectX::XMFLOAT2 spritePos, float spriteWidth, float spriteHeight)
{
	float spriteSizeX = spriteWidth / 2.0f;
	float spriteSizeY = spriteHeight / 2.0f;

	DirectX::XMFLOAT2 spriteUpperLeft = { spritePos.x - spriteSizeX, spritePos.y - spriteSizeY };
	DirectX::XMFLOAT2 spriteLowerRight = { spritePos.x + spriteSizeX, spritePos.y + spriteSizeY };

	return spriteUpperLeft.x <= mousePos.x && spriteLowerRight.x >= mousePos.x && spriteUpperLeft.y <= mousePos.y && spriteLowerRight.y >= mousePos.y;
}

BaseScene::ScoreNumber BaseScene::JudgeDigitNumber(int score, int digit)
{
	if (score >= 1000000) {
		return nine;
	}

	int num = (score / (int)pow(10, digit)) % 10;

	return (ScoreNumber)(64 * num);
}

void BaseScene::SceneChangeEffect()
{
	const float targetPosX = -150.0f;

	if (isSceneChangeStart && !isSceneChange) {
		sceneChangeTimer++;
	}

	if (sceneChangeTimer >= sceneChangeTime) {
		isSceneChange = true;
		sceneChangeTimer = 0;
	}

	for (int i = 0; i < 10; i++) {
		sceneChangeEffectsPos[i].x = Easing::GetIns()->easeIn(sceneChangeTimer, sceneChangeTime, targetPosX, sceneChangeEffectsPos[i].x);
		sceneChangeEffects[i]->SetPosition(sceneChangeEffectsPos[i]);
	}
}

void BaseScene::SceneChangeCompleteEffect()
{
	const float sceneChangeInitPosX = 1280.0f;
	const float sceneChangeShiftX = 100.0f;

	if (isSceneChangeComplete) {
		sceneChangeTimer++;
	}

	if (sceneChangeTimer >= sceneChangeTime) {
		isSceneChange = false;
		isSceneChangeComplete = false;
		isSceneChangeStart = false;
		sceneChangeTimer = 0;
	}

	for (int i = 0; i < 10; i++) {
		sceneChangeEffectsPos[i].x = Easing::GetIns()->easeOut(sceneChangeTimer,
			sceneChangeTime, sceneChangeInitPosX + (sceneChangeShiftX * i),
			sceneChangeEffectsPos[i].x
		);
		sceneChangeEffects[i]->SetPosition(sceneChangeEffectsPos[i]);
	}
}

void BaseScene::SceneChangeEffectDraw()
{
	for (int i = 0; i < 10; i++) {
		sceneChangeEffects[i]->Draw();
	}
}

void BaseScene::SceneChangeFinalize()
{
	for (int i = 0; i < 10; i++) {
		safe_delete(sceneChangeEffects[i]);
	}
}
