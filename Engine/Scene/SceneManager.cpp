#include "SceneManager.h"

BaseScene* SceneManager::nowScene = nullptr;
int SceneManager::nextScene = Game;

void SceneManager::Initialize() {
	nextScene = Game;
	SceneChange(Title);
}

void SceneManager::Update() {
	nowScene->Update();
	if (KeyInput::GetIns()->TriggerKey(DIK_N)) {
		nextScene = (nextScene + 1) % 3;
		SceneChange((SceneName)nextScene);
	}
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
		//nowScene->Finalize();
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
	default:
		break;
	}
}