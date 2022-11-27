#include "ResultScene.h"

void ResultScene::Initialize()
{
	clear = Sprite::Create(ImageManager::ImageName::clear, { 0, 0 });

	//PostEffectの初期化
	postEffect = new PostEffect();
	postEffect->Initialize();
}

void ResultScene::Update()
{
	if (KeyInput::GetIns()->TriggerKey(DIK_SPACE) || MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
		SceneManager::SceneChange(SceneManager::Title);
	}
}

void ResultScene::Draw()
{
	//背景色
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };
	static int postEffectNo = 0;

	postEffect->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//スプライト描画処理(背景)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	//background->Draw();
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());

	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	clear->Draw();

	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect->Draw(DirectXSetting::GetIns()->GetCmdList(), postEffectNo);
	DirectXSetting::GetIns()->PostDraw();
}

void ResultScene::Finalize()
{
	safe_delete(postEffect);
	safe_delete(clear);
}
