#include "GameOverScene.h"

void GameOverScene::Initialize()
{
	gameover = Sprite::Create(ImageManager::ImageName::score, { 0, 0 });

	//PostEffect‚Ì‰Šú‰»
	postEffect = new PostEffect();
	postEffect->Initialize();
	postEffectNo = PostEffect::NONE;
}

void GameOverScene::Update()
{
	if (KeyInput::GetIns()->TriggerKey(DIK_SPACE) || MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
		SceneManager::SceneChange(SceneManager::Title);
	}
}

void GameOverScene::Draw()
{
	//”wŒiF
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };

	postEffect->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//ƒXƒvƒ‰ƒCƒg•`‰æˆ—(”wŒi)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	//background->Draw();
	Sprite::PostDraw();

	//3DƒIƒuƒWƒFƒNƒg•`‰æˆ—
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());

	Object3d::PostDraw();

	//ƒXƒvƒ‰ƒCƒg•`‰æˆ—(UI“™)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	gameover->Draw();

	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect->Draw(DirectXSetting::GetIns()->GetCmdList(), postEffectNo);
	DirectXSetting::GetIns()->PostDraw();
}

void GameOverScene::Finalize()
{
	safe_delete(postEffect);
	safe_delete(gameover);
}
