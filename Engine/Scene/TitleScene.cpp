#include "TitleScene.h"

void TitleScene::Initialize()
{
	cameraPos = { -50, 0, 100 };
	cameraTargetPos = { 0, 500, 0 };

	camera = new Camera;
	camera->SetEye(cameraPos);
	camera->SetTarget(cameraTargetPos);

	titlePos = { 300, 200 };
	startButtonPos = { 640, 550 };
	stage1Pos = { -300, 100 };
	stage2Pos = { -300, 300 };
	manualButtonPos = { -300, 500 };
	closePos = { 640, 550 };

	const XMFLOAT2 spriteCenter = { 0.5f, 0.5f };
	title = Sprite::Create(ImageManager::ImageName::title, titlePos);
	title->SetAnchorPoint(spriteCenter);
	startButton = Sprite::Create(ImageManager::ImageName::StartButton, startButtonPos);
	startButton->SetAnchorPoint(spriteCenter);
	stage1 = Sprite::Create(ImageManager::ImageName::Stage1, stage1Pos);
	stage1->SetAnchorPoint(spriteCenter);
	stage2 = Sprite::Create(ImageManager::ImageName::Stage2, stage2Pos);
	stage2->SetAnchorPoint(spriteCenter);
	manualButton = Sprite::Create(ImageManager::ImageName::ManualButton, manualButtonPos);
	manualButton->SetAnchorPoint(spriteCenter);
	manual = Sprite::Create(ImageManager::ImageName::Manual, { 640, 300 });
	manual->SetAnchorPoint(spriteCenter);
	close = Sprite::Create(ImageManager::ImageName::Close, closePos);
	close->SetAnchorPoint(spriteCenter);

	startButtonSize = startButton->GetSize();
	stage1Size = stage1->GetSize();
	stage2Size = stage2->GetSize();
	manualButtonSize = manualButton->GetSize();
	manualSize = { 0, 0 };
	manualMaxSize = manual->GetSize();
	closeSize = close->GetSize();
	startTimer = 0;

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

	celetialSphere = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::CelestialSphere));
	celetialSphere->SetScale({ 15, 15, 15 });

	mousePos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };
	stageSelectTimer = 0;

	postEffect = new PostEffect();
	postEffect->Initialize();
}

void TitleScene::Update()
{
	mousePos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };

	titlePlayer->Update();
	ground->Update();
	celetialSphere->Update();

	if (!isStageSelect && IsMouseHitSprite(mousePos, startButtonPos, 256, 128)) {
		XMFLOAT2 spriteSize = startButtonSize;
		spriteSize.x *= 0.9f;
		spriteSize.y *= 0.9f;
		startButton->SetSize(spriteSize);
		startButton->SetAlpha(selectAlpha);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
			isStageSelect = true;
		}
	}
	else {
		startButton->SetSize(startButtonSize);
		startButton->SetAlpha(initAlpha);
	}

	if (IsMouseHitSprite(mousePos, stage1Pos, 270, 128)) {
		XMFLOAT2 spriteSize = stage1Size;
		spriteSize.x *= 0.9f;
		spriteSize.y *= 0.9f;
		stage1->SetSize(spriteSize);
		stage1->SetAlpha(selectAlpha);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
			isStage1 = true;
		}
	}
	else {
		stage1->SetSize(stage1Size);
		stage1->SetAlpha(initAlpha);
	}

	if (IsMouseHitSprite(mousePos, stage2Pos, 300, 128)) {
		XMFLOAT2 spriteSize = stage2Size;
		spriteSize.x *= 0.9f;
		spriteSize.y *= 0.9f;
		stage2->SetSize(spriteSize);
		stage2->SetAlpha(selectAlpha);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
			isStage2 = true;
		}
	}
	else {
		stage2->SetSize(stage2Size);
		stage2->SetAlpha(initAlpha);
	}
	
	if (IsMouseHitSprite(mousePos, manualButtonPos, 300, 128)) {
		XMFLOAT2 spriteSize = manualButtonSize;
		spriteSize.x *= 0.9f;
		spriteSize.y *= 0.9f;
		manualButton->SetSize(spriteSize);
		manualButton->SetAlpha(selectAlpha);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
			isManual = true;
		}
	}
	else {
		manualButton->SetSize(manualButtonSize);
		manualButton->SetAlpha(initAlpha);
	}

	if (IsMouseHitSprite(mousePos, closePos, 270, 128)) {
		XMFLOAT2 spriteSize = closeSize;
		spriteSize.x *= 0.9f;
		spriteSize.y *= 0.9f;
		close->SetSize(spriteSize);
		close->SetAlpha(selectAlpha);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
			isManual = false;
		}
	}
	else {
		close->SetSize(closeSize);
		close->SetAlpha(initAlpha);
	}

	if (isStageSelect) {
		const float outPos = -300;
		const float comePos = 200;
		stageSelectTimer++;
		if (stageSelectTimer >= manualComeTime) {
			stageSelectTimer = manualComeTime;
		}
		cameraTargetPos.y = Easing::GetIns()->easeOut(stageSelectTimer, stage1ComeTime, 1, cameraTargetPos.y);
		titlePos.x = Easing::GetIns()->easeInBack(stageSelectTimer, titleOutTime, outPos, titlePos.x, 1);
		stage1Pos.x = Easing::GetIns()->easeIn(stageSelectTimer, stage1ComeTime, comePos, stage1Pos.x);
		stage2Pos.x = Easing::GetIns()->easeIn(stageSelectTimer, stage2ComeTime, comePos, stage2Pos.x);
		manualButtonPos.x = Easing::GetIns()->easeIn(stageSelectTimer, manualComeTime, comePos, manualButtonPos.x);

		camera->SetTarget(cameraTargetPos);
		title->SetPosition(titlePos);
		stage1->SetPosition(stage1Pos);
		stage2->SetPosition(stage2Pos);
		manualButton->SetPosition(manualButtonPos);
	}

	if (isManual) {
		const float openWidth = manualMaxSize.x;
		const float openHeight = manualMaxSize.y;
		const float outPos = -300;

		stageSelectTimer = titleOutTime;
		stage1Pos.x = outPos;
		stage2Pos.x = outPos;
		manualButtonPos.x = outPos;

		manualTimer++;
		if (manualTimer >= manualOpenTime) {
			manualTimer = manualOpenTime;
		}
		manualSize.x = Easing::GetIns()->easeOut(manualTimer, manualOpenTime, openWidth, manualSize.x);
		manualSize.y = Easing::GetIns()->easeOut(manualTimer, manualOpenTime, openHeight, manualSize.y);

		manual->SetSize(manualSize);
	}
	else {
		manualTimer = 0;
		manualSize = { 0.0f, 0.0f };
	}

	//シーン切り替え
	if (isStage1) {
		startTimer++;
		playerPos.z = Easing::GetIns()->easeIn(startTimer, startTime / 2, 200, playerPos.z);
		titlePlayer->SetPosition(playerPos);
		if (startTimer >= startTime) {
			SceneManager::SceneChange(SceneManager::Stage1_Rail);
		}
	}
	else if (isStage2) {
		startTimer++;
		playerPos.z = Easing::GetIns()->easeIn(startTimer, startTime / 2, 200, playerPos.z);
		titlePlayer->SetPosition(playerPos);
		if (startTimer >= startTime) {
			SceneManager::SceneChange(SceneManager::Stage2_Rail);
		}
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
	celetialSphere->Draw();
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	if (isManual) {
		manual->Draw();
		close->Draw();
	}

	if (isStageSelect && !isManual) {
		stage1->Draw();
		stage2->Draw();
		manualButton->Draw();
	}

	if (!isStageSelect) {
		startButton->Draw();
	}
	title->Draw();
	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect->Draw(DirectXSetting::GetIns()->GetCmdList(), 10.0f, PostEffect::NONE);
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
	safe_delete(celetialSphere);
	safe_delete(close);
}