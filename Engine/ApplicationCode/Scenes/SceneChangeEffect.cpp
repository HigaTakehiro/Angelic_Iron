#include "SceneChangeEffect.h"
#include "Easing.h"
#include "SafeDelete.h"

const int32_t SceneChangeEffect::sceneChangeTime = 60;
int32_t SceneChangeEffect::sceneChangeTimer = 0;
bool SceneChangeEffect::isSceneChangeStart = false;
bool SceneChangeEffect::isSceneChange = false;
bool SceneChangeEffect::isSceneChangeComplete = false;
Sprite* SceneChangeEffect::sceneChangeEffects[] = {};
DirectX::XMFLOAT2 SceneChangeEffect::sceneChangeEffectsPos[] = {};

SceneChangeEffect* SceneChangeEffect::GetIns()
{
	static SceneChangeEffect instance;
	return &instance;
}

void SceneChangeEffect::Initialize()
{
	//シーン切り替えスプライト初期座標
	const float sceneChangeEffectInitPosX = 1280.0;
	//シーン切り替えスプライトX座標ずらし
	const float sceneChangeShiftX = 100.0f;
	//シーン切り替えスプライトY座標ずらし
	const float sceneChangeShiftY = 72.0f;

	for (int i = 0; i < 10; i++) {
		if (sceneChangeEffectsPos[i].x == 0.0f) {
			sceneChangeEffectsPos[i].x = sceneChangeEffectInitPosX + sceneChangeShiftX * i;
			sceneChangeEffectsPos[i].y = sceneChangeShiftY * i;
			sceneChangeEffects[i] = Sprite::Create(ImageManager::SceneChangeBar, sceneChangeEffectsPos[i]);
		}
	}
}

void SceneChangeEffect::Update()
{
	//シーン切り替え演出
	if (isSceneChangeStart && !isSceneChangeComplete) {
		SceneChangePerformance();
	}
	//シーン切り替え完了演出
	if (isSceneChangeComplete) {
		SceneChangeCompletePerformance();
	}
}

void SceneChangeEffect::Draw()
{
	for (int i = 0; i < 10; i++) {
		sceneChangeEffects[i]->Draw();
	}
}

void SceneChangeEffect::Finalize()
{
	for (int i = 0; i < 10; i++) {
		safe_delete(sceneChangeEffects[i]);
	}
}

void SceneChangeEffect::SceneChangePerformance()
{
	//イージング目標座標
	const float targetPosX = -150.0f;

	//シーン切り替え開始フラグが立っておりシーン切り替えフラグが立っていなければ
	if (isSceneChangeStart && !isSceneChange) {
		sceneChangeTimer++;
	}
	//シーン切り替えタイマーがシーン切り替え時間以上になれば
	if (sceneChangeTimer >= sceneChangeTime) {
		//シーン切り替えフラグを立てる
		isSceneChange = true;
		sceneChangeTimer = 0;
	}
	//スプライト座標を更新する
	for (int i = 0; i < 10; i++) {
		sceneChangeEffectsPos[i].x = Easing::easeIn((float)sceneChangeTimer, (float)sceneChangeTime, targetPosX, sceneChangeEffectsPos[i].x);
		sceneChangeEffects[i]->SetPosition(sceneChangeEffectsPos[i]);
	}
}

void SceneChangeEffect::SceneChangeCompletePerformance()
{
	//シーン切り替えフラグをfalseにする
	isSceneChange = false;
	//イージング目標座標
	const float sceneChangeInitPosX = 1280.0f;
	//シーン切り替えスプライトX座標ずらし
	const float sceneChangeShiftX = 100.0f;

	//シーン切り替え完了フラグが立っていれば
	if (isSceneChangeComplete) {
		sceneChangeTimer++;
	}
	//シーン切り替えタイマーがシーン切り替え時間以上になれば
	if (sceneChangeTimer >= sceneChangeTime) {
		//各フラグをfalseにする
		isSceneChangeComplete = false;
		isSceneChangeStart = false;
		sceneChangeTimer = 0;
	}
	//スプライト座標を更新する
	for (int i = 0; i < 10; i++) {
		sceneChangeEffectsPos[i].x = Easing::easeOut((float)sceneChangeTimer,
			(float)sceneChangeTime, sceneChangeInitPosX + (sceneChangeShiftX * i),
			sceneChangeEffectsPos[i].x
		);
		sceneChangeEffects[i]->SetPosition(sceneChangeEffectsPos[i]);
	}
}
