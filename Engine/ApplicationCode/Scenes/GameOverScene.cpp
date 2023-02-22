#include "GameOverScene.h"

void GameOverScene::Initialize()
{
	cameraPos = { -50, 0, 100 };
	cameraTargetPos = { 0, 500, 0 };

	SceneChangeEffect::GetIns()->SetIsSceneChangeComplete(true);

	camera = new Camera;
	camera->SetEye(cameraPos);
	camera->SetTarget(cameraTargetPos);

	score = Sprite::Create(ImageManager::ImageName::score, { 300, 100 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	for (int i = 0; i < 6; i++) {
		scoreNumbers[i] = Sprite::Create(ImageManager::scoreNumbers, { 450 - ((float)i * 60), 250 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
		scoreNumbers[i]->SetTextureRect({ nine, 0 }, { 64, 64 });
		scoreNumbers[i]->SetSize({ 64, 64 });
	}
	titleBack = Sprite::Create(ImageManager::TitleBack, { 840.0f, 600.0f }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	titleBackAlpha = 1.0f;
	titleBackSize = titleBack->GetSize();
	restart = Sprite::Create(ImageManager::Restart, { 440.0f, 600.0f }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	restartAlpha = 1.0f;
	restartSize = restart->GetSize();
	restartSize.x /= 2;
	restartSize.y /= 2;

	light = LightGroup::Create();
	for (int i = 0; i < 3; i++) {
		light->SetDirLightActive(i, false);
		light->SetPointLightActive(i, false);
		light->SetSpotLightActive(0, true);
	}
	light->SetCircleShadowActive(0, true);
	Object3d::SetLight(light);



	scoreRollTimer = 0;
	for (int i = 0; i < 6; i++) {
		scoreRollPos[i] = { -640, 0 };
	}

	resultPlayer = Object3d::Create(ModelManager::GetIns()->GetModel("player_Down"));
	playerScale = { 20, 20, 20 };
	playerPos = { -30, 500, 0 };
	playerRot = { 0, 0, 0 };
	resultPlayer->SetScale(playerScale);
	resultPlayer->SetPosition(playerPos);
	resultPlayer->SetRotation(playerRot);

	ground = Object3d::Create(ModelManager::GetIns()->GetModel("ground"));
	groundPos = { 0, -50, 0 };
	ground->SetPosition(groundPos);
	groundScale = { 10, 10, 10 };
	ground->SetScale(groundScale);
	ground->SetAmbient({ 0, 0, 0 });

	celetialSphere = Object3d::Create(ModelManager::GetIns()->GetModel("celetialSphere"));
	celetialSphere->SetAmbient({ 0, 0, 0 });
	celetialSphere->SetScale({ 15, 15, 15 });

	//PostEffectの初期化
	postEffect = new PostEffect();
	postEffect->Initialize();
	postEffectNo = PostEffect::DAMAGE;
}

void GameOverScene::Update()
{
	const XMFLOAT2 scoreSize = { 64, 64 };
	const float endPoint = 0;
	const float scoreRollTime = 240;
	const float fallTime = 120;
	mousePos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };

	scoreRollTimer++;
	if (scoreRollTimer >= scoreRollTime) {
		scoreRollTimer = scoreRollTime;
	}

	cameraTargetPos.y = Easing::easeOut(scoreRollTimer, fallTime, endPoint, cameraTargetPos.y);
	playerPos.y = Easing::easeOut(scoreRollTimer, fallTime, endPoint, playerPos.y);

	camera->SetTarget(cameraTargetPos);
	resultPlayer->SetPosition(playerPos);

	for (int i = 0; i < 6; i++) {
		scoreRollPos[i].x = Easing::easeOut(scoreRollTimer, scoreRollTime, (float)JudgeDigitNumber(SceneManager::GetScore(), i), scoreRollPos[i].x);
	}
	for (int i = 0; i < 6; i++) {
		scoreNumbers[i]->SetTextureRect(scoreRollPos[i], scoreSize);
	}

	resultPlayer->Update();
	celetialSphere->Update();
	ground->Update();

	titleBack->SetAlpha(titleBackAlpha);
	titleBack->SetSize(titleBackSize);
	restart->SetAlpha(restartAlpha);
	restart->SetSize(restartSize);
	titleBackAlpha = 1.0f;
	restartAlpha = 1.0f;

	light->Update();
	//レティクル更新処理
	Reticle::GetIns()->Update();

	//シーン変更
	SceneChangeEffect::GetIns()->Update();
	SceneChange();
}

void GameOverScene::Draw()
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
	resultPlayer->Draw();
	celetialSphere->Draw();
	ground->Draw();
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	score->Draw();
	for (int i = 0; i < 6; i++) {
		scoreNumbers[i]->Draw();
	}
	if (!isSelectedButton) {
		titleBack->Draw();
		restart->Draw();
	}
	Reticle::GetIns()->Draw();
	SceneChangeEffect::GetIns()->Draw();
	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect->Draw(DirectXSetting::GetIns()->GetCmdList(), 0, postEffectNo);
	DirectXSetting::GetIns()->PostDraw();
}

void GameOverScene::Finalize()
{
	safe_delete(postEffect);
	safe_delete(score);
	safe_delete(resultPlayer);
	safe_delete(celetialSphere);
	safe_delete(ground);
	safe_delete(titleBack);
	safe_delete(restart);
	safe_delete(light);
	for (int i = 0; i < 6; i++) {
		safe_delete(scoreNumbers[i]);
	}
}

void GameOverScene::SceneChange()
{
	if (!isSelectedButton) {
		if (IsMouseHitSprite(mousePos, titleBack->GetPosition(), titleBackSize.x, titleBackSize.y)) {
			titleBackAlpha = 0.5f;
			XMFLOAT2 spriteSize = titleBackSize;
			spriteSize.x *= 0.9f;
			spriteSize.y *= 0.9f;
			titleBack->SetSize(spriteSize);
			if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
				ground->SetAmbient({ 1, 1, 1 });
				celetialSphere->SetAmbient({ 1, 1, 1 });
				SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
				isTitleBack = true;
				isSelectedButton = true;
			}
		}
		else if (IsMouseHitSprite(mousePos, restart->GetPosition(), restartSize.x, restartSize.y)) {
			restartAlpha = 0.5f;
			XMFLOAT2 spriteSize = restartSize;
			spriteSize.x *= 0.9f;
			spriteSize.y *= 0.9f;
			restart->SetSize(spriteSize);
			if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
				ground->SetAmbient({ 1, 1, 1 });
				celetialSphere->SetAmbient({ 1, 1, 1 });
				SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
				isRestart = true;
				isSelectedButton = true;
			}
		}
	}

	if (SceneChangeEffect::GetIns()->GetIsSceneChange()) {
		if (isTitleBack) {
			SceneManager::SceneChange(SceneManager::Title);
		}
		else if (isRestart) {
			switch (SceneManager::GetStageNo())
			{
			case 1:
				SceneManager::SceneChange(SceneManager::Stage1_Rail);
				break;
			case 2:
				SceneManager::SceneChange(SceneManager::Stage2_Rail);
				break;
			default:
				SceneManager::SceneChange(SceneManager::Title);
				break;
			}
		}
	}
}