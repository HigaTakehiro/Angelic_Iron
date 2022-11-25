#include "SceneManager.h"

BaseScene* SceneManager::nowScene = nullptr;
DirectXCommon* SceneManager::dxCommon = nullptr;
Sound* SceneManager::sound = nullptr;
int SceneManager::nextScene = Game;

void SceneManager::Initialize(DirectXCommon* dxCommon, Sound* sound) {
	this->dxCommon = dxCommon;
	this->sound = sound;
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
		nowScene->Initialize(dxCommon, sound);
		break;

	case Game:
		nowScene = new GameScene();
		nowScene->Initialize(dxCommon, sound);
		break;

	case Result:
		nowScene = new ResultScene();
		nowScene->Initialize(dxCommon, sound);
		break;
	default:
		break;
	}
}