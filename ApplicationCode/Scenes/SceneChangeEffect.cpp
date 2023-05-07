#include "SceneChangeEffect.h"
#include "Easing.h"
#include "SafeDelete.h"

const int32_t SceneChangeEffect::sceneChangeTime_ = 60;
int32_t SceneChangeEffect::sceneChangeTimer_ = 0;
bool SceneChangeEffect::isSceneChangeStart_ = false;
bool SceneChangeEffect::isSceneChange_ = false;
bool SceneChangeEffect::isSceneChangeComplete_ = false;
Sprite* SceneChangeEffect::sceneChangeEffects_[] = {};
DirectX::XMFLOAT2 SceneChangeEffect::sceneChangeEffectsPos_[] = {};

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

	for (int32_t i = 0; i < 10; i++) {
		if (sceneChangeEffectsPos_[i].x == 0.0f) {
			sceneChangeEffectsPos_[i].x = sceneChangeEffectInitPosX + sceneChangeShiftX * i;
			sceneChangeEffectsPos_[i].y = sceneChangeShiftY * i;
			sceneChangeEffects_[i] = Sprite::Create(ImageManager::SceneChangeBar, sceneChangeEffectsPos_[i]);
		}
	}
}

void SceneChangeEffect::Update()
{
	//シーン切り替え演出
	if (isSceneChangeStart_ && !isSceneChangeComplete_) {
		SceneChangePerformance();
	}
	//シーン切り替え完了演出
	if (isSceneChangeComplete_) {
		SceneChangeCompletePerformance();
	}
}

void SceneChangeEffect::Draw()
{
	for (int32_t i = 0; i < 10; i++) {
		sceneChangeEffects_[i]->Draw();
	}
}

void SceneChangeEffect::Finalize()
{
	for (int32_t i = 0; i < 10; i++) {
		safe_delete(sceneChangeEffects_[i]);
	}
}

void SceneChangeEffect::SceneChangePerformance()
{
	//イージング目標座標
	const float targetPosX = -150.0f;

	//シーン切り替え開始フラグが立っておりシーン切り替えフラグが立っていなければ
	if (isSceneChangeStart_ && !isSceneChange_) {
		sceneChangeTimer_++;
	}
	//シーン切り替えタイマーがシーン切り替え時間以上になれば
	if (sceneChangeTimer_ >= sceneChangeTime_) {
		//シーン切り替えフラグを立てる
		isSceneChange_ = true;
		sceneChangeTimer_ = 0;
	}
	//スプライト座標を更新する
	for (int32_t i = 0; i < 10; i++) {
		sceneChangeEffectsPos_[i].x = Easing::easeIn((float)sceneChangeTimer_, (float)sceneChangeTime_, targetPosX, sceneChangeEffectsPos_[i].x);
		sceneChangeEffects_[i]->SetPosition(sceneChangeEffectsPos_[i]);
	}
}

void SceneChangeEffect::SceneChangeCompletePerformance()
{
	//シーン切り替えフラグをfalseにする
	isSceneChange_ = false;
	//イージング目標座標
	const float sceneChangeInitPosX = 1280.0f;
	//シーン切り替えスプライトX座標ずらし
	const float sceneChangeShiftX = 100.0f;

	//シーン切り替え完了フラグが立っていれば
	if (isSceneChangeComplete_) {
		sceneChangeTimer_++;
	}
	//シーン切り替えタイマーがシーン切り替え時間以上になれば
	if (sceneChangeTimer_ >= sceneChangeTime_) {
		//各フラグをfalseにする
		isSceneChangeComplete_ = false;
		isSceneChangeStart_ = false;
		sceneChangeTimer_ = 0;
	}
	//スプライト座標を更新する
	for (int32_t i = 0; i < 10; i++) {
		sceneChangeEffectsPos_[i].x = Easing::easeOut((float)sceneChangeTimer_,
			(float)sceneChangeTime_, sceneChangeInitPosX + (sceneChangeShiftX * i),
			sceneChangeEffectsPos_[i].x
		);
		sceneChangeEffects_[i]->SetPosition(sceneChangeEffectsPos_[i]);
	}
}
