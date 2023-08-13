#include "ResultScene.h"

void ResultScene::Initialize()
{
	SceneChangeEffect::GetIns()->SetIsSceneChangeComplete(true);

	cameraPos_ = { -50, 0, 100 };
	cameraTargetPos_ = { 0, 0, 0 };

	camera_ = new Camera;
	camera_->SetEye(cameraPos_);
	camera_->SetTarget(cameraTargetPos_);

	score_ = Sprite::Create((UINT)ImageManager::ImageName::score, { 300, 100 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	for (int32_t i = 0; i < 6; i++) {
		scoreNumbers_[i] = Sprite::Create((UINT)ImageManager::ImageName::scoreNumbers, { 450 - ((float)i * 60), 250 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
		scoreNumbers_[i]->SetTextureRect({ nine, 0 }, { 64, 64 });
		scoreNumbers_[i]->SetSize({ 64, 64 });
	}
	titleBack_ = Button::CreateButton(ImageManager::ImageName::TitleBack, { 640, 600 }, { 256.0f, 128.0f }, 0.0f);

	scoreRollTimer_ = 0;
	for (int32_t i = 0; i < 6; i++) {
		scoreRollPos_[i] = { -640, 0 };
	}

	light_ = LightGroup::Create();
	for (int32_t i = 0; i < 3; i++) {
		light_->SetDirLightActive(0, true);
		light_->SetPointLightActive(i, false);
		light_->SetSpotLightActive(i, false);
	}
	light_->SetCircleShadowActive(0, true);
	Object3d::SetLight(light_);

	resultPlayer_ = Object3d::Create(ModelManager::GetIns()->GetModel("player_Normal"));
	playerScale_ = { 20, 20, 20 };
	playerPos_ = { -30, 0, -500 };
	playerRot_ = { 0, 0, 0 };
	resultPlayer_->SetScale(playerScale_);
	resultPlayer_->SetPosition(playerPos_);
	resultPlayer_->SetRotation(playerRot_);

	gun_ = Object3d::Create(ModelManager::GetIns()->GetModel("gun"));
	gun_->SetPosition(Vector3(0.9f, 0.6f, 1.2f));
	gun_->SetParent(resultPlayer_);

	ground_ = Object3d::Create(ModelManager::GetIns()->GetModel("ground"));
	groundPos_ = { 0, -50, 0 };
	ground_->SetPosition(groundPos_);
	groundScale_ = { 10, 10, 10 };
	ground_->SetScale(groundScale_);

	celetialSphere_ = Object3d::Create(ModelManager::GetIns()->GetModel("celetialSphere"));
	celetialSphere_->SetScale({ 15, 15, 15 });

	//PostEffectの初期化
	postEffect_ = new PostEffect();
	postEffect_->Initialize();
	postEffectNo_ = PostEffect::PostEffectNo::NORMAL;
}

void ResultScene::Update()
{
	const float scoreRollTime = 240.0f;
	const float fallTime = 120.0f;
	const XMFLOAT2 scoreSize = { 64, 64 };
	const float endPoint = 0;

	mousePos_ = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };

	light_->SetCircleShadowCasterPos(0, playerPos_);
	light_->SetDirLightDirection(0, { 0, -1, 0 });
	light_->SetCircleShadowDir(0, { 0, -1, 0 });
	light_->SetCircleShadowAtten(0, { 0.0f, 0.01f, 0.0f });
	light_->SetCircleShadowDistanceCasterLight(0, 1000.0f);
	light_->SetCircleShadowAngle(0, { 0.0f, 0.5f });
	//レティクル更新処理
	Reticle::GetIns()->Update();

	scoreRollTimer_++;
	if (scoreRollTimer_ >= scoreRollTime) {
		scoreRollTimer_ = scoreRollTime;
	}

	playerPos_.z = Easing::easeOut(scoreRollTimer_, fallTime, endPoint, playerPos_.z);

	camera_->SetTarget(cameraTargetPos_);
	resultPlayer_->SetPosition(playerPos_);

	for (int32_t i = 0; i < 6; i++) {
		scoreRollPos_[i].x = Easing::easeOut(scoreRollTimer_, scoreRollTime, (float)JudgeDigitNumber(SceneManager::GetScore(), i), scoreRollPos_[i].x);
	}
	for (int32_t i = 0; i < 6; i++) {
		scoreNumbers_[i]->SetTextureRect(scoreRollPos_[i], scoreSize);
	}

	resultPlayer_->Update();
	celetialSphere_->Update();
	ground_->Update();
	gun_->Update();

	if (waitTimer_++ >= waitTime) {
		titleBack_->Update();
		waitTimer_ = waitTime;
	}

	light_->Update();

	//シーン変更
	SceneChangeEffect::GetIns()->Update();
	SceneChange();
}

void ResultScene::Draw()
{
	//背景色
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };

	postEffect_->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//スプライト描画処理(背景)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	//background->Draw();
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	resultPlayer_->Draw();
	celetialSphere_->Draw();
	ground_->Draw();
	gun_->Draw();
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	score_->Draw();
	for (int32_t i = 0; i < 6; i++) {
		scoreNumbers_[i]->Draw();
	}
	titleBack_->Draw();
	Reticle::GetIns()->Draw();
	SceneChangeEffect::GetIns()->Draw();
	Sprite::PostDraw();

	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), 60, postEffectNo_, true);
	DirectXSetting::GetIns()->PostDraw();
}

void ResultScene::Finalize()
{
	safe_delete(postEffect_);
	safe_delete(score_);
	safe_delete(resultPlayer_);
	safe_delete(celetialSphere_);
	safe_delete(ground_);
	safe_delete(gun_);
	safe_delete(titleBack_);
	safe_delete(light_);
	for (int32_t i = 0; i < 6; i++) {
		safe_delete(scoreNumbers_[i]);
	}
}

void ResultScene::SceneChange()
{
	if (titleBack_->GetIsClick()) {
		SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
	}

	if (SceneChangeEffect::GetIns()->GetIsSceneChange()) {
		SceneManager::SceneChange(SceneManager::SceneName::Title);
	}
}
