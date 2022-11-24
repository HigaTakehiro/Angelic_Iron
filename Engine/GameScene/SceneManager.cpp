#include "SceneManager.h"

void SceneManager::Initialize() {

}

void SceneManager::Update() {

}

void SceneManager::Draw() {

}

void SceneManager::Finalize() {
	if (nowSceneNo == Title) {

	}
	else if (nowSceneNo == Stage1_Rail) {

	}
	else if (nowSceneNo == Stage1_Boss) {

	}
}

void SceneManager::SceneChange(SceneName sceneName) {
	nextSceneNo = sceneName;
}