#include "BossScene.h"

void BossScene::Initialize()
{

}

void BossScene::Update()
{
	if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
		SceneManager::SceneChange(SceneManager::Result);
	}
}

void BossScene::Draw()
{

}

void BossScene::Finalize()
{

}
