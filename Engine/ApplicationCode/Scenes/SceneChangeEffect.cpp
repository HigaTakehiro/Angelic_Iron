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
	//�V�[���؂�ւ��X�v���C�g�������W
	const float sceneChangeEffectInitPosX = 1280.0;
	//�V�[���؂�ւ��X�v���C�gX���W���炵
	const float sceneChangeShiftX = 100.0f;
	//�V�[���؂�ւ��X�v���C�gY���W���炵
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
	//�V�[���؂�ւ����o
	if (isSceneChangeStart && !isSceneChangeComplete) {
		SceneChangePerformance();
	}
	//�V�[���؂�ւ��������o
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
	//�C�[�W���O�ڕW���W
	const float targetPosX = -150.0f;

	//�V�[���؂�ւ��J�n�t���O�������Ă���V�[���؂�ւ��t���O�������Ă��Ȃ����
	if (isSceneChangeStart && !isSceneChange) {
		sceneChangeTimer++;
	}
	//�V�[���؂�ւ��^�C�}�[���V�[���؂�ւ����Ԉȏ�ɂȂ��
	if (sceneChangeTimer >= sceneChangeTime) {
		//�V�[���؂�ւ��t���O�𗧂Ă�
		isSceneChange = true;
		sceneChangeTimer = 0;
	}
	//�X�v���C�g���W���X�V����
	for (int i = 0; i < 10; i++) {
		sceneChangeEffectsPos[i].x = Easing::easeIn((float)sceneChangeTimer, (float)sceneChangeTime, targetPosX, sceneChangeEffectsPos[i].x);
		sceneChangeEffects[i]->SetPosition(sceneChangeEffectsPos[i]);
	}
}

void SceneChangeEffect::SceneChangeCompletePerformance()
{
	//�V�[���؂�ւ��t���O��false�ɂ���
	isSceneChange = false;
	//�C�[�W���O�ڕW���W
	const float sceneChangeInitPosX = 1280.0f;
	//�V�[���؂�ւ��X�v���C�gX���W���炵
	const float sceneChangeShiftX = 100.0f;

	//�V�[���؂�ւ������t���O�������Ă����
	if (isSceneChangeComplete) {
		sceneChangeTimer++;
	}
	//�V�[���؂�ւ��^�C�}�[���V�[���؂�ւ����Ԉȏ�ɂȂ��
	if (sceneChangeTimer >= sceneChangeTime) {
		//�e�t���O��false�ɂ���
		isSceneChangeComplete = false;
		isSceneChangeStart = false;
		sceneChangeTimer = 0;
	}
	//�X�v���C�g���W���X�V����
	for (int i = 0; i < 10; i++) {
		sceneChangeEffectsPos[i].x = Easing::easeOut((float)sceneChangeTimer,
			(float)sceneChangeTime, sceneChangeInitPosX + (sceneChangeShiftX * i),
			sceneChangeEffectsPos[i].x
		);
		sceneChangeEffects[i]->SetPosition(sceneChangeEffectsPos[i]);
	}
}
