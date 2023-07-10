#include "GameOverScene.h"

void GameOverScene::Initialize()
{
	cameraPos_ = { -50, 0, 100 };
	cameraTargetPos_ = { 0, 500, 0 };

	SceneChangeEffect::GetIns()->SetIsSceneChangeComplete(true);

	camera_ = new Camera;
	camera_->SetEye(cameraPos_);
	camera_->SetTarget(cameraTargetPos_);

	score_ = Sprite::Create((UINT)ImageManager::ImageName::score, { 300, 100 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	for (int32_t i = 0; i < 6; i++) {
		scoreNumbers_[i] = Sprite::Create((UINT)ImageManager::ImageName::scoreNumbers, { 450 - ((float)i * 60), 250 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
		scoreNumbers_[i]->SetTextureRect({ nine, 0 }, { 64, 64 });
		scoreNumbers_[i]->SetSize({ 64, 64 });
	}
	titleBack_ = Button::CreateButton(ImageManager::ImageName::TitleBack, { 840.0f, 600.0f }, { 256.0f, 128.0f }, 0.0f);
	restart_ = Button::CreateButton(ImageManager::ImageName::Restart, { 440.0f, 600.0f }, { 256.0f, 64.0f }, 0.0f);

	light_ = LightGroup::Create();
	for (int32_t i = 0; i < 3; i++) {
		light_->SetDirLightActive(i, false);
		light_->SetPointLightActive(i, false);
		light_->SetSpotLightActive(0, true);
	}
	light_->SetCircleShadowActive(0, true);
	Object3d::SetLight(light_);

	scoreRollTimer_ = 0;
	for (int32_t i = 0; i < 6; i++) {
		scoreRollPos_[i] = { -640, 0 };
	}

	resultPlayer_ = Object3d::Create(ModelManager::GetIns()->GetModel("player_Down"));
	playerScale_ = { 20, 20, 20 };
	playerPos_ = { -30, 500, 0 };
	playerRot_ = { 0, 0, 0 };
	resultPlayer_->SetScale(playerScale_);
	resultPlayer_->SetPosition(playerPos_);
	resultPlayer_->SetRotation(playerRot_);

	ground_ = Object3d::Create(ModelManager::GetIns()->GetModel("ground"));
	groundPos_ = { 0, -50, 0 };
	ground_->SetPosition(groundPos_);
	groundScale_ = { 10, 10, 10 };
	ground_->SetScale(groundScale_);
	ground_->SetAmbient({ 0, 0, 0 });

	celetialSphere_ = Object3d::Create(ModelManager::GetIns()->GetModel("celetialSphere"));
	celetialSphere_->SetAmbient({ 0, 0, 0 });
	celetialSphere_->SetScale({ 15, 15, 15 });

	//PostEffectの初期化
	postEffect_ = new PostEffect();
	postEffect_->Initialize();
	postEffectNo_ = PostEffect::PostEffectNo::DAMAGE;
}

void GameOverScene::Update()
{
	const XMFLOAT2 scoreSize = { 64, 64 };
	const float endPoint = 0;
	const float scoreRollTime = 60;
	const float fallTime = 120;
	mousePos_ = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };

	scoreRollTimer_++;
	if (scoreRollTimer_ >= scoreRollTime) {
		scoreRollTimer_ = scoreRollTime;
		isButtonSelectTiming_ = true;
	}

	if (isButtonSelectTiming_) {
		restart_->Update();
		titleBack_->Update();


		if (!isSelectedButton_) {
			if (titleBack_->GetIsClick()) {
				ground_->SetAmbient({ 1, 1, 1 });
				celetialSphere_->SetAmbient({ 1, 1, 1 });
				SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
				isTitleBack_ = true;
				isSelectedButton_ = true;
			}
			else if (restart_->GetIsClick()) {
				ground_->SetAmbient({ 1, 1, 1 });
				celetialSphere_->SetAmbient({ 1, 1, 1 });
				SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
				isRestart_ = true;
				isSelectedButton_ = true;
			}
		}
	}

	cameraTargetPos_.y = Easing::easeOut(scoreRollTimer_, fallTime, endPoint, cameraTargetPos_.y);
	playerPos_.y = Easing::easeOut(scoreRollTimer_, fallTime, endPoint, playerPos_.y);

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

	light_->Update();
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
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	score_->Draw();
	for (int32_t i = 0; i < 6; i++) {
		scoreNumbers_[i]->Draw();
	}
	titleBack_->Draw();
	restart_->Draw();
	Reticle::GetIns()->Draw();
	SceneChangeEffect::GetIns()->Draw();
	Sprite::PostDraw();

	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), 0, postEffectNo_);
	DirectXSetting::GetIns()->PostDraw();
}

void GameOverScene::Finalize()
{
	safe_delete(postEffect_);
	safe_delete(score_);
	safe_delete(resultPlayer_);
	safe_delete(celetialSphere_);
	safe_delete(ground_);
	safe_delete(titleBack_);
	safe_delete(restart_);
	safe_delete(light_);
	for (int32_t i = 0; i < 6; i++) {
		safe_delete(scoreNumbers_[i]);
	}
}

void GameOverScene::SceneChange()
{
	if (SceneChangeEffect::GetIns()->GetIsSceneChange()) {
		if (isTitleBack_) {
			SceneManager::SceneChange(SceneManager::SceneName::Title);
		}
		else if (isRestart_) {
			switch (SceneManager::GetStageNo())
			{
			case 1:
				if (SceneManager::GetIsBossScene()) {
					SceneManager::SceneChange(SceneManager::SceneName::Stage1_Boss);
				}
				else {
					SceneManager::SceneChange(SceneManager::SceneName::Stage1_Rail);
				}
				break;
			case 2:
				SceneManager::SceneChange(SceneManager::SceneName::Stage2_Rail);
				break;
			default:
				SceneManager::SceneChange(SceneManager::SceneName::Title);
				break;
			}
		}
	}
}