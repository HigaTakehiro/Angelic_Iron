#include "ResultScene.h"

void ResultScene::Initialize()
{
	SceneChangeEffect::GetIns()->SetIsSceneChangeComplete(true);

	cameraPos = { -50, 0, 100 };
	cameraTargetPos = { 0, 0, 0 };

	camera = new Camera;
	camera->SetEye(cameraPos);
	camera->SetTarget(cameraTargetPos);

	score = Sprite::Create(ImageManager::ImageName::score, { 300, 100 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	for (int i = 0; i < 6; i++) {
		scoreNumbers[i] = Sprite::Create(ImageManager::scoreNumbers, { 450 - ((float)i * 60), 250 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
		scoreNumbers[i]->SetTextureRect({ nine, 0 }, { 64, 64 });
		scoreNumbers[i]->SetSize({ 64, 64 });
	}
	titleBack = Sprite::Create(ImageManager::TitleBack, { 640, 600 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	titleBackSize = titleBack->GetSize();
	titleBackAlpha = 1.0f;

	scoreRollTimer = 0;
	for (int i = 0; i < 6; i++) {
		scoreRollPos[i] = { -640, 0 };
	}

	light = LightGroup::Create();
	for (int i = 0; i < 3; i++) {
		light->SetDirLightActive(0, true);
		light->SetPointLightActive(i, false);
		light->SetSpotLightActive(i, false);
	}
	light->SetCircleShadowActive(0, true);
	Object3d::SetLight(light);

	resultPlayer = Object3d::Create(ModelManager::GetIns()->GetModel("player_Normal"));
	playerScale = { 20, 20, 20 };
	playerPos = { -30, 0, -500 };
	playerRot = { 0, 0, 0 };
	resultPlayer->SetScale(playerScale);
	resultPlayer->SetPosition(playerPos);
	resultPlayer->SetRotation(playerRot);

	gun = Object3d::Create(ModelManager::GetIns()->GetModel("gun"));
	gun->SetPosition(Vector3(0.9f, 0.6f, 1.2f));
	gun->SetParent(resultPlayer);

	ground = Object3d::Create(ModelManager::GetIns()->GetModel("ground"));
	groundPos = { 0, -50, 0 };
	ground->SetPosition(groundPos);
	groundScale = { 10, 10, 10 };
	ground->SetScale(groundScale);

	celetialSphere = Object3d::Create(ModelManager::GetIns()->GetModel("celetialSphere"));
	celetialSphere->SetScale({ 15, 15, 15 });

	//PostEffectの初期化
	postEffect = new PostEffect();
	postEffect->Initialize();
	postEffectNo = PostEffect::NORMAL;
}

void ResultScene::Update()
{
	const float scoreRollTime = 240.0f;
	const float fallTime = 120.0f;
	const XMFLOAT2 scoreSize = { 64, 64 };
	const float endPoint = 0;

	mousePos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };

	light->SetCircleShadowCasterPos(0, playerPos);
	light->SetDirLightDirection(0, { 0, -1, 0 });
	light->SetCircleShadowDir(0, { 0, -1, 0 });
	light->SetCircleShadowAtten(0, { 0.0f, 0.01f, 0.0f });
	light->SetCircleShadowDistanceCasterLight(0, 1000.0f);
	light->SetCircleShadowAngle(0, { 0.0f, 0.5f });
	//レティクル更新処理
	Reticle::GetIns()->Update();

	scoreRollTimer++;
	if (scoreRollTimer >= scoreRollTime) {
		scoreRollTimer = scoreRollTime;
	}

	playerPos.z = Easing::easeOut(scoreRollTimer, fallTime, endPoint, playerPos.z);

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
	gun->Update();

	titleBack->SetAlpha(titleBackAlpha);
	titleBack->SetSize(titleBackSize);
	titleBackAlpha = 1.0f;

	light->Update();

	//シーン変更
	SceneChangeEffect::GetIns()->Update();
	SceneChange();
}

void ResultScene::Draw()
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
	gun->Draw();
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	score->Draw();
	for (int i = 0; i < 6; i++) {
		scoreNumbers[i]->Draw();
	}
	titleBack->Draw();
	Reticle::GetIns()->Draw();
	SceneChangeEffect::GetIns()->Draw();
	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect->Draw(DirectXSetting::GetIns()->GetCmdList(), 60, postEffectNo, true);
	DirectXSetting::GetIns()->PostDraw();
}

void ResultScene::Finalize()
{
	safe_delete(postEffect);
	safe_delete(score);
	safe_delete(resultPlayer);
	safe_delete(celetialSphere);
	safe_delete(ground);
	safe_delete(gun);
	safe_delete(titleBack);
	safe_delete(light);
	for (int i = 0; i < 6; i++) {
		safe_delete(scoreNumbers[i]);
	}
}

void ResultScene::SceneChange()
{
	if (IsMouseHitSprite(mousePos, titleBack->GetPosition(), titleBackSize.x, titleBackSize.y)) {
		titleBackAlpha = 0.5f;
		XMFLOAT2 spriteSize = titleBackSize;
		spriteSize.x *= 0.9f;
		spriteSize.y *= 0.9f;
		titleBack->SetSize(spriteSize);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
			SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
		}
	}

	if (SceneChangeEffect::GetIns()->GetIsSceneChange()) {
		SceneManager::SceneChange(SceneManager::Title);
	}
}
