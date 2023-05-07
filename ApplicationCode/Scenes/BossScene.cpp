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

	postEffectNo_ = PostEffect::NORMAL;
	postEffectTime_ = 0;

	player_ = new BossScenePlayer;
	player_->Initialize(camera_);
	player_->SetBossScene(this);

	int32_t stageNo = 0;
	stageNo = SceneManager::GetStageNo();
	if (stageNo == 1) {
		LoadTextMessage("Stage1BossText.aid");
	}

	textWindow_ = Sprite::Create(ImageManager::TextWindow, { 580, 630 });
	textWindow_->SetAlpha(0.4f);
	textWindowSize_ = textWindow_->GetSize();
	textWindowSize_.y = 0;
	textWindow_->SetAnchorPoint({ 0.5f, 0.5f });
	faceWindow_ = Sprite::Create(ImageManager::FaceWindow, { 90, 630 });
	faceWindowSize_ = faceWindow_->GetSize();
	faceWindowSize_.y = 0;
	faceWindow_->SetAlpha(0.4f);
	faceWindow_->SetAnchorPoint({ 0.5f, 0.5f });
	for (int32_t i = 0; i < 3; i++) {
		opeNormal_[i] = Sprite::Create(ImageManager::OPE_NORMAL, { 90, 630 });
		opeNormal_[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeNormal_[i]->SetSize({ 160, 160 });
		opeNormal_[i]->SetColor({ 2, 2, 2 });
		opeNormal_[i]->SetAnchorPoint({ 0.5f, 0.5f });

		opeSurprise_[i] = Sprite::Create(ImageManager::OPE_SURPRISE, { 90, 630 });
		opeSurprise_[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeSurprise_[i]->SetSize({ 160, 160 });
		opeSurprise_[i]->SetColor({ 2, 2, 2 });
		opeSurprise_[i]->SetAnchorPoint({ 0.5f, 0.5f });

		opeSmile_[i] = Sprite::Create(ImageManager::OPE_SMILE, { 90, 630 });
		opeSmile_[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeSmile_[i]->SetSize({ 160, 160 });
		opeSmile_[i]->SetColor({ 2, 2, 2 });
		opeSmile_[i]->SetAnchorPoint({ 0.5f, 0.5f });
	}
	for (int32_t i = 0; i < 2; i++) {
		movieBarPos_[i] = { 600.0f, 710.0f * (float)i };
		movieBar_[i] = Sprite::Create(ImageManager::SceneChangeBar, movieBarPos_[i]);
		movieBar_[i]->SetSize({ 1680, 200 });
		movieBar_[i]->SetAnchorPoint({ 0.5f, 0.5f });
	}
	textAddTimer_ = 0;
	textSpeed_ = 1;
	//boss = new FirstBoss;
	//boss->Initialize(ModelManager::BossBody, { 0, 0, 0 });

	firstBoss_ = new FirstBoss;
	firstBoss_->Initialize("boss1_Body", {0, 0, 0});
	firstBoss_->SetBossScene(this);
	firstBoss_->SetPlayer(player_);

	pause_ = Sprite::Create(ImageManager::ImageName::Pause, { 640, 100 });
	pause_->SetAnchorPoint({ 0.5f, 0.5f });
	titleBack_ = Sprite::Create(ImageManager::ImageName::TitleBack, { 640, 300 });
	titleBack_->SetAnchorPoint({ 0.5f, 0.5f });
	titleBackSize_ = titleBack_->GetSize();
	back_ = Sprite::Create(ImageManager::ImageName::Back, { 640, 450 });
	back_->SetAnchorPoint({ 0.5f, 0.5f });
	backSize_ = back_->GetSize();
	scoreText_ = Sprite::Create(ImageManager::score, { 1180, 50 });
	scoreText_->SetAnchorPoint({ 0.5f, 0.5f });
	scoreText_->SetSize({ scoreText_->GetSize().x / 2.0f, scoreText_->GetSize().y / 2.0f });
	for (int32_t i = 0; i < 6; i++) {
		scoreNumber_[i] = Sprite::Create(ImageManager::scoreNumbers, { 1252 - ((float)i * 30), 100 });
		scoreNumber_[i]->SetAnchorPoint({ 0.5f, 0.5f });
		scoreNumber_[i]->SetTextureRect({ nine, 0.0f }, { 64, 64 });
		scoreNumber_[i]->SetSize({ 32, 32 });
	}
	operatorSize_ = { 160.0f, 0.0f };
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
	isTitleBack_ = false;
	isDead_ = false;

	movieTimer_ = 0;
	cameraPos_ = { 220.0f, 0.0f, 0.0f };
}

void BossScene::Update()
{
	playerBullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });
	bossBullets_.remove_if([](std::unique_ptr<EnemyBullet>& bossBullet) { return bossBullet->IsDead(); });
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
	postEffectNo_ = PostEffect::NORMAL;

	if (firstBoss_->GetIsMovie()) {
		if (firstBoss_->GetIsCameraMoveTiming() && firstBoss_->GetIsMovie()) {
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

	if (!isTextWindowOpen_) {
		closeWindowTimer_++;
		if (closeWindowTimer_ >= closeWindowTime) {
			closeWindowTimer_ = closeWindowTime;
		}
		textWindowSize_.y = Easing::easeInOut((float)closeWindowTimer_, (float)closeWindowTime, closeWindowSizeY, textWindowSize_.y);
		faceWindowSize_.y = Easing::easeInOut((float)closeWindowTimer_, (float)closeWindowTime, closeWindowSizeY, faceWindowSize_.y);
		operatorSize_.y = Easing::easeInOut((float)closeWindowTimer_, (float)closeWindowTime, closeWindowSizeY, operatorSize_.y);

		textWindow_->SetSize(textWindowSize_);
		faceWindow_->SetSize(faceWindowSize_);
		for (int32_t i = 0; i < 3; i++) {
			opeNormal_[i]->SetSize(operatorSize_);
		}
	}
	else if (isTextWindowOpen_) {
		closeWindowTimer_ = 0;
		openWindowTimer_++;
		if (openWindowTimer_ >= openWindowTime) {
			openWindowTimer_ = openWindowTime;
		}
		textWindowSize_.y = Easing::easeInOut((float)openWindowTimer_, (float)openWindowTime, openWindowSizeY, textWindowSize_.y);
		faceWindowSize_.y = Easing::easeInOut((float)openWindowTimer_, (float)openWindowTime, openWindowSizeY, faceWindowSize_.y);
		operatorSize_.y = Easing::easeInOut((float)openWindowTimer_, (float)openWindowTime, openWindowSizeY, operatorSize_.y);

		textWindow_->SetSize(textWindowSize_);
		faceWindow_->SetSize(faceWindowSize_);
		for (int32_t i = 0; i < 3; i++) {
			opeNormal_[i]->SetSize(operatorSize_);
			opeSurprise_[i]->SetSize(operatorSize_);
			opeSmile_[i]->SetSize(operatorSize_);
		}
	}

	if (!isPause_) {
		TextMessageUpdate();

		ground_->Update();
		celetialSphere_->Update();
		if (!firstBoss_->GetIsMovie()) {
			player_->Update();
		}

		if (player_->GetHPCount() <= noneHP && !isDead_) {
			XMVECTOR playerPos = player_->GetPlayerObj()->GetMatWorld().r[3];
			XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
			playerPos = XMVector3TransformCoord(playerPos, matVPV);

			XMFLOAT2 player2dPos = { playerPos.m128_f32[0], playerPos.m128_f32[1] };
			std::unique_ptr<Particle2d> new2DParticle = std::make_unique<Particle2d>();
			new2DParticle->Initialize(player2dPos, { 200, 200 }, 100, ImageManager::enemyDead, { 0.5f, 0.5f }, 8, { 0, 0 }, { 32, 32 });
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
			firstBoss_->Update(player_->GetPlayerObj()->GetMatWorld().r[3]);

			for (std::unique_ptr<PlayerBullet>& playerBullet : playerBullets_) {
				playerBullet->Update();
			}

			for (std::unique_ptr<Object3d>& building : buildings_) {
				building->Update();
			}

			for (std::unique_ptr<EnemyBullet>& bossBullet : bossBullets_) {
				bossBullet->Update();
			}

			for (const std::unique_ptr<PlayerBullet>& playerBullet : playerBullets_) {
				if (Collision::GetIns()->OBJSphereCollision(playerBullet->GetBulletObj(), firstBoss_->GetBossObj(), 1.0f, 100.0f)) {
					if (firstBoss_->GetBossHp() > 0) {
						score_ += 100;
						firstBoss_->OnCollision();
						playerBullet->OnCollision();
					}
				}

				if (!firstBoss_->GetIsLeftHandDead()) {
					if (Collision::GetIns()->OBJSphereCollision(playerBullet->GetBulletObj(), firstBoss_->GetLeftHandObj(), 1.0f, 30.0f)) {
						score_ += 100;
						firstBoss_->LeftHandOnCollision();
						playerBullet->OnCollision();
					}
				}

				if (!firstBoss_->GetIsRightHandDead()) {
					if (Collision::GetIns()->OBJSphereCollision(playerBullet->GetBulletObj(), firstBoss_->GetRightHandObj(), 1.0f, 30.0f)) {
						score_ += 100;
						firstBoss_->RightHandOnCollision();
						playerBullet->OnCollision();
					}
				}
			}

			for (const std::unique_ptr<EnemyBullet>& bossBullet : bossBullets_) {
				if (Collision::GetIns()->OBJSphereCollision(bossBullet->GetEnemyBulletObj(), player_->GetPlayerObj(), 2.0f, 5.0f)) {
					bossBullet->OnCollision();
					if (!player_->GetIsDamage() && player_->GetHPCount() > noneHP) {
						player_->OnCollision();
					}
				}
			}

			if (Collision::GetIns()->OBJSphereCollision(firstBoss_->GetLeftHandObj(), player_->GetPlayerObj(), 2.0f, 30.0f)) {
				if (!player_->GetIsDamage() && player_->GetHPCount() > noneHP) {
					player_->OnCollision();
				}
			}
			if (Collision::GetIns()->OBJSphereCollision(firstBoss_->GetRightHandObj(), player_->GetPlayerObj(), 2.0f, 30.0f)) {
				if (!player_->GetIsDamage() && player_->GetHPCount() > noneHP) {
					player_->OnCollision();
				}
			}
		}

	}
	else {
		XMFLOAT2 mousePos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };
		const float selectAlpha = 0.5f;
		const float normalAlpha = 1.0f;
		XMFLOAT2 selectSize;
		if (IsMouseHitSprite(mousePos, titleBack_->GetPosition(), titleBackSize_.x, titleBackSize_.y)) {
			selectSize = { titleBackSize_.x * 0.9f, titleBackSize_.y * 0.9f };
			titleBack_->SetSize(selectSize);
			titleBack_->SetAlpha(selectAlpha);
			if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
				isTitleBack_ = true;
				SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
			}
		}
		else {
			titleBack_->SetSize(titleBackSize_);
			titleBack_->SetAlpha(normalAlpha);
		}

		if (IsMouseHitSprite(mousePos, back_->GetPosition(), backSize_.x, backSize_.y)) {
			selectSize = { backSize_.x * 0.9f, backSize_.y * 0.9f };
			back_->SetSize(selectSize);
			back_->SetAlpha(selectAlpha);
			if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
				isPause_ = !isPause_;
			}
		}
		else {
			back_->SetSize(backSize_);
			back_->SetAlpha(normalAlpha);
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

	opeAnimeTimer_++;
	if (opeAnimeTimer_ >= opeAnimeTime) {
		opeAnimeTimer_ = 0;
		opeAnimeCount_++;
		if (opeAnimeCount_ >= 3) {
			opeAnimeCount_ = 0;
		}
	}

	if (isTextDraw_) {
		opeAnimeCount_ = 0;
		opeAnimeTimer_ = 0;
	}

	if (player_->GetIsDamage()) {
		postEffectNo_ = PostEffect::DAMAGE;
		postEffectTime_ = 60;
	}
	else if (player_->GetIsDash()) {
		postEffectNo_ = PostEffect::DASH;
		postEffectTime_ = 28;
	}
	else {
		postEffectNo_ = PostEffect::NORMAL;
		postEffectTime_ = 60;
	}

	isRoop = true;

	if (firstBoss_->GetIsMovieEffectTiming() && firstBoss_->GetIsMovie()) {
		postEffectNo_ = PostEffect::DASH;
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
	firstBoss_->Draw();
	for (std::unique_ptr<Object3d>& building : buildings_) {
		building->Draw();
	}
	for (std::unique_ptr<PlayerBullet>& playerBullet : playerBullets_) {
		playerBullet->Draw();
	}
	for (std::unique_ptr<EnemyBullet>& bossBullet : bossBullets_) {
		bossBullet->Draw();
	}
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	if (!firstBoss_->GetIsMovie()) {
		scoreText_->Draw();
		for (int32_t i = 0; i < 6; i++) {
			scoreNumber_[i]->Draw();
		}
	}
	for (int32_t i = 0; i < 2; i++) {
		if (firstBoss_->GetIsMovie()) {
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
		textWindow_->Draw();
		faceWindow_->Draw();
		opeNormal_[opeAnimeCount_]->Draw();
		firstBoss_->SpriteDraw();
	}
	Reticle::GetIns()->Draw();
	SceneChangeEffect::GetIns()->Draw();
	Sprite::PostDraw();

	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	if (!isPause_) {
		TextMessageDraw();
	}
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), (float)postEffectTime_, postEffectNo_, isRoop);
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
	firstBoss_->Finalize();
	safe_delete(firstBoss_);
	player_->Finalize();
	safe_delete(player_);
	safe_delete(scoreText_);
	safe_delete(light_);
	safe_delete(textDraw_);
	safe_delete(textWindow_);
	safe_delete(faceWindow_);
	for (int32_t i = 0; i < 3; i++) {
		safe_delete(opeNormal_[i]);
		safe_delete(opeSurprise_[i]);
		safe_delete(opeSmile_[i]);
	}
	for (int32_t i = 0; i < 2; i++) {
		safe_delete(movieBar_[i]);
	}
	for (int32_t i = 0; i < 6; i++) {
		safe_delete(scoreNumber_[i]);
	}
}

void BossScene::AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet)
{
	playerBullets_.push_back(std::move(playerBullet));
}

void BossScene::AddEnemyBullet(std::unique_ptr<EnemyBullet> bossBullet)
{
	bossBullets_.push_back(std::move(bossBullet));
}

void BossScene::LoadTextMessage(const std::string fileName)
{
	//ファイルストリーム
	std::ifstream file;
	textData_.str("");
	textData_.clear(std::stringstream::goodbit);

	const std::string directory = "Engine/Resources/GameData/";
	file.open(directory + fileName);
	if (file.fail()) {
		assert(0);
	}

	textData_ << file.rdbuf();

	file.close();
}

void BossScene::TextMessageUpdate()
{
	std::string line;
	std::string face;
	std::string messageData;
	std::wstring messageDataW;

	if (isMessageWait_) {
		if (isTextDraw_) {
			waitMessageTimer_--;
		}
		if (waitMessageTimer_ <= 0) {
			isMessageWait_ = false;
			textCount_ = 0;
			message_.clear();
			drawMessage_.clear();
		}
		return;
	}

	while (getline(textData_, line)) {
		std::istringstream line_stream(line);
		std::string word;
		//半角区切りで文字列を取得
		getline(line_stream, word, ' ');
		if (word == "#") {
			continue;
		}
		if (word == "OPEN") {
			isTextWindowOpen_ = true;
		}
		if (word == "FACE") {
			line_stream >> face;
			if (face == "OPE_NORMAL") {
				faceType_ = FaceGraphics::OPE_NORMALFACE;
			}
			else if (face == "OPE_SURPRISE") {
				faceType_ = FaceGraphics::OPE_SURPRISEFACE;
			}
			else if (face == "OPE_SMILE") {
				faceType_ = FaceGraphics::OPE_SMILEFACE;
			}
		}
		if (word == "TEXT") {
			line_stream >> messageData;
			messageDataW = StringToWstring(messageData);
			message_ = messageDataW;
		}
		if (word == "SPEED") {
			line_stream >> textSpeed_;
		}
		if (word == "WAIT") {
			isMessageWait_ = true;
			line_stream >> waitMessageTimer_;
			break;
		}
		if (word == "CLOSE") {
			isTextWindowOpen_ = false;
		}
	}
}

void BossScene::TextMessageDraw()
{
	if (textSpeed_ <= 0) {
		textSpeed_ = 1;
	}

	D2D1_RECT_F textDrawPos = {
		200, 560, 950, 700
	};

	textAddTimer_++;
	isTextDraw_ = false;
	if (textAddTimer_ >= textSpeed_) {
		textAddTimer_ = 0;
		if (textCount_ < message_.size()) {
			if (message_.substr(textCount_, 1) != L"/") {
				drawMessage_ += message_.substr(textCount_, 1);
			}
			else {
				drawMessage_ += L"\n";
			}
			textCount_++;
		}

		if (textCount_ >= message_.size()) {
			isTextDraw_ = true;
		}
	}

	textDraw_->Draw("meiryo", "white", drawMessage_, textDrawPos);
}

std::wstring BossScene::StringToWstring(const std::string& text)
{
	//文字サイズを取得
	int32_t iBufferSize = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, (wchar_t*)NULL, 0);
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];
	//SJISからwstringに変換
	MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, cpUCS2, iBufferSize);
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

	delete[] cpUCS2;

	return oRet;
}

void BossScene::SceneChange()
{
	if (firstBoss_->GetIsDead()) {
		SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
	}

	if (SceneChangeEffect::GetIns()->GetIsSceneChange()) {
		if (player_->GetIsDead()) {
			SceneManager::AddScore(score_);
			SceneManager::SceneChange(SceneManager::SceneName::GameOver);
		}
		else if (firstBoss_->GetIsDead()) {
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
