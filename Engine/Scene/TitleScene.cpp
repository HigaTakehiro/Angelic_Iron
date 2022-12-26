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
	allowPos = { 1240, 330 };
	manualPos = { 640, 300 };

	pageNumber = 1;
	prePageNumber = 1;

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
	manual = Sprite::Create(ImageManager::ImageName::Manual, manualPos);
	manual->SetAnchorPoint(spriteCenter);
	manual2 = Sprite::Create(ImageManager::Manual_2, { manualPos.x * (pageNumber + 2), manualPos.y });
	manual2->SetAnchorPoint(spriteCenter);
	allow = Sprite::Create(ImageManager::Allow, allowPos);
	allow->SetAnchorPoint(spriteCenter);
	allow->SetRotation(90.0f);
	close = Sprite::Create(ImageManager::ImageName::Close, closePos);
	close->SetAnchorPoint(spriteCenter);
	aim = Sprite::Create(ImageManager::aim, { 0, 0 });
	aim->SetAnchorPoint({ 0.5f, 0.5f });
	aim->SetSize({ aim->GetSize().x / 2, aim->GetSize().y / 2 });

	startButtonSize = startButton->GetSize();
	stage1Size = stage1->GetSize();
	stage2Size = stage2->GetSize();
	manualButtonSize = manualButton->GetSize();
	manualSize = { 0, 0 };
	manualMaxSize = manual->GetSize();
	closeSize = close->GetSize();
	allowSize = allow->GetSize();
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

	testSquareModel = Shapes::CreateSquare({ 0.0f, 0.0f }, { 15.0f, 15.0f }, "Bomb.png");
	testSquare = Object3d::Create(testSquareModel);
	testSquare->SetRotation({ 0.0f, 0.0f, 0.0f });

	celetialSphere = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::CelestialSphere));
	celetialSphere->SetScale({ 15, 15, 15 });

	particle = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);
	//particle->LoadTexture("Aim");
	particle2 = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);
	particle2->LoadTexture("Bomb");

	mousePos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };
	stageSelectTimer = 0;

	postEffect = new PostEffect();
	postEffect->Initialize();

	sphereRot = { 0, 0, 0 };

	FBXObject3d::SetCamera(camera);
	test = new FBXObject3d;
	test->Initialize();
	test->SetModel(ModelManager::GetIns()->GetFBXModel(ModelManager::Test));
	test->SetScale({ 0.05f, 0.05f, 0.05f });
	test->PlayAnimation(true);
}

void TitleScene::Update()
{
	mousePos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };
	aim->SetPosition(mousePos);

	sphereRot.y += 0.1f;
	celetialSphere->SetRotation(sphereRot);

	for (int i = 0; i < 10; i++) {
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.01f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		const float startScale = 10.0f;
		const float endScale = 10.0f;

		particle->Add(60, pos, vel, acc, startScale, endScale, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f);
		//particle2->Add(60, pos, vel, acc, startScale, endScale, { 1.0f, 0.0f, 0.0f }, {0.0f, 0.0f, 1.0f});
	}

	titlePlayer->Update();
	ground->Update();
	celetialSphere->Update();
	test->Update();
	testSquare->Update();
	particle->Update();
	//particle2->Update();

	if (KeyInput::GetIns()->PushKey(DIK_LEFT)) {
		Vector3 cameraPos = { camera->GetEye().x, camera->GetEye().y,camera->GetEye().z };
		cameraPos.x -= 2.0f;
		camera->SetEye(cameraPos);
	}
	if (KeyInput::GetIns()->PushKey(DIK_RIGHT)) {
		Vector3 cameraPos = { camera->GetEye().x, camera->GetEye().y,camera->GetEye().z };
		cameraPos.x += 2.0f;
		camera->SetEye(cameraPos);
	}
	if (KeyInput::GetIns()->PushKey(DIK_UP)) {
		Vector3 cameraPos = { camera->GetEye().x, camera->GetEye().y,camera->GetEye().z };
		cameraPos.y += 2.0f;
		camera->SetEye(cameraPos);
	}
	if (KeyInput::GetIns()->PushKey(DIK_DOWN)) {
		Vector3 cameraPos = { camera->GetEye().x, camera->GetEye().y,camera->GetEye().z };
		cameraPos.y -= 2.0f;
		camera->SetEye(cameraPos);
	}

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

	if (IsMouseHitSprite(mousePos, allowPos, 64, 64)) {
		XMFLOAT2 spriteSize = allowSize;
		spriteSize.x *= 0.9f;
		spriteSize.y *= 0.9f;
		float spriteRot = 90;
		allow->SetSize(spriteSize);
		allow->SetAlpha(selectAlpha);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK) && pageNumber == 1) {
			pageNumber += 1;
		}
		else if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK) && pageNumber == 2) {
			pageNumber -= 1;
		}

		if (pageNumber != 1) {
			allowPos.x = 50;
			spriteRot = -90;
		}
		else {
			allowPos.x = 1240;
			spriteRot = 90;
		}

		allow->SetPosition(allowPos);
		allow->SetRotation(spriteRot);
	}
	else {
		allow->SetSize(allowSize);
		allow->SetAlpha(initAlpha);
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
		const float manualOutPos = -640;
		const float manualInPos = 640;
		const float outPos = -300;

		stageSelectTimer = titleOutTime;
		stage1Pos.x = outPos;
		stage2Pos.x = outPos;
		manualButtonPos.x = outPos;

		manualTimer++;
		manualSlideTimer++;
		if (manualTimer >= manualOpenTime) {
			manualTimer = manualOpenTime;
		}
		if (manualSlideTimer >= manualSlideTime) {
			manualSlideTimer = manualSlideTime;
			isNextPage = false;
			isPrevPage = false;
		}
		manualSize.x = Easing::GetIns()->easeOut(manualTimer, manualOpenTime, openWidth, manualSize.x);
		manualSize.y = Easing::GetIns()->easeOut(manualTimer, manualOpenTime, openHeight, manualSize.y);

		if (pageNumber != prePageNumber) {
			isNextPage = false;
			isPrevPage = false;
			manualSlideTimer = 0;
			if (prePageNumber < pageNumber) {
				isNextPage = true;
				manualPos.x = manualInPos;
			}
			else {
				isPrevPage = true;
				manualPos.x = manualOutPos;
			}
			prePageNumber = pageNumber;
		}
		if (isNextPage) {
			manualPos.x = Easing::GetIns()->easeOut(manualSlideTimer, manualSlideTime, manualOutPos, manualPos.x);
		}
		else if (isPrevPage) {
			manualPos.x = Easing::GetIns()->easeOut(manualSlideTimer, manualSlideTime, manualInPos, manualPos.x);
		}

		manual->SetPosition(manualPos);
		manual2->SetPosition({ manualPos.x + (manualInPos * 2), manualPos.y });
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
	//test->Draw(DirectXSetting::GetIns()->GetCmdList());
	testSquare->Draw();
	Object3d::PostDraw();

	particle->Draw(DirectXSetting::GetIns()->GetCmdList());
	//particle2->Draw(DirectXSetting::GetIns()->GetCmdList());

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	if (isManual) {
		manual->Draw();
		manual2->Draw();
		allow->Draw();
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
	aim->Draw();
	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, PostEffect::NONE);
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
	safe_delete(aim);
	safe_delete(manual2);
	safe_delete(allow);
	safe_delete(test);
	safe_delete(testSquare);
	safe_delete(testSquareModel);
	safe_delete(particle);
	safe_delete(particle2);
}