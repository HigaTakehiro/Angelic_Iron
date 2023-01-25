#include "TitleScene.h"

void TitleScene::Initialize()
{
	SoundManager::GetIns()->PlayBGM(SoundManager::TITLE, true, 0.1f);
	isSceneChangeComplete = true;
	SceneChangeInitialize();

	cameraPos = { -100, 50, 200 };
	cameraTargetPos = { 0, 500, 0 };

	camera = new Camera;
	camera->SetEye(cameraPos);
	camera->SetTarget(cameraTargetPos);

	textDraw->Initialize();

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

	light = LightGroup::Create();
	for (int i = 0; i < 3; i++) {
		light->SetDirLightActive(0, true);
		light->SetPointLightActive(i, false);
		light->SetSpotLightActive(i, false);
	}
	light->SetCircleShadowActive(0, true);
	Object3d::SetLight(light);

	titlePlayer = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Player_Stand));
	playerScale = { 20, 20, 20 };
	playerPos = { -30, 50, 0 };
	playerRot = { 0, 0, 0 };
	titlePlayer->SetScale(playerScale);
	titlePlayer->SetPosition(playerPos);
	titlePlayer->SetRotation(playerRot);

	wave = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Wave));
	wavePos = { 0, -50, 0 };
	wave->SetPosition(wavePos);
	waveScale = { 10, 10, 10 };
	wave->SetScale(waveScale);
	wave->SetAmbient({ 1, 1, 1 });

	aircraft_Carrier = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Aircraft_Carrier));
	aircraft_Carrier->SetScale({ 10, 10, 10 });
	aircraft_Carrier->SetAmbient({ 1, 1, 1 });

	testSquareModel = Shapes::CreateSquare({ 0.0f, 0.0f }, { 15.0f, 15.0f }, "Bomb.png");
	testSquare = Object3d::Create(testSquareModel);
	testSquare->SetRotation({ 0.0f, 180.0f, 0.0f });
	testSquare->SetIsBillboard(true);

	celetialSphere = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::CelestialSphere));
	celetialSphere->SetScale({ 15, 15, 15 });

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

	postEffectNo = PostEffect::NORMAL;
	particle = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);

	debugText.Initialize(0);
}

void TitleScene::Update()
{
	mousePos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };
	aim->SetPosition(mousePos);

	sphereRot.y += 0.1f;
	celetialSphere->SetRotation(sphereRot);

	static Vector3 lightPos = { 0, 0, 0 };

	char lightPosText[256];
	sprintf_s(lightPosText, "PlayerWPos = (x : %f, y : %f, z : %f)", lightPos.x, lightPos.y, lightPos.z);
	debugText.Print(lightPosText, 0, 0, 2);

	light->SetDirLightDirection(0, { 0, -1, 0 });
	light->SetCircleShadowDir(0, { 0, -1, 0 });
	light->SetCircleShadowCasterPos(0, playerPos);
	light->SetCircleShadowAtten(0, { 0.0f, 0.01f, 0.0f });
	light->SetCircleShadowDistanceCasterLight(0, 3000.0f);
	light->SetCircleShadowAngle(0, { 0.0f, 0.5f });

	titlePlayer->SetPosition(playerPos);

	titlePlayer->Update();
	wave->Update(1200.0f);
	particle->Update();
	aircraft_Carrier->Update();
	celetialSphere->Update();
	test->Update();
	testSquare->Update();
	light->Update();


	const float cameraSpeed = 10.0f;
	if (KeyInput::GetIns()->PushKey(DIK_LEFT)) {
		if (camera->GetTarget().z < cameraPos.z) {
			cameraPos.x += cameraSpeed;
		}
		else {
			cameraPos.x -= cameraSpeed;
		}
	}
	if (KeyInput::GetIns()->PushKey(DIK_RIGHT)) {
		XMFLOAT3 camraPos = camera->GetEye();
		if (camera->GetTarget().z < cameraPos.z) {
			cameraPos.x -= cameraSpeed;
		}
		else {
			cameraPos.x += cameraSpeed;
		}
	}
	if (KeyInput::GetIns()->PushKey(DIK_UP) && KeyInput::GetIns()->PushKey(DIK_LSHIFT)) {
		cameraPos.y += cameraSpeed;
	}
	else if (KeyInput::GetIns()->PushKey(DIK_UP)) {
		cameraPos.z -= cameraSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_DOWN) && KeyInput::GetIns()->PushKey(DIK_LSHIFT)) {
		cameraPos.y -= cameraSpeed;
	}
	else if (KeyInput::GetIns()->PushKey(DIK_DOWN)) {
		cameraPos.z += cameraSpeed;
	}

	camera->SetEye(cameraPos);
	//testSquare->SetPosition(lightPos);

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
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK) && !isStageChoice) {
			isStage1 = true;
			isStageChoice = true;
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
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK) && !isStageChoice) {
			isStage2 = true;
			isStageChoice = true;
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
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK) && !isStageChoice) {
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

	if (isStageChoice) {
		SoundManager::GetIns()->StopBGM(SoundManager::TITLE);
	}

	if (isSceneChangeComplete) {
		SceneChangeCompleteEffect();
	}
	if (isSceneChangeStart) {
		SceneChangeEffect();
	}

	//シーン切り替え
	if (isStageChoice) {
		if (startTimer <= startTime) {
			startTimer++;
		}
		if (startTimer >= startTime / 2.0f) {
			postEffectNo = PostEffect::DASH;
			for (int i = 0; i < 8; i++) {
				Vector3 particlePos = { 0.0f, 0.0f, 0.0f };
				particlePos = MotionMath::GetIns()->CircularMotion(playerPos, particlePos, 45 * i, 10.0f, MotionMath::Y);
				particlePos.normalize();
				particle->Add(30, playerPos, particlePos, -particlePos, 3.0f);
			}
		}
		float timeRate = min((float)startTimer / (float)startTime, 1.0f);
		Vector3 pointA = { -30, 50, 0 };
		Vector3 pointB = { -30.0f, 50.0f, 200.0f };
		Vector3 pointC = { -30, 300, 200 };
		Vector3 easingPointA = easeIn(pointA, pointB, timeRate);
		Vector3 easingPointB = easeIn(pointB, pointC, timeRate);
		playerPos = easeIn(easingPointA, easingPointB, timeRate);
		cameraPos.y = Easing::GetIns()->easeIn(startTimer, startTime / 2, 3, cameraPos.y);
		cameraPos.z = Easing::GetIns()->easeIn(startTimer, startTime / 2, -150, cameraPos.z);
		titlePlayer->SetPosition(playerPos);
		if (startTimer >= startTime) {
			isSceneChangeStart = true;
		}

		if (isSceneChange) {
			if (isStage1) {
				SceneManager::SceneChange(SceneManager::Stage1_Rail);
			}
			else if (isStage2) {
				SceneManager::SceneChange(SceneManager::Stage2_Rail);
			}
		}
	}

}

void TitleScene::Draw()
{
	//背景色
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };

	postEffect->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//スプライト描画処理(背景)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	//background->Draw();
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	titlePlayer->Draw();
	wave->Draw(Object3d::Wave);
	celetialSphere->Draw();
	aircraft_Carrier->Draw();
	particle->Draw(DirectXSetting::GetIns()->GetCmdList());
	//test->Draw(DirectXSetting::GetIns()->GetCmdList());
	//testSquare->Draw();
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	if (isManual) {
		manual->Draw();
		manual2->Draw();
		allow->Draw();
		close->Draw();
	}

	if (isStageSelect && !isManual && !isStageChoice) {
		stage1->Draw();
		stage2->Draw();
		manualButton->Draw();
	}

	if (!isStageSelect) {
		startButton->Draw();
	}
	title->Draw();
	aim->Draw();
	//debugText.DrawAll(DirectXSetting::GetIns()->GetCmdList());
	SceneChangeEffectDraw();
	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	static D2D1_RECT_F rectangle2 = D2D1::RectF(
		0, 500, 1280, 720
	);

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo, true);
	DirectXSetting::GetIns()->PostDraw();

}

void TitleScene::Finalize()
{
	safe_delete(postEffect);
	safe_delete(title);
	safe_delete(titlePlayer);
	safe_delete(camera);
	safe_delete(wave);
	safe_delete(aircraft_Carrier);
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
	safe_delete(light);
	safe_delete(textDraw);
	safe_delete(particle);
}