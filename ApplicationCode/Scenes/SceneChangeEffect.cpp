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
	//�V�[���؂�ւ��X�v���C�g�������W
	const float sceneChangeEffectInitPosX = 1280.0;
	//�V�[���؂�ւ��X�v���C�gX���W���炵
	const float sceneChangeShiftX = 100.0f;
	//�V�[���؂�ւ��X�v���C�gY���W���炵
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
	//�V�[���؂�ւ����o
	if (isSceneChangeStart_ && !isSceneChangeComplete_) {
		SceneChangePerformance();
	}
	//�V�[���؂�ւ��������o
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
	//�C�[�W���O�ڕW���W
	const float targetPosX = -150.0f;

	//�V�[���؂�ւ��J�n�t���O�������Ă���V�[���؂�ւ��t���O�������Ă��Ȃ����
	if (isSceneChangeStart_ && !isSceneChange_) {
		sceneChangeTimer_++;
	}
	//�V�[���؂�ւ��^�C�}�[���V�[���؂�ւ����Ԉȏ�ɂȂ��
	if (sceneChangeTimer_ >= sceneChangeTime_) {
		//�V�[���؂�ւ��t���O�𗧂Ă�
		isSceneChange_ = true;
		sceneChangeTimer_ = 0;
	}
	//�X�v���C�g���W���X�V����
	for (int32_t i = 0; i < 10; i++) {
		sceneChangeEffectsPos_[i].x = Easing::easeIn((float)sceneChangeTimer_, (float)sceneChangeTime_, targetPosX, sceneChangeEffectsPos_[i].x);
		sceneChangeEffects_[i]->SetPosition(sceneChangeEffectsPos_[i]);
	}
}

void SceneChangeEffect::SceneChangeCompletePerformance()
{
	//�V�[���؂�ւ��t���O��false�ɂ���
	isSceneChange_ = false;
	//�C�[�W���O�ڕW���W
	const float sceneChangeInitPosX = 1280.0f;
	//�V�[���؂�ւ��X�v���C�gX���W���炵
	const float sceneChangeShiftX = 100.0f;

	//�V�[���؂�ւ������t���O�������Ă����
	if (isSceneChangeComplete_) {
		sceneChangeTimer_++;
	}
	//�V�[���؂�ւ��^�C�}�[���V�[���؂�ւ����Ԉȏ�ɂȂ��
	if (sceneChangeTimer_ >= sceneChangeTime_) {
		//�e�t���O��false�ɂ���
		isSceneChangeComplete_ = false;
		isSceneChangeStart_ = false;
		sceneChangeTimer_ = 0;
	}
	//�X�v���C�g���W���X�V����
	for (int32_t i = 0; i < 10; i++) {
		sceneChangeEffectsPos_[i].x = Easing::easeOut((float)sceneChangeTimer_,
			(float)sceneChangeTime_, sceneChangeInitPosX + (sceneChangeShiftX * i),
			sceneChangeEffectsPos_[i].x
		);
		sceneChangeEffects_[i]->SetPosition(sceneChangeEffectsPos_[i]);
	}
}
