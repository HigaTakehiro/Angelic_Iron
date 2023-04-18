#include "SceneManager.h"
#include "SceneChangeEffect.h"
#include "Reticle.h"

BaseScene* SceneManager::nowScene = nullptr;
int32_t SceneManager::stageNo = 1;
int32_t SceneManager::score = 0;
bool SceneManager::isBossScene = false;

void SceneManager::Initialize() {
	//�}�E�X�J�[�\�����\���ɂ���
	ShowCursor(false);
	//DirectWrite������
	textDraw = std::make_unique<TextDraw>();
	textDraw->Initialize();
	//���e�B�N��������
	Reticle::GetIns()->Initialize();
	//�V�[���؂�ւ����o������
	SceneChangeEffect::GetIns()->Initialize();
	//�V�[���؂�ւ�
	SceneChange(Title);
}

void SceneManager::Update() {
	nowScene->Update();
}

void SceneManager::Draw() {
	nowScene->Draw();
}

void SceneManager::Finalize() {
	//���݂̃V�[���̏I������
	nowScene->Finalize();
	//���e�B�N�����
	Reticle::GetIns()->Finalize();
	//�V�[���؂�ւ����o�I������
	SceneChangeEffect::GetIns()->Finalize();
	//�x�[�X�V�[�����
	safe_delete(nowScene);
	//�J�[�\������
	ShowCursor(true);
}

void SceneManager::AddScore(const int32_t score) {
	SceneManager::score += score;
}

void SceneManager::SetScore(const int32_t score)
{
	SceneManager::score = score;
}

void SceneManager::SceneChange(SceneName scene) {
	if (nowScene != nullptr) {
		nowScene->Finalize();
		safe_delete(nowScene);
	}

	switch (scene) {
	case Title:
		nowScene = new TitleScene();
		nowScene->Initialize();
		break;

	case Stage1_Rail:
		stageNo = 1;
		score = 0;
		nowScene = new RailScene();
		nowScene->Initialize();
		break;
	case Stage1_Boss:
		nowScene = new BossScene();
		nowScene->Initialize();
		break;
	case Stage2_Rail:
		stageNo = 2;
		score = 0;
		nowScene = new RailScene();
		nowScene->Initialize();
		break;
	case Stage2_Boss:
		nowScene = new BossScene();
		nowScene->Initialize();
		break;
	case Result:
		nowScene = new ResultScene();
		nowScene->Initialize();
		break;
	case GameOver:
		nowScene = new GameOverScene();
		nowScene->Initialize();
		break;
	default:
		break;
	}
}