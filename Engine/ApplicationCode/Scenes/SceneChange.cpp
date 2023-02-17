#include "SceneChange.h"
#include "Easing.h"
#include "SafeDelete.h"

const int32_t SceneChange::sceneChangeTime = 60;
int32_t SceneChange::sceneChangeTimer = 0;
bool SceneChange::isSceneChangeStart = false;
bool SceneChange::isSceneChange = false;
bool SceneChange::isSceneChangeComplete = false;
Sprite* SceneChange::sceneChangeEffects[] = {};
DirectX::XMFLOAT2 SceneChange::sceneChangeEffectsPos[] = {};

SceneChange* SceneChange::GetIns()
{
	SceneChange instance;
	return &instance;
}

void SceneChange::Initialize()
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

void SceneChange::Update()
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

void SceneChange::Draw()
{
	for (int i = 0; i < 10; i++) {
		sceneChangeEffects[i]->Draw();
	}
}

void SceneChange::Finalize()
{
	for (int i = 0; i < 10; i++) {
		safe_delete(sceneChangeEffects[i]);
	}
}

void SceneChange::SceneChangePerformance()
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

void SceneChange::SceneChangeCompletePerformance()
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
