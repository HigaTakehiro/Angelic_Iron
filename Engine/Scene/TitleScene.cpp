#include "TitleScene.h"

void TitleScene::Initialize()
{
	camera = new Camera;
	camera->SetEye(XMFLOAT3(-50, 0, 100));
	camera->SetTarget(XMFLOAT3(0, 1, 0));

	titlePos = { 0, 0 };
	startButtonPos = { 640, 550 };
	stage1Pos = { 200, 100 };
	stage2Pos = { 200, 300 };
	manualButtonPos = { 200, 500 };
	closePos = { 640, 550 };

	startButtonSize = initSize;
	stage1Size = initSize;
	stage2Size = initSize;
	manualButtonSize = initSize;
	manualSize = initSize;
	closeSize = initSize;

	title = Sprite::Create(ImageManager::ImageName::title, titlePos);
	startButton = Sprite::Create(ImageManager::ImageName::StartButton, startButtonPos);
	startButton->SetAnchorPoint({ 0.5f, 0.5f });
	stage1 = Sprite::Create(ImageManager::ImageName::Stage1, stage1Pos);
	stage2 = Sprite::Create(ImageManager::ImageName::Stage2, stage2Pos);
	manualButton = Sprite::Create(ImageManager::ImageName::ManualButton, manualButtonPos);
	manual = Sprite::Create(ImageManager::ImageName::Manual, { 640, 300 });
	manual->SetAnchorPoint({ 0.5f, 0.5f });
	close = Sprite::Create(ImageManager::ImageName::Close, closePos);
	close->SetAnchorPoint({ 0.5f, 0.5f });

	titlePlayer = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Player_Stand));
	playerScale = { 20, 20, 20 };
	playerPos = { -30, 0, 0 };
	playerRot = { 0, 0, 0 };
	titlePlayer->SetScale(playerScale);
	titlePlayer->SetPosition(playerPos);
	titlePlayer->SetRotation(playerRot);

	ground = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Ground));
	groundPos = { 0, -50, 0 };
	ground->SetPosition(groundPos);
	groundScale = { 10, 10, 10 };
	ground->SetScale(groundScale);

	postEffect = new PostEffect();
	postEffect->Initialize();
}

void TitleScene::Update()
{
	titlePlayer->Update();
	ground->Update();

	//シーン切り替え
	if (KeyInput::GetIns()->TriggerKey(DIK_SPACE) || MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
		SceneManager::SceneChange(SceneManager::Stage1_Rail);
	}
}

void TitleScene::Draw()
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
	titlePlayer->Draw();
	ground->Draw();
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	manual->Draw();
	title->Draw();
	startButton->Draw();
	stage1->Draw();
	stage2->Draw();
	manualButton->Draw();
	//close->Draw();
	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect->Draw(DirectXSetting::GetIns()->GetCmdList(), postEffectNo);
	DirectXSetting::GetIns()->PostDraw();

}

void TitleScene::Finalize()
{
	safe_delete(postEffect);
	safe_delete(title);
	safe_delete(titlePlayer);
	safe_delete(camera);
	safe_delete(ground);
	safe_delete(startButton);
	safe_delete(stage1);
	safe_delete(stage2);
	safe_delete(manualButton);
	safe_delete(manual);
	safe_delete(close);
}
