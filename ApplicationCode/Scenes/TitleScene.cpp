#include "TitleScene.h"
#include <random>

void TitleScene::Initialize()
{
	//SoundManager::GetIns()->PlayBGM(SoundManager::TITLE, true, 0.1f);
	SceneChangeEffect::GetIns()->SetIsSceneChangeComplete(true);

	cameraPos_ = { -100, 50, 200 };
	cameraTargetPos_ = { 0, 500, 0 };

	camera_ = std::make_unique<Camera>();
	camera_->SetEye(cameraPos_);
	camera_->SetTarget(cameraTargetPos_);

	titlePos_ = { 300, 200 };
	startButtonPos_ = { 640, 550 };
	stage1Pos_ = { -300, 100 };
	manualButtonPos_ = { -300, 500 };
	closePos_ = { 640, 550 };
	allowPos_ = { 1240, 330 };
	manualPos_ = { 640, 300 };

	pageNumber_ = 1;
	prePageNumber_ = 1;

	const XMFLOAT2 spriteCenter = { 0.5f, 0.5f };
	title_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::title, titlePos_);
	title_->SetAnchorPoint(spriteCenter);
	startButton_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::StartButton, startButtonPos_);
	startButton_->SetAnchorPoint(spriteCenter);
	stage1_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::Stage1, stage1Pos_);
	stage1_->SetAnchorPoint(spriteCenter);
	manualButton_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::ManualButton, manualButtonPos_);
	manualButton_->SetAnchorPoint(spriteCenter);
	manual_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::Manual, manualPos_);
	manual_->SetAnchorPoint(spriteCenter);
	manual2_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::Manual_2, { manualPos_.x * (pageNumber_ + 2), manualPos_.y });
	manual2_->SetAnchorPoint(spriteCenter);
	allow_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::Allow, allowPos_);
	allow_->SetAnchorPoint(spriteCenter);
	allow_->SetRotation(90.0f);
	close_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::Close, closePos_);
	close_->SetAnchorPoint(spriteCenter);

	startButtonSize_ = startButton_->GetSize();
	stage1Size_ = stage1_->GetSize();
	manualButtonSize_ = manualButton_->GetSize();
	manualSize_ = { 0, 0 };
	manualMaxSize_ = manual_->GetSize();
	closeSize_ = close_->GetSize();
	allowSize_ = allow_->GetSize();
	startTimer_ = 0;

	light_ = LightGroup::UniquePtrCreate();
	for (int32_t i = 0; i < 3; i++) {
		light_->SetDirLightActive(0, true);
		light_->SetPointLightActive(i, false);
		light_->SetSpotLightActive(i, false);
	}
	//light_->SetCircleShadowActive(0, true);
	Object3d::SetLight(light_.get());

	jsonLoader_ = std::make_unique<JsonLoader>();
	jsonLoader_->StageDataLoadandSet("TitleScene_Stage");

	titlePlayer_ = Object3d::UniquePtrCreate(ModelManager::GetIns()->GetModel("player_Stand"));
	playerScale_ = { 20, 20, 20 };
	playerPos_ = { -30, 50, 0 };
	playerRot_ = { 0, 0, 0 };
	titlePlayer_->SetScale(playerScale_);
	titlePlayer_->SetPosition(playerPos_);
	titlePlayer_->SetRotation(playerRot_);

	mousePos_ = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };
	stageSelectTimer_ = 0;

	postEffect_ = std::make_unique<PostEffect>();
	postEffect_->Initialize();

	postEffectNo_ = PostEffect::PostEffectNo::NORMAL;
	particle_ = ParticleManager::UniquePtrCreate(DirectXSetting::GetIns()->GetDev(), camera_.get());

	shadow_ = new ShadowMap();
	shadow_->Initialize();

	debugText_.Initialize(0);
}

void TitleScene::Update()
{
	mousePos_ = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };

	static Vector3 lightPos = { 0, 0, 0 };
	static Vector3 lightDir = { 1, 0, 0 };

	char lightPosText[256];
	sprintf_s(lightPosText, "PlayerWPos = (x : %f, y : %f, z : %f)", lightPos.x, lightPos.y, lightPos.z);
	debugText_.Print(lightPosText, 0, 0, 2);

	std::random_device rnd;
	std::mt19937_64 seed(rnd());
	std::uniform_int_distribution<> randomNumber(-300, 300);

	XMFLOAT3 cloudPos;
	cloudPos.x = (float)randomNumber(seed);
	cloudPos.y = 200.0f;
	cloudPos.z = (float)randomNumber(seed);
	particle_->Add(300, cloudPos, { 0, 0, 0.2f }, { 0, 0, 0 }, 30.0f, 30.0f, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, 0.5f, 0.5f);

	light_->SetDirLightDirection(0, { 0, -1, 0 });

	titlePlayer_->SetPosition(playerPos_);

	titlePlayer_->Update();
	particle_->Update();
	light_->Update();
	//レティクル更新処理
	Reticle::GetIns()->Update();
	Reticle::GetIns()->SetIsSelectReticle(false);

	const float cameraSpeed = 10.0f;

	camera_->SetEye(cameraPos_);
	//testSquare->SetPosition(lightPos);

	if (!isStageSelectMenu_ && IsMouseHitSprite(mousePos_, startButtonPos_, 256, 128)) {
		XMFLOAT2 spriteSize = startButtonSize_;
		spriteSize.x *= 0.9f;
		spriteSize.y *= 0.9f;
		startButton_->SetSize(spriteSize);
		startButton_->SetAlpha(selectAlpha);
		Reticle::GetIns()->SetIsSelectReticle(true);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::LEFT_CLICK)) {
			isStageSelectMenu_ = true;
		}
	}
	else {
		startButton_->SetSize(startButtonSize_);
		startButton_->SetAlpha(initAlpha);
	}

	if (IsMouseHitSprite(mousePos_, stage1Pos_, 270, 128)) {
		XMFLOAT2 spriteSize = stage1Size_;
		spriteSize.x *= 0.9f;
		spriteSize.y *= 0.9f;
		stage1_->SetSize(spriteSize);
		stage1_->SetAlpha(selectAlpha);
		Reticle::GetIns()->SetIsSelectReticle(true);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::LEFT_CLICK) && !isStageChoice_) {
			isStage1_ = true;
			isStageChoice_ = true;
		}
	}
	else {
		stage1_->SetSize(stage1Size_);
		stage1_->SetAlpha(initAlpha);
	}

	if (IsMouseHitSprite(mousePos_, manualButtonPos_, 300, 128)) {
		XMFLOAT2 spriteSize = manualButtonSize_;
		spriteSize.x *= 0.9f;
		spriteSize.y *= 0.9f;
		manualButton_->SetSize(spriteSize);
		manualButton_->SetAlpha(selectAlpha);
		Reticle::GetIns()->SetIsSelectReticle(true);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::LEFT_CLICK) && !isStageChoice_) {
			isManual_ = true;
		}
	}
	else {
		manualButton_->SetSize(manualButtonSize_);
		manualButton_->SetAlpha(initAlpha);
	}

	if (IsMouseHitSprite(mousePos_, closePos_, 270, 128) && isManual_) {
		XMFLOAT2 spriteSize = closeSize_;
		spriteSize.x *= 0.9f;
		spriteSize.y *= 0.9f;
		close_->SetSize(spriteSize);
		close_->SetAlpha(selectAlpha);
		Reticle::GetIns()->SetIsSelectReticle(true);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::LEFT_CLICK)) {
			isManual_ = false;
		}
	}
	else {
		close_->SetSize(closeSize_);
		close_->SetAlpha(initAlpha);
	}

	if (IsMouseHitSprite(mousePos_, allowPos_, 64, 64) && isManual_) {
		XMFLOAT2 spriteSize = allowSize_;
		spriteSize.x *= 0.9f;
		spriteSize.y *= 0.9f;
		float spriteRot = 90;
		allow_->SetSize(spriteSize);
		allow_->SetAlpha(selectAlpha);
		Reticle::GetIns()->SetIsSelectReticle(true);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::LEFT_CLICK) && pageNumber_ == 1) {
			pageNumber_ += 1;
		}
		else if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::LEFT_CLICK) && pageNumber_ == 2) {
			pageNumber_ -= 1;
		}

		if (pageNumber_ != 1) {
			allowPos_.x = 50;
			spriteRot = -90;
		}
		else {
			allowPos_.x = 1240;
			spriteRot = 90;
		}

		allow_->SetPosition(allowPos_);
		allow_->SetRotation(spriteRot);
	}
	else {
		allow_->SetSize(allowSize_);
		allow_->SetAlpha(initAlpha);
	}

	if (isStageSelectMenu_) {
		const float outPos = -300;
		const float comePos = 200;
		stageSelectTimer_++;
		if (stageSelectTimer_ >= manualComeTime) {
			stageSelectTimer_ = manualComeTime;
		}
		cameraTargetPos_.y = Easing::easeOut((float)stageSelectTimer_, (float)stage1ComeTime, 1, cameraTargetPos_.y);
		titlePos_.x = Easing::easeInBack((float)stageSelectTimer_, (float)titleOutTime, outPos, titlePos_.x, 1);
		stage1Pos_.x = Easing::easeIn((float)stageSelectTimer_, (float)stage1ComeTime, comePos, stage1Pos_.x);
		manualButtonPos_.x = Easing::easeIn((float)stageSelectTimer_, (float)manualComeTime, comePos, manualButtonPos_.x);

		camera_->SetTarget(cameraTargetPos_);
		title_->SetPosition(titlePos_);
		stage1_->SetPosition(stage1Pos_);
		manualButton_->SetPosition(manualButtonPos_);
	}

	if (isManual_) {
		const float openWidth = manualMaxSize_.x;
		const float openHeight = manualMaxSize_.y;
		const float manualOutPos = -640;
		const float manualInPos = 640;
		const float outPos = -300;

		stageSelectTimer_ = titleOutTime;
		stage1Pos_.x = outPos;
		manualButtonPos_.x = outPos;

		manualTimer_++;
		manualSlideTimer_++;
		if (manualTimer_ >= manualOpenTime) {
			manualTimer_ = manualOpenTime;
		}
		if (manualSlideTimer_ >= manualSlideTime) {
			manualSlideTimer_ = manualSlideTime;
			isNextPage_ = false;
			isPrevPage_ = false;
		}
		manualSize_.x = Easing::easeOut((float)manualTimer_, (float)manualOpenTime, openWidth, manualSize_.x);
		manualSize_.y = Easing::easeOut((float)manualTimer_, (float)manualOpenTime, openHeight, manualSize_.y);

		if (pageNumber_ != prePageNumber_) {
			isNextPage_ = false;
			isPrevPage_ = false;
			manualSlideTimer_ = 0;
			if (prePageNumber_ < pageNumber_) {
				isNextPage_ = true;
				manualPos_.x = manualInPos;
			}
			else {
				isPrevPage_ = true;
				manualPos_.x = manualOutPos;
			}
			prePageNumber_ = pageNumber_;
		}
		if (isNextPage_) {
			manualPos_.x = Easing::easeOut((float)manualSlideTimer_, (float)manualSlideTime, manualOutPos, manualPos_.x);
		}
		else if (isPrevPage_) {
			manualPos_.x = Easing::easeOut((float)manualSlideTimer_, (float)manualSlideTime, manualInPos, manualPos_.x);
		}

		manual_->SetPosition(manualPos_);
		manual2_->SetPosition({ manualPos_.x + (manualInPos * 2), manualPos_.y });
		manual_->SetSize(manualSize_);
	}
	else {
		manualTimer_ = 0;
		manualSize_ = { 0.0f, 0.0f };
	}

	shadow_->Update(titlePlayer_.get());
	jsonLoader_->Update();

	if (isStageChoice_) {
		SoundManager::GetIns()->StopBGM(SoundManager::BGMKey::TITLE);
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

	if (postEffectNo_ == PostEffect::PostEffectNo::DASH) {
		postEffect_->SetBlurCenter({ -0.5f, -0.5f });
		postEffect_->SetMask(0.0f);
	}

	postEffect_->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//スプライト描画処理(背景)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	shadow_->Draw();
	titlePlayer_->Draw();
	//jsonLoader_->Draw();
	particle_->Draw(DirectXSetting::GetIns()->GetCmdList());
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	if (isManual_) {
		manual_->Draw();
		manual2_->Draw();
		allow_->Draw();
		close_->Draw();
	}

	if (isStageSelectMenu_ && !isManual_ && !isStageChoice_) {
		stage1_->Draw();
		manualButton_->Draw();
	}

	if (!isStageSelectMenu_) {
		startButton_->Draw();
	}
	title_->Draw();
	//debugText_.DrawAll(DirectXSetting::GetIns()->GetCmdList());
	Reticle::GetIns()->Draw();
	SceneChangeEffect::GetIns()->Draw();
	Sprite::PostDraw();

	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	static D2D1_RECT_F rectangle2 = D2D1::RectF(
		0, 500, 1280, 720
	);

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo_, true);
	DirectXSetting::GetIns()->PostDraw();

}

void TitleScene::Finalize()
{
	safe_delete(shadow_);
	jsonLoader_->Finalize();
}

void TitleScene::SceneChange()
{
	//シーン切り替え
	//ステージ選択フラグが立っていれば
	if (isStageChoice_) {
		if (startTimer_ <= startTime) {
			startTimer_++;
		}
		//開始演出時間が半分過ぎたら
		if (startTimer_ >= startTime / 2.0f) {
			//ブラーをかける
			postEffectNo_ = PostEffect::PostEffectNo::DASH;
			//パーティクルを発生させる
			//乱数上限
			const int32_t randMax = 18;
			//パーティクル生成時間
			int32_t particleLife = 3;
			//加速度
			Vector3 acc = { 0.0f, 0.0f, 0.0f };
			//初期アルファ値
			Vector3 initAlpha = { 0.0f, 0.0f, 0.6f };
			//最終的なアルファ値
			Vector3 endAlpha = { 1.0f, 1.0f, 1.0f };
			//最終的な大きさ
			float endScale = 0.0f;

			//プレイヤーのワールド行列からパーティクルの生成位置を求める
			XMVECTOR playerPos_ = { 0.0f, 1.2f, -1.0f };
			playerPos_ = XMVector3TransformCoord(playerPos_, titlePlayer_->GetMatWorld());
			Vector3 thrusterPos = playerPos_;

			for (int32_t i = 0; i < 10; i++) {
				float thrusterPower = (float)(rand() % randMax);
				thrusterPower *= -0.1f;
				float startScale = (float)(rand() % (randMax - 2));
				XMVECTOR playerBack = { 0.0f, 0.0f, thrusterPower };
				playerBack = XMVector3TransformNormal(playerBack, titlePlayer_->GetMatWorld());
				Vector3 thrusterDir = playerBack;
				particle_->Add(
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
		float timeRate = min((float)startTimer_ / (float)startTime, 1.0f);
		//線分補間用座標
		Vector3 point[3];
		point[0] = { -30, 50, 0 };
		point[1] = { -30.0f, 50.0f, 200.0f };
		point[2] = { -30, 300, 200 };

		//弧を描くように移動させる
		Vector3 easingPointA = easeIn(point[0], point[1], timeRate);
		Vector3 easingPointB = easeIn(point[1], point[2], timeRate);
		playerPos_ = easeIn(easingPointA, easingPointB, timeRate);

		//カメラ位置を変更する
		cameraPos_.y = Easing::easeIn((float)startTimer_, (float)startTime / 2, 3, cameraPos_.y);
		cameraPos_.z = Easing::easeIn((float)startTimer_, (float)startTime / 2, -150, cameraPos_.z);
		//プレイヤー座標を更新する
		titlePlayer_->SetPosition(playerPos_);

		//シーン切り替え演出開始フラグを立てる
		if (startTimer_ >= startTime) {
			SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
		}
		//シーンを切り替える
		if (SceneChangeEffect::GetIns()->GetIsSceneChange()) {
			if (isStage1_) {
				SceneManager::SceneChange(SceneManager::SceneName::Stage1_Rail);
			}
		}
	}
}