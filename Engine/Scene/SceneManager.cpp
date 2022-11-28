#include "SceneManager.h"

BaseScene* SceneManager::nowScene = nullptr;
int SceneManager::stageNo = 1;

void SceneManager::Initialize() {
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
	safe_delete(nowScene);
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
		nowScene = new GameScene();
		nowScene->Initialize();
		break;

	case Stage1_Boss:
		nowScene = new GameScene();
		nowScene->Initialize();
		break;
	case Stage2_Rail:
		stageNo = 2;
		nowScene = new GameScene();
		nowScene->Initialize();
		break;
	case Stage2_Boss:
		nowScene = new GameScene();
		nowScene->Initialize();
		break;
	case Result:
		nowScene = new ResultScene();
		nowScene->Initialize();
		break;
	case GameOver:
		nowScene = new GameOverScene();
		nowScene->Initialize();
	default:
		break;
	}
}