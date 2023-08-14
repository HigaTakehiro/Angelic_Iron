#include "Collision.h"
#include "BossScene.h"

using namespace DirectX;

void BossScene::Initialize()
{
	camera_ = new Camera;
	camera_->SetEye(XMFLOAT3(0, 100, 0));
	camera_->SetTarget(XMFLOAT3(0, 10, 0));
	SceneChangeEffect::GetIns()->SetIsSceneChangeComplete(true);
	SceneManager::SetIsBossScene(true);

	for (int32_t i = 0; i < 36; i++) {
		Vector3 pos = { 0, 20, 0 };
		Vector3 rot = { 0, 270, 0 };
		Vector3 scale = { 20, 20, 20 };
		float angle = 20;
		float length = 300;
		if (i > 17) {
			angle = 25;
			length = 500;
		}
		pos = MotionMath::CircularMotion({ 0, 0, 0 }, pos, angle * i, length, MotionMath::Y);
		pos.y = (float)(rand() % 20 - 30);
		rot.y -= angle * i;
		std::unique_ptr<Object3d> newBuilding;
		newBuilding = (std::unique_ptr<Object3d>)Object3d::Create(ModelManager::GetIns()->GetModel("building"));
		newBuilding->SetPosition(pos);
		newBuilding->SetRotation(rot);
		newBuilding->SetScale(scale);
		buildings_.push_back(std::move(newBuilding));
	}

	ground_ = Object3d::Create(ModelManager::GetIns()->GetModel("ground"));
	groundPos_ = { 0, -50, 0 };
	ground_->SetPosition(groundPos_);
	groundScale_ = { 10, 10, 10 };
	ground_->SetScale(groundScale_);

	celetialSphere_ = Object3d::Create(ModelManager::GetIns()->GetModel("celetialSphere"));
	celetialSphere_->SetPosition(spherePos_);
	celetialSphere_->SetScale(sphereScale_);

	postEffect_ = new PostEffect();
	postEffect_->Initialize();
	postEffect_->SetMask(1.2f);

	postEffectNo_ = PostEffect::PostEffectNo::NORMAL;
	postEffectTime_ = 0;

	bulletManager_ = new BulletManager();

	player_ = new BossScenePlayer;
	player_->Initialize(camera_);
	player_->SetBossScene(this);
	player_->SetBulletManager(bulletManager_);
	player_->Update();

	int32_t stageNo = 0;
	stageNo = SceneManager::GetStageNo();
	messageWindow_ = new MessageWindow();
	if (stageNo == 1) {
		messageWindow_->Initialize("Stage1BossText.aid");
		boss_ = new FirstBoss;
		boss_->Initialize("boss1_Body", { 0, 0, 0 });
		boss_->SetBossScene(this);
		boss_->SetPlayer(player_);
	}

	pause_ = Sprite::Create((UINT)ImageManager::ImageName::Pause, { 640, 100 });
	pause_->SetAnchorPoint({ 0.5f, 0.5f });
	titleBack_ = Button::CreateButton(ImageManager::ImageName::TitleBack, { 640, 300 }, { 256, 128 }, 0.0f);
	back_ = Button::CreateButton(ImageManager::ImageName::Back, { 640, 450 }, { 256, 128 }, 0.0f);
	scoreText_ = Sprite::Create((UINT)ImageManager::ImageName::score, { 1180, 50 });
	scoreText_->SetAnchorPoint({ 0.5f, 0.5f });
	scoreText_->SetSize({ scoreText_->GetSize().x / 2.0f, scoreText_->GetSize().y / 2.0f });
	for (int32_t i = 0; i < 6; i++) {
		scoreNumber_[i] = Sprite::Create((UINT)ImageManager::ImageName::scoreNumbers, { 1252 - ((float)i * 30), 100 });
		scoreNumber_[i]->SetAnchorPoint({ 0.5f, 0.5f });
		scoreNumber_[i]->SetTextureRect({ nine, 0.0f }, { 64, 64 });
		scoreNumber_[i]->SetSize({ 32, 32 });
	}
	for (int32_t i = 0; i < 2; i++) {
		movieBarPos_[i] = { 600.0f, 710.0f * (float)i };
		movieBar_[i] = Sprite::Create((UINT)ImageManager::ImageName::SceneChangeBar, movieBarPos_[i]);
		movieBar_[i]->SetSize({ 1680, 200 });
		movieBar_[i]->SetAnchorPoint({ 0.5f, 0.5f });
	}
	score_ = 0;

	light_ = LightGroup::Create();
	for (int32_t i = 0; i < 3; i++) {
		light_->SetDirLightActive(0, true);
		light_->SetPointLightActive(i, false);
		light_->SetSpotLightActive(i, false);
	}
	light_->SetCircleShadowActive(0, true);
	Object3d::SetLight(light_);

	isPause_ = false;
	isDead_ = false;

	movieTimer_ = 0;
	cameraPos_ = { 220.0f, 0.0f, 0.0f };

	player_->SetBulletManager(bulletManager_);
	boss_->SetBulletManager(bulletManager_);
}

void BossScene::Update()
{
	particles2d_.remove_if([](std::unique_ptr<Particle2d>& particle2d) {return particle2d->IsDelete(); });

	const int32_t delayTime = 0;
	const int32_t noneHP = 0;
	const float closeWindowSizeY = 0.0f;
	const float openWindowSizeY = 160.0f;
	const Vector3 movieCameraPos = { 240.0f, 30.0f, 0.0f };
	const Vector3 initCameraPos = { 250.0f, -20.0f, 0.0f };
	const Vector3 movieCameraTarget = { 0.0f, 30.0f, 0.0f };
	const Vector3 initCameraTarget = { 0.0f, 0.0f, 0.0f };
	const int32_t cameraMoveTime = 60;

	XMFLOAT3 playerPos = { player_->GetPlayerObj()->GetMatWorld().r[3].m128_f32[0], player_->GetPlayerObj()->GetMatWorld().r[3].m128_f32[1], player_->GetPlayerObj()->GetMatWorld().r[3].m128_f32[2] };
	light_->SetCircleShadowCasterPos(0, playerPos);
	light_->SetDirLightDirection(0, { 0, -1, 0 });
	light_->SetCircleShadowDir(0, { 0, -1, 0 });
	light_->SetCircleShadowAtten(0, { 0.0f, 0.01f, 0.0f });
	light_->SetCircleShadowDistanceCasterLight(0, 1000.0f);
	light_->SetCircleShadowAngle(0, { 0.0f, 0.5f });
	//レティクル更新処理
	Reticle::GetIns()->Update();
	postEffectNo_ = PostEffect::PostEffectNo::NORMAL;

	if (boss_->GetIsMovie()) {
		if (boss_->GetIsCameraMoveTiming() && boss_->GetIsMovie()) {
			movieTimer_++;
			float timeRate = min((float)movieTimer_ / (float)cameraMoveTime, 1.0f);
			cameraPos_ = easeIn(movieCameraPos, initCameraPos, timeRate);
			Vector3 cameraTarget = easeIn(movieCameraTarget, initCameraTarget, timeRate);
			movieBarPos_[0].y = Easing::easeIn((float)movieTimer_, (float)cameraMoveTime, -180.0f, movieBarPos_[0].y);
			movieBarPos_[1].y = Easing::easeIn((float)movieTimer_, (float)cameraMoveTime, 900.0f, movieBarPos_[1].y);
			camera_->SetEye(cameraPos_);
			camera_->SetTarget(cameraTarget);
			for (int32_t i = 0; i < 2; i++) {
				movieBar_[i]->SetPosition(movieBarPos_[i]);
			}
		}
		else {
			camera_->SetEye(movieCameraPos);
			camera_->SetTarget(movieCameraTarget);
		}
	}

	if (KeyInput::GetIns()->TriggerKey(DIK_ESCAPE)) {
		isPause_ = !isPause_;
	}

	for (int32_t i = 0; i < 6; i++) {
		scoreNumber_[i]->SetTextureRect({ (float)JudgeDigitNumber(score_ + SceneManager::GetScore(), i), 0 }, { 64, 64 });
	}

	if (!isPause_) {
		messageWindow_->Update();
		colManager_->Update();

		ground_->Update();
		celetialSphere_->Update();
		if (!boss_->GetIsMovie()) {
			player_->Update();
		}

		if (player_->GetHPCount() <= noneHP && !isDead_) {
			XMVECTOR playerPos = player_->GetPlayerObj()->GetMatWorld().r[3];
			XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
			playerPos = XMVector3TransformCoord(playerPos, matVPV);

			XMFLOAT2 player2dPos = { playerPos.m128_f32[0], playerPos.m128_f32[1] };
			std::unique_ptr<Particle2d> new2DParticle = std::make_unique<Particle2d>();
			new2DParticle->Initialize(player2dPos, { 200, 200 }, 100, ImageManager::ImageName::enemyDead, { 0.5f, 0.5f }, 8, { 0, 0 }, { 32, 32 });
			particles2d_.push_back(std::move(new2DParticle));
			isDead_ = true;
			SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
		}

		if (player_->GetIsLeftDash()) {
			postEffect_->SetBlurCenter({ +0.5f, -0.5f });
		}
		else if (player_->GetIsRightDash()) {
			postEffect_->SetBlurCenter({ -1.5f, -0.5f });
		}

		for (std::unique_ptr<Particle2d>& particle2d : particles2d_) {
			particle2d->Update();
		}

		if (player_->GetHPCount() > noneHP) {
			boss_->Update(player_->GetPlayerObj()->GetMatWorld().r[3]);

			for (std::unique_ptr<Object3d>& building : buildings_) {
				building->Update();
			}
			
			bulletManager_->Update(score_);
		}

	}
	else {
		titleBack_->Update();
		back_->Update();

		if (titleBack_->GetIsClick()) {
			isTitleBack_ = true;
		}
		if (back_->GetIsClick()) {
			isPause_ = false;
		}
	}

	//ライト更新処理
	light_->Update();

	//シーン変更
	SceneChangeEffect::GetIns()->Update();
	SceneChange();
}

void BossScene::Draw()
{
	//背景色
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };
	bool isRoop = false;

	if (player_->GetIsDamage()) {
		postEffectNo_ = PostEffect::PostEffectNo::DAMAGE;
		postEffectTime_ = 60;
	}
	else if (player_->GetIsDash()) {
		postEffectNo_ = PostEffect::PostEffectNo::DASH;
		postEffectTime_ = 28;
	}
	else {
		postEffectNo_ = PostEffect::PostEffectNo::NORMAL;
		postEffectTime_ = 60;
	}

	isRoop = true;

	if (boss_->GetIsMovieEffectTiming() && boss_->GetIsMovie()) {
		postEffectNo_ = PostEffect::PostEffectNo::DASH;
		postEffect_->SetBlurCenter({ -0.5f, -0.5f });
		postEffect_->SetMask(0.2f);
		postEffectTime_ = 60;
		isRoop = false;
	}
	else {
		postEffect_->SetMask(0.7f);
	}

	postEffect_->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//スプライト描画処理(背景)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	ground_->Draw();
	celetialSphere_->Draw();
	player_->Draw();
	boss_->Draw();
	for (std::unique_ptr<Object3d>& building : buildings_) {
		building->Draw();
	}
	bulletManager_->Draw();
	Object3d::PostDraw();

	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	if (!isPause_) {
		messageWindow_->TextMessageDraw(false);
	}
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), (float)postEffectTime_, postEffectNo_, isRoop);
	//ポストエフェクトを掛けないスプライト描画(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	if (!boss_->GetIsMovie()) {
		scoreText_->Draw();
		for (int32_t i = 0; i < 6; i++) {
			scoreNumber_[i]->Draw();
		}
	}
	for (int32_t i = 0; i < 2; i++) {
		if (boss_->GetIsMovie()) {
			movieBar_[i]->Draw();
		}
	}
	player_->SpriteDraw();
	if (isPause_) {
		pause_->Draw();
		titleBack_->Draw();
		back_->Draw();
	}
	for (std::unique_ptr<Particle2d>& particle2d : particles2d_) {
		particle2d->Draw();
	}
	if (!isPause_) {
		messageWindow_->SpriteDraw();
		boss_->SpriteDraw();
	}
	Reticle::GetIns()->Draw();
	SceneChangeEffect::GetIns()->Draw();
	Sprite::PostDraw();
	DirectXSetting::GetIns()->PostDraw();
}

void BossScene::Finalize()
{
	safe_delete(ground_);
	safe_delete(celetialSphere_);
	safe_delete(camera_);
	safe_delete(postEffect_);
	safe_delete(pause_);
	safe_delete(titleBack_);
	safe_delete(back_);
	boss_->Finalize();
	safe_delete(boss_);
	player_->Finalize();
	safe_delete(player_);
	safe_delete(scoreText_);
	safe_delete(light_);
	safe_delete(bulletManager_);
	safe_delete(messageWindow_);
	for (int32_t i = 0; i < 2; i++) {
		safe_delete(movieBar_[i]);
	}
	for (int32_t i = 0; i < 6; i++) {
		safe_delete(scoreNumber_[i]);
	}
	colManager_->Finalize();
}

void BossScene::SceneChange()
{
	if (boss_->GetIsDead()) {
		SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
	}

	if (SceneChangeEffect::GetIns()->GetIsSceneChange()) {
		if (player_->GetIsDead()) {
			SceneManager::AddScore(score_);
			SceneManager::SceneChange(SceneManager::SceneName::GameOver);
		}
		else if (boss_->GetIsDead()) {
			SceneManager::AddScore(score_);
			SceneManager::SetIsBossScene(false);
			SceneManager::SceneChange(SceneManager::SceneName::Result);
		}
		else if (isTitleBack_) {
			SceneManager::SetIsBossScene(false);
			SceneManager::SceneChange(SceneManager::SceneName::Title);
		}
	}
}
