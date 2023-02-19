#include "SceneManager.h"
#include "SceneChangeEffect.h"

BaseScene* SceneManager::nowScene = nullptr;
int SceneManager::stageNo = 1;
int SceneManager::score = 0;

void SceneManager::Initialize() {
	//�}�E�X�J�[�\�����\���ɂ���
	ShowCursor(false);
	SceneChangeEffect::GetIns()->Initialize();
	SceneChange(Title);
}

void SceneManager::Update() {
	nowScene->Update();
}

void SceneManager::Draw() {
	nowScene->Draw();
}

void SceneManager::Finalize() {
	nowScene->Finalize();
	SceneChangeEffect::GetIns()->Finalize();
	safe_delete(nowScene);
	ShowCursor(true);
}

void SceneManager::AddScore(const int score) {
	SceneManager::score += score;
}

void SceneManager::SetScore(const int score)
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