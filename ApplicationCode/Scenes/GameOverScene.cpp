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
	titleBack_ = Sprite::Create((UINT)ImageManager::ImageName::TitleBack, { 840.0f, 600.0f }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	titleBackAlpha_ = 1.0f;
	titleBackSize_ = titleBack_->GetSize();
	restart_ = Sprite::Create((UINT)ImageManager::ImageName::Restart, { 440.0f, 600.0f }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	restartAlpha_ = 1.0f;
	restartSize_ = restart_->GetSize();
	restartSize_.x /= 2;
	restartSize_.y /= 2;

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
	const float scoreRollTime = 240;
	const float fallTime = 120;
	mousePos_ = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };

	scoreRollTimer_++;
	if (scoreRollTimer_ >= scoreRollTime) {
		scoreRollTimer_ = scoreRollTime;
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

	titleBack_->SetAlpha(titleBackAlpha_);
	titleBack_->SetSize(titleBackSize_);
	restart_->SetAlpha(restartAlpha_);
	restart_->SetSize(restartSize_);
	titleBackAlpha_ = 1.0f;
	restartAlpha_ = 1.0f;

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
	if (!isSelectedButton_) {
		titleBack_->Draw();
		restart_->Draw();
	}
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
	if (!isSelectedButton_) {
		if (IsMouseHitSprite(mousePos_, titleBack_->GetPosition(), titleBackSize_.x, titleBackSize_.y)) {
			titleBackAlpha_ = 0.5f;
			XMFLOAT2 spriteSize = titleBackSize_;
			spriteSize.x *= 0.9f;
			spriteSize.y *= 0.9f;
			titleBack_->SetSize(spriteSize);
			if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::LEFT_CLICK)) {
				ground_->SetAmbient({ 1, 1, 1 });
				celetialSphere_->SetAmbient({ 1, 1, 1 });
				SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
				isTitleBack_ = true;
				isSelectedButton_ = true;
			}
		}
		else if (IsMouseHitSprite(mousePos_, restart_->GetPosition(), restartSize_.x, restartSize_.y)) {
			restartAlpha_ = 0.5f;
			XMFLOAT2 spriteSize = restartSize_;
			spriteSize.x *= 0.9f;
			spriteSize.y *= 0.9f;
			restart_->SetSize(spriteSize);
			if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::LEFT_CLICK)) {
				ground_->SetAmbient({ 1, 1, 1 });
				celetialSphere_->SetAmbient({ 1, 1, 1 });
				SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
				isRestart_ = true;
				isSelectedButton_ = true;
			}
		}
	}

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