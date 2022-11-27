#include "SceneManager.h"

BaseScene* SceneManager::nowScene = nullptr;
int SceneManager::nextScene = Title;

void SceneManager::Initialize() {
	nextScene = Title;
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

	case Game:
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