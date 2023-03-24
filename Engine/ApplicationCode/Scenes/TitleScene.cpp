#include "TitleScene.h"

void TitleScene::Initialize()
{
	//SoundManager::GetIns()->PlayBGM(SoundManager::TITLE, true, 0.1f);
	SceneChangeEffect::GetIns()->SetIsSceneChangeComplete(true);

	cameraPos = { -100, 50, 200 };
	cameraTargetPos = { 0, 500, 0 };

	camera = std::make_unique<Camera>();
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
	title = Sprite::UniquePtrCreate(ImageManager::ImageName::title, titlePos);
	title->SetAnchorPoint(spriteCenter);
	startButton = Sprite::UniquePtrCreate(ImageManager::ImageName::StartButton, startButtonPos);
	startButton->SetAnchorPoint(spriteCenter);
	stage1 = Sprite::UniquePtrCreate(ImageManager::ImageName::Stage1, stage1Pos);
	stage1->SetAnchorPoint(spriteCenter);
	stage2 = Sprite::UniquePtrCreate(ImageManager::ImageName::Stage2, stage2Pos);
	stage2->SetAnchorPoint(spriteCenter);
	manualButton = Sprite::UniquePtrCreate(ImageManager::ImageName::ManualButton, manualButtonPos);
	manualButton->SetAnchorPoint(spriteCenter);
	manual = Sprite::UniquePtrCreate(ImageManager::ImageName::Manual, manualPos);
	manual->SetAnchorPoint(spriteCenter);
	manual2 = Sprite::UniquePtrCreate(ImageManager::Manual_2, { manualPos.x * (pageNumber + 2), manualPos.y });
	manual2->SetAnchorPoint(spriteCenter);
	allow = Sprite::UniquePtrCreate(ImageManager::Allow, allowPos);
	allow->SetAnchorPoint(spriteCenter);
	allow->SetRotation(90.0f);
	close = Sprite::UniquePtrCreate(ImageManager::ImageName::Close, closePos);
	close->SetAnchorPoint(spriteCenter);

	startButtonSize = startButton->GetSize();
	stage1Size = stage1->GetSize();
	stage2Size = stage2->GetSize();
	manualButtonSize = manualButton->GetSize();
	manualSize = { 0, 0 };
	manualMaxSize = manual->GetSize();
	closeSize = close->GetSize();
	allowSize = allow->GetSize();
	startTimer = 0;

	light = LightGroup::UniquePtrCreate();
	for (int i = 0; i < 3; i++) {
		light->SetDirLightActive(0, true);
		light->SetPointLightActive(i, false);
		light->SetSpotLightActive(i, false);
	}
	//light->SetCircleShadowActive(0, true);
	light->SetShadowMapActive(0, true);
	Object3d::SetLight(light.get());

	jsonLoader = std::make_unique<JsonLoader>();
	jsonLoader->StageDataLoadandSet("TitleScene_Stage");

	titlePlayer = Object3d::UniquePtrCreate(ModelManager::GetIns()->GetModel("player_Stand"));
	playerScale = { 20, 20, 20 };
	playerPos = { -30, 50, 0 };
	playerRot = { 0, 0, 0 };
	titlePlayer->SetScale(playerScale);
	titlePlayer->SetPosition(playerPos);
	titlePlayer->SetRotation(playerRot);

	mousePos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };
	stageSelectTimer = 0;

	postEffect = std::make_unique<PostEffect>();
	postEffect->Initialize();

	postEffectNo = PostEffect::NORMAL;
	particle = ParticleManager::UniquePtrCreate(DirectXSetting::GetIns()->GetDev(), camera.get());

	debugText.Initialize(0);
}

void TitleScene::Update()
{
	mousePos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };

	static Vector3 lightPos = { 0, 0, 0 };
	static Vector3 lightDir = { 1, 0, 0 };

	char lightPosText[256];
	sprintf_s(lightPosText, "PlayerWPos = (x : %f, y : %f, z : %f)", lightPos.x, lightPos.y, lightPos.z);
	debugText.Print(lightPosText, 0, 0, 2);

	light->SetDirLightDirection(0, { 0, -1, 0 });
	light->SetShadowMapLightDir(0, { 0, -1, 0 });
	//light->SetCircleShadowDir(0, { 0, -1, 0 });
	//light->SetCircleShadowCasterPos(0, playerPos);
	//light->SetCircleShadowAtten(0, { 0.0f, 0.01f, 0.0f });
	//light->SetCircleShadowDistanceCasterLight(0, 3000.0f);
	//light->SetCircleShadowAngle(0, { 0.0f, 0.5f });

	titlePlayer->SetPosition(playerPos);

	titlePlayer->Update();
	particle->Update();
	light->Update();
	//レティクル更新処理
	Reticle::GetIns()->Update();
	Reticle::GetIns()->SetIsSelectReticle(false);

	const float cameraSpeed = 10.0f;
	if (KeyInput::GetIns()->PushKey(DIK_LEFT)) {
		lightDir.x += 1.0f;
		light->SetShadowMapLightDir(0, { lightDir.x, lightDir.y, lightDir.z });
	}
	if (KeyInput::GetIns()->PushKey(DIK_RIGHT)) {
		lightDir.x -= 1.0f;
		light->SetShadowMapLightDir(0, { lightDir.x, lightDir.y, lightDir.z });
	}
	if (KeyInput::GetIns()->PushKey(DIK_UP) && KeyInput::GetIns()->PushKey(DIK_LSHIFT)) {
		lightDir.z += 1.0f;
		light->SetShadowMapLightDir(0, { lightDir.x, lightDir.y, lightDir.z });
	}
	else if (KeyInput::GetIns()->PushKey(DIK_UP)) {
		lightDir.z -= 1.0f;
		light->SetShadowMapLightDir(0, { lightDir.x, lightDir.y, lightDir.z });
	}
	if (KeyInput::GetIns()->PushKey(DIK_DOWN) && KeyInput::GetIns()->PushKey(DIK_LSHIFT)) {
		lightDir.y -= 1.0f;
		light->SetShadowMapLightDir(0, { lightDir.x, lightDir.y, lightDir.z });
	}
	else if (KeyInput::GetIns()->PushKey(DIK_DOWN)) {
		lightDir.y += 1.0f;
		light->SetShadowMapLightDir(0, { lightDir.x, lightDir.y, lightDir.z });
	}

	camera->SetEye(cameraPos);
	//testSquare->SetPosition(lightPos);

	if (!isStageSelectMenu && IsMouseHitSprite(mousePos, startButtonPos, 256, 128)) {
		XMFLOAT2 spriteSize = startButtonSize;
		spriteSize.x *= 0.9f;
		spriteSize.y *= 0.9f;
		startButton->SetSize(spriteSize);
		startButton->SetAlpha(selectAlpha);
		Reticle::GetIns()->SetIsSelectReticle(true);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
			isStageSelectMenu = true;
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
		Reticle::GetIns()->SetIsSelectReticle(true);
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
		Reticle::GetIns()->SetIsSelectReticle(true);
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
		Reticle::GetIns()->SetIsSelectReticle(true);
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
		Reticle::GetIns()->SetIsSelectReticle(true);
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
		Reticle::GetIns()->SetIsSelectReticle(true);
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

	if (isStageSelectMenu) {
		const float outPos = -300;
		const float comePos = 200;
		stageSelectTimer++;
		if (stageSelectTimer >= manualComeTime) {
			stageSelectTimer = manualComeTime;
		}
		cameraTargetPos.y = Easing::easeOut((float)stageSelectTimer, (float)stage1ComeTime, 1, cameraTargetPos.y);
		titlePos.x = Easing::easeInBack((float)stageSelectTimer, (float)titleOutTime, outPos, titlePos.x, 1);
		stage1Pos.x = Easing::easeIn((float)stageSelectTimer, (float)stage1ComeTime, comePos, stage1Pos.x);
		stage2Pos.x = Easing::easeIn((float)stageSelectTimer, (float)stage2ComeTime, comePos, stage2Pos.x);
		manualButtonPos.x = Easing::easeIn((float)stageSelectTimer, (float)manualComeTime, comePos, manualButtonPos.x);

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
		manualSize.x = Easing::easeOut((float)manualTimer, (float)manualOpenTime, openWidth, manualSize.x);
		manualSize.y = Easing::easeOut((float)manualTimer, (float)manualOpenTime, openHeight, manualSize.y);

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
			manualPos.x = Easing::easeOut((float)manualSlideTimer, (float)manualSlideTime, manualOutPos, manualPos.x);
		}
		else if (isPrevPage) {
			manualPos.x = Easing::easeOut((float)manualSlideTimer, (float)manualSlideTime, manualInPos, manualPos.x);
		}

		manual->SetPosition(manualPos);
		manual2->SetPosition({ manualPos.x + (manualInPos * 2), manualPos.y });
		manual->SetSize(manualSize);
	}
	else {
		manualTimer = 0;
		manualSize = { 0.0f, 0.0f };
	}

	jsonLoader->Update();

	if (isStageChoice) {
		SoundManager::GetIns()->StopBGM(SoundManager::TITLE);
	}
	//シーン切り替え演出を更新
	SceneChangeEffect::GetIns()->Update();
	//シーン切り替え
	SceneChange();
}

void TitleScene::Draw()
{
	//背景色
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };

	if (postEffectNo == PostEffect::DASH) {
		postEffect->SetBlurCenter({ -0.5f, -0.5f });
		postEffect->SetMask(0.0f);
	}

	postEffect->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//スプライト描画処理(背景)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	titlePlayer->Draw();
	jsonLoader->Draw();
	particle->Draw(DirectXSetting::GetIns()->GetCmdList());
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	if (isManual) {
		manual->Draw();
		manual2->Draw();
		allow->Draw();
		close->Draw();
	}

	if (isStageSelectMenu && !isManual && !isStageChoice) {
		stage1->Draw();
		stage2->Draw();
		manualButton->Draw();
	}

	if (!isStageSelectMenu) {
		startButton->Draw();
	}
	title->Draw();
	//debugText.DrawAll(DirectXSetting::GetIns()->GetCmdList());
	Reticle::GetIns()->Draw();
	SceneChangeEffect::GetIns()->Draw();
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
	jsonLoader->Finalize();
}

void TitleScene::SceneChange()
{
	//シーン切り替え
	//ステージ選択フラグが立っていれば
	if (isStageChoice) {
		if (startTimer <= startTime) {
			startTimer++;
		}
		//開始演出時間が半分過ぎたら
		if (startTimer >= startTime / 2.0f) {
			//ブラーをかける
			postEffectNo = PostEffect::DASH;
			//パーティクルを発生させる
			//乱数上限
			const int randMax = 18;
			//パーティクル生成時間
			int particleLife = 3;
			//加速度
			Vector3 acc = { 0.0f, 0.0f, 0.0f };
			//初期アルファ値
			Vector3 initAlpha = { 0.0f, 0.0f, 0.6f };
			//最終的なアルファ値
			Vector3 endAlpha = { 1.0f, 1.0f, 1.0f };
			//最終的な大きさ
			float endScale = 0.0f;

			//プレイヤーのワールド行列からパーティクルの生成位置を求める
			XMVECTOR playerPos = { 0.0f, 1.2f, -1.0f };
			playerPos = XMVector3TransformCoord(playerPos, titlePlayer->GetMatWorld());
			Vector3 thrusterPos = playerPos;

			for (int i = 0; i < 10; i++) {
				float thrusterPower = (float)(rand() % randMax);
				thrusterPower *= -0.1f;
				float startScale = (float)(rand() % (randMax - 2));
				XMVECTOR playerBack = { 0.0f, 0.0f, thrusterPower };
				playerBack = XMVector3TransformNormal(playerBack, titlePlayer->GetMatWorld());
				Vector3 thrusterDir = playerBack;
				particle->Add(
					particleLife,
					thrusterPos,
					thrusterDir,
					acc,
					startScale,
					endScale,
					initAlpha,
					endAlpha
				);
			}
		}
		//時間を0~1の値をとるようにする
		float timeRate = min((float)startTimer / (float)startTime, 1.0f);
		//線分補間用座標
		Vector3 point[3];
		point[0] = { -30, 50, 0 };
		point[1] = { -30.0f, 50.0f, 200.0f };
		point[2] = { -30, 300, 200 };

		//弧を描くように移動させる
		Vector3 easingPointA = easeIn(point[0], point[1], timeRate);
		Vector3 easingPointB = easeIn(point[1], point[2], timeRate);
		playerPos = easeIn(easingPointA, easingPointB, timeRate);

		//カメラ位置を変更する
		cameraPos.y = Easing::easeIn((float)startTimer, (float)startTime / 2, 3, cameraPos.y);
		cameraPos.z = Easing::easeIn((float)startTimer, (float)startTime / 2, -150, cameraPos.z);
		//プレイヤー座標を更新する
		titlePlayer->SetPosition(playerPos);

		//シーン切り替え演出開始フラグを立てる
		if (startTimer >= startTime) {
			SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
		}
		//シーンを切り替える
		if (SceneChangeEffect::GetIns()->GetIsSceneChange()) {
			if (isStage1) {
				SceneManager::SceneChange(SceneManager::Stage1_Rail);
			}
			else if (isStage2) {
				SceneManager::SceneChange(SceneManager::Stage2_Rail);
			}
		}
	}
}
