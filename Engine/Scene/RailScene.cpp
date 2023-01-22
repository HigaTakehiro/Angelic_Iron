#include "RailScene.h"
#include "FBXObject3d.h"
#include <algorithm>
#include <fstream>

void RailScene::Initialize() {

	//SoundManager::GetIns()->PlayBGM(SoundManager::STAGE1_RAIL, true, 0.2f);
	isSceneChangeComplete = true;
	SceneChangeInitialize();

	//カメラ初期化
	camera = new Camera;
	camera->SetEye(XMFLOAT3(50, 1, -100));
	camera->SetTarget(XMFLOAT3(50, 0, 0));
	railCamera = new RailCamera;

	debugText.Initialize(debugTextNumber);

	background = Sprite::Create(ImageManager::ImageName::background, { 0, 0 });
	pause = Sprite::Create(ImageManager::ImageName::Pause, { 640, 100 });
	pause->SetAnchorPoint({ 0.5f, 0.5f });
	titleBack = Sprite::Create(ImageManager::ImageName::TitleBack, { 640, 300 });
	titleBack->SetAnchorPoint({ 0.5f, 0.5f });
	titleBackSize = titleBack->GetSize();
	back = Sprite::Create(ImageManager::ImageName::Back, { 640, 450 });
	back->SetAnchorPoint({ 0.5f, 0.5f });
	backSize = back->GetSize();
	restart = Sprite::Create(ImageManager::Restart, { 640, 600 });
	restart->SetAnchorPoint({ 0.5f, 0.5f });
	restartSize = restart->GetSize();
	restartSize.x /= 2;
	restartSize.y /= 2;
	scoreSprite = Sprite::Create(ImageManager::score, { 1180, 50 });
	scoreSprite->SetAnchorPoint({ 0.5f, 0.5f });
	scoreSprite->SetSize({ scoreSprite->GetSize().x / 2.0f, scoreSprite->GetSize().y / 2.0f });
	textWindow = Sprite::Create(ImageManager::TextWindow, { 580, 630 });
	textWindow->SetAlpha(0.4f);
	textWindowSize = textWindow->GetSize();
	textWindowSize.y = 0;
	textWindow->SetAnchorPoint({ 0.5f, 0.5f });
	faceWindow = Sprite::Create(ImageManager::FaceWindow, { 90, 630 });
	faceWindowSize = faceWindow->GetSize();
	faceWindowSize.y = 0;
	faceWindow->SetAlpha(0.4f);
	faceWindow->SetAnchorPoint({ 0.5f, 0.5f });
	operatorSize = { 160, 0 };
	for (int i = 0; i < 3; i++) {
		opeNormal[i] = Sprite::Create(ImageManager::OPE_NORMAL, { 90, 630 });
		opeNormal[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeNormal[i]->SetSize({ 160, 160 });
		opeNormal[i]->SetColor({ 2, 2, 2 });
		opeNormal[i]->SetAnchorPoint({ 0.5f, 0.5f });

		opeSurprise[i] = Sprite::Create(ImageManager::OPE_SURPRISE, { 90, 630 });
		opeSurprise[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeSurprise[i]->SetSize({ 160, 160 });
		opeSurprise[i]->SetColor({ 2, 2, 2 });
		opeSurprise[i]->SetAnchorPoint({ 0.5f, 0.5f });

		opeSmile[i] = Sprite::Create(ImageManager::OPE_SMILE, { 90, 630 });
		opeSmile[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeSmile[i]->SetSize({ 160, 160 });
		opeSmile[i]->SetColor({ 2, 2, 2 });
		opeSmile[i]->SetAnchorPoint({ 0.5f, 0.5f });
	}
	for (int i = 0; i < 6; i++) {
		scoreNumber[i] = Sprite::Create(ImageManager::scoreNumbers, { 1252 - ((float)i * 30), 100 });
		scoreNumber[i]->SetAnchorPoint({ 0.5f, 0.5f });
		scoreNumber[i]->SetTextureRect({ nine, 0.0f }, { 64, 64 });
		scoreNumber[i]->SetSize({ 32, 32 });
	}

	light = LightGroup::Create();
	for (int i = 0; i < 3; i++) {
		light->SetDirLightActive(0, true);
		light->SetPointLightActive(i, false);
		light->SetSpotLightActive(i, false);
	}
	light->SetCircleShadowActive(0, true);
	Object3d::SetLight(light);

	ground = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Ground));
	groundPos = { 0, -50, 0 };
	ground->SetPosition(groundPos);
	groundScale = { 10, 10, 10 };
	ground->SetScale(groundScale);
	ground->SetAmbient({ 1, 1, 1 });

	celetialSphere = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::CelestialSphere));
	celetialSphere->SetPosition(spherePos);
	celetialSphere->SetScale(sphereScale);

	bombParticle = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);
	enemyParticle = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);

	for (int i = 0; i < 90; i++) {
		Vector3 pos = { 0, 20, 0 };
		Vector3 rot = { 0, 270, 0 };
		Vector3 scale = { 5, 5, 5 };
		float angle = 20;
		float length = 100;
		if (i > 17) {
			angle = 25;
			length = 200;
		}
		if (i > 35) {
			angle = 20;
			length = 300;
		}
		if (i > 53) {
			angle = 22;
			length = 400;
		}
		if (i > 71) {
			angle = 20;
			length = 500;
		}
		pos = MotionMath::GetIns()->CircularMotion({ 0, 0, 0 }, pos, angle * i, length, MotionMath::Y);
		pos.y = rand() % 20 - 40;
		rot.y -= angle * i;
		std::unique_ptr<Object3d> newBuilding;
		newBuilding = (std::unique_ptr<Object3d>)Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Building));
		newBuilding->SetPosition(pos);
		newBuilding->SetRotation(rot);
		newBuilding->SetScale(scale);
		buildings.push_back(std::move(newBuilding));
	}

	player = new Player;
	player->Initialize(camera, clearTime);
	player->SetRailScene(this);

	int stageNo;
	stageNo = SceneManager::GetStageNo();
	if (stageNo == 1) {
		LoadRailPoint("Stage1RailPoints.aid");
		LoadEnemyData("Stage1EnemyData.aid");
		LoadTextMessage("Stage1RailText.aid");
	}
	else if (stageNo == 2) {
		LoadRailPoint("Stage2RailPoints.aid");
		LoadEnemyData("Stage2EnemyData.aid");
	}

	//FBXの初期化
	//FBXObject3d::SetCamera(camera);
	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(ModelManager::GetIns()->GetFBXModel(ModelManager::Test));
	object1->SetScale({ 1.0f, 1.0f, 1.0f });
	object1->PlayAnimation();

	railCamera->SetStartTime(GetTickCount64());

	//PostEffectの初期化
	postEffect = new PostEffect();
	postEffect->Initialize();

	postEffectNo = PostEffect::NORMAL;

	score = 0;

	//ゲームシーン用変数の初期化
	//isDead = false;
	//isClear = false;
	//isWait = false;

	textAddTimer = 0;
	textSpeed = 1;
	textCount = 0;
	isTextDraw = false;

	clearTimer = clearTime;

	referenceCount = std::chrono::steady_clock::now();

	faceType = FaceGraphics::OPE_NORMALFACE;

}

void RailScene::Update() {
	// DirectX毎フレーム処理　ここから
	const int32_t noneHP = 0;
	const float closeWindowSizeY = 0.0f;
	const float openWindowSizeY = 160.0f;
	//SoundManager::GetIns()->PlayBGM(SoundManager::STAGE1_RAIL, true, 0.2f);

	enemies.remove_if([](std::unique_ptr<BaseEnemy>& enemy) {return enemy->GetIsDead(); });
	enemyBullets.remove_if([](std::unique_ptr<EnemyBullet>& enemyBullet) { return enemyBullet->IsDead(); });
	playerBullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });
	particles2d.remove_if([](std::unique_ptr<Particle2d>& particle) {return particle->IsDelete(); });
	bombs.remove_if([](std::unique_ptr<Bomb>& bomb) {return bomb->GetIsDead(); });

	light->SetCircleShadowCasterPos(0, { player->GetPlayerObject()->GetMatWorld().r[3].m128_f32[0], player->GetPlayerObject()->GetMatWorld().r[3].m128_f32[1], player->GetPlayerObject()->GetMatWorld().r[3].m128_f32[2] });
	light->SetDirLightDirection(0, { 0, -1, 0 });
	light->SetCircleShadowDir(0, { 0, -1, 0 });
	light->SetCircleShadowAtten(0, { 0.0f, 0.01f, 0.0f });
	light->SetCircleShadowDistanceCasterLight(0, 1000.0f);
	light->SetCircleShadowAngle(0, { 0.0f, 0.5f });

	opeAnimeTimer++;
	if (opeAnimeTimer >= opeAnimeTime) {
		opeAnimeTimer = 0;
		opeAnimeCount++;
		if (opeAnimeCount >= 3) {
			opeAnimeCount = 0;
		}
	}

	if (isTextDraw) {
		opeAnimeCount = 0;
		opeAnimeTimer = 0;
	}

	char xPos[256];
	char yPos[256];
	char isSlowCheck[256];
	sprintf_s(xPos, "PlayerWPos = (x : %f, y : %f, z : %f)", player->GetPlayerPos().x, player->GetPlayerPos().y, player->GetPlayerPos().z);
	sprintf_s(yPos, "aim3DPos = (x : %f, y : %f, z : %f)", player->Get3dAimPos().x, player->Get3dAimPos().y, player->Get3dAimPos().z);
	if (!player->GetIsBomb()) {
		sprintf_s(isSlowCheck, "false");
	}
	else {
		sprintf_s(isSlowCheck, "true");
	}
	debugText.Print(xPos, 0, 0, 2.0f);
	debugText.Print(yPos, 0, 50, 2.0f);
	debugText.Print(isSlowCheck, 0, 100, 2.0f);

	if (KeyInput::GetIns()->TriggerKey(DIK_ESCAPE)) {
		isPause = !isPause;
	}

	EnemyDataUpdate();
	if (!isTextWindowOpen) {
		openWindowTimer = 0;
		closeWindowTimer++;
		if (closeWindowTimer >= closeWindowTime) {
			closeWindowTimer = closeWindowTime;
		}
		textWindowSize.y = Easing::GetIns()->easeInOut(closeWindowTimer, closeWindowTime, closeWindowSizeY, textWindowSize.y);
		faceWindowSize.y = Easing::GetIns()->easeInOut(closeWindowTimer, closeWindowTime, closeWindowSizeY, faceWindowSize.y);
		operatorSize.y = Easing::GetIns()->easeInOut(closeWindowTimer, closeWindowTime, closeWindowSizeY, operatorSize.y);

		textWindow->SetSize(textWindowSize);
		faceWindow->SetSize(faceWindowSize);
		for (int i = 0; i < 3; i++) {
			opeNormal[i]->SetSize(operatorSize);
			opeSurprise[i]->SetSize(operatorSize);
			opeSmile[i]->SetSize(operatorSize);
		}
	}
	else if (isTextWindowOpen) {
		closeWindowTimer = 0;
		openWindowTimer++;
		if (openWindowTimer >= openWindowTime) {
			openWindowTimer = openWindowTime;
		}
		textWindowSize.y = Easing::GetIns()->easeInOut(openWindowTimer, openWindowTime, openWindowSizeY, textWindowSize.y);
		faceWindowSize.y = Easing::GetIns()->easeInOut(openWindowTimer, openWindowTime, openWindowSizeY, faceWindowSize.y);
		operatorSize.y = Easing::GetIns()->easeInOut(openWindowTimer, openWindowTime, openWindowSizeY, operatorSize.y);

		textWindow->SetSize(textWindowSize);
		faceWindow->SetSize(faceWindowSize);
		for (int i = 0; i < 3; i++) {
			opeNormal[i]->SetSize(operatorSize);
			opeSurprise[i]->SetSize(operatorSize);
			opeSmile[i]->SetSize(operatorSize);
		}
	}

	if (railCamera->GetIsEnd()) {
		clearTimer--;
	}
	if (clearTimer <= 0) {
		isClear = true;
		isSceneChangeStart = true;
	}

	for (int i = 0; i < 6; i++) {
		scoreNumber[i]->SetTextureRect({ (float)JudgeDigitNumber(score, i), 0 }, { 64, 64 });
	}

	if (player->GetHPCount() <= noneHP && !isPlayerDead) {
		XMVECTOR playerPos = { player->GetPlayerPos().x, player->GetPlayerPos().y, player->GetPlayerPos().z };
		XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
		playerPos = XMVector3TransformCoord(playerPos, matVPV);

		XMFLOAT2 player2dPos = { playerPos.m128_f32[0] - 150, playerPos.m128_f32[1] - 140 };
		std::unique_ptr<Particle2d> new2DParticle = std::make_unique<Particle2d>();
		new2DParticle->Initialize(player2dPos, { 200, 200 }, 80, ImageManager::enemyDead, { 0.5f, 0.5f }, 8, { 0, 0 }, { 32, 32 });
		particles2d.push_back(std::move(new2DParticle));
		isPlayerDead = true;
		SoundManager::GetIns()->StopBGM(SoundManager::STAGE1_RAIL);
	}

	if (player->GetIsDead()) {
		isDead = true;
		isSceneChangeStart = true;
	}

	float delayCount = 0.0f;

	if (player->GetIsBomb()) {
		delayCount = 3.0f;
	}

	if (!isPause) {
		TextMessageUpdate();

		celetialSphere->Update();
		ground->Update();
		for (std::unique_ptr<Object3d>& building : buildings) {
			building->Update();
		}

		if (player->GetHPCount() > 0) {
			if (!railCamera->GetIsEnd()) {
				railCamera->Update(delayCount);
			}
			for (std::unique_ptr<BaseEnemy>& enemy : enemies) {
				enemy->Update(delayCount);
				if (enemy->GetHP() <= 0) {
					XMFLOAT3 enemyPos;
					enemyPos.x = enemy->GetEnemyObj()->GetMatWorld().r[3].m128_f32[0];
					enemyPos.y = enemy->GetEnemyObj()->GetMatWorld().r[3].m128_f32[1];
					enemyPos.z = enemy->GetEnemyObj()->GetMatWorld().r[3].m128_f32[2];
					enemyParticle->Add(30, enemyPos, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.02f, 0.0f }, 5.0f, 0.0f);
				}
			}
			for (std::unique_ptr<Bomb>& bomb : bombs) {
				bomb->Update();
				bombParticle->Add(20, { bomb->GetBullet()->GetMatWorld().r[3].m128_f32[0],
					bomb->GetBullet()->GetMatWorld().r[3].m128_f32[1],
					bomb->GetBullet()->GetMatWorld().r[3].m128_f32[2] },
					{ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
					3.0f, 0.0f, { 1.0f, 1.0f, 1.0f },
					{ 1.0f, 1.0f, 1.0f }, 1.0f, 0.0f);
			}
		}

		enemyParticle->Update();
		bombParticle->Update();

		for (std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets) {
			enemyBullet->Update(delayCount);
		}
		for (std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
			playerBullet->Update(delayCount);
		}
		for (std::unique_ptr<Particle2d>& particle2d : particles2d) {
			particle2d->Update();
		}

		for (const std::unique_ptr<BaseEnemy>& enemy : enemies) {
			for (const std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
				if (Collision::GetIns()->OBJSphereCollision(playerBullet->GetBulletObj(), enemy->GetEnemyObj(), 1.0f, 5.0f)) {
					score += 100;
					enemy->OnCollision();
					playerBullet->OnCollision();
				}
			}
		}

		for (const std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets) {
			if (Collision::GetIns()->OBJSphereCollision(enemyBullet->GetEnemyBulletObj(), player->GetPlayerObject(), 1.0f, 2.0f)) {
				if (!player->GetIsDamage() && player->GetHPCount() > noneHP) {
					player->OnCollision();
				}
				enemyBullet->OnCollision();
				railCamera->SetIsDamage();
			}
		}

		for (const std::unique_ptr<BaseEnemy>& enemy : enemies) {
			for (const std::unique_ptr<Bomb>& bomb : bombs) {
				if (Collision::GetIns()->OBJSphereCollision(enemy->GetEnemyObj(), bomb->GetBullet(), 5.0f, 1.0f)) {
					score += 100;
					enemy->OnCollision();
					for (int i = 0; i < 10; i++) {
						XMFLOAT3 pos = {
							bomb->GetBullet()->GetMatWorld().r[3].m128_f32[0],
							bomb->GetBullet()->GetMatWorld().r[3].m128_f32[1],
							bomb->GetBullet()->GetMatWorld().r[3].m128_f32[2]
						};
						pos.x += rand() % 40 - 20;
						pos.y += rand() % 40 - 20;
						pos.z += rand() % 40 - 20;

						const float rnd_vel = 0.1f;
						XMFLOAT3 vel{};
						vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
						vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
						vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

						XMFLOAT3 acc{};
						const float rnd_acc = 0.01f;
						acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
						acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
						acc.z = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;

						bombParticle->Add(30, pos, vel, acc, 8.0f, 0.0f, { 0.6f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
					}
					bomb->OnCollision();

				}
			}
		}

		for (std::unique_ptr<BaseEnemy>& enemy : enemies) {
			XMVECTOR raticle2D = { enemy->GetEnemyObj()->GetMatWorld().r[3] }; //ワールド座標
			XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
			raticle2D = XMVector3TransformCoord(raticle2D, matViewProjectionViewport); //スクリーン座標

			DirectX::XMFLOAT2 spritePos = { raticle2D.m128_f32[0], raticle2D.m128_f32[1] };

			XMFLOAT2 targetCheckHitPos = { spritePos.x - player->GetAimPos().x, spritePos.y - player->GetAimPos().y };

			if (IsTargetCheck(spritePos, player->GetAimPos()) && player->GetIsBomb()) {
				enemy->SetTarget(true);
			}

			if (enemy->GetIsDead() && enemy->GetHP() <= 0) {
				std::unique_ptr<Particle2d> new2DParticle = std::make_unique<Particle2d>();
				new2DParticle->Initialize(spritePos, { 50, 50 }, 24, ImageManager::enemyDead, { 0.5f, 0.5f }, 8, { 0, 0 }, { 32, 32 });
				particles2d.push_back(std::move(new2DParticle));
			}
		}

		player->Update(railCamera->GetIsEnd());
	}
	else {
		SoundManager::GetIns()->StopBGM(SoundManager::STAGE1_RAIL);
		XMFLOAT2 mousePos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };
		const float selectAlpha = 0.5f;
		const float normalAlpha = 1.0f;
		XMFLOAT2 selectSize;
		if (IsMouseHitSprite(mousePos, titleBack->GetPosition(), titleBackSize.x, titleBackSize.y)) {
			selectSize = { titleBackSize.x * 0.9f, titleBackSize.y * 0.9f };
			titleBack->SetSize(selectSize);
			titleBack->SetAlpha(selectAlpha);
			if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
				isTitleBack = true;
				isSceneChangeStart = true;
			}
		}
		else {
			titleBack->SetSize(titleBackSize);
			titleBack->SetAlpha(normalAlpha);
		}

		if (IsMouseHitSprite(mousePos, back->GetPosition(), backSize.x, backSize.y)) {
			selectSize = { backSize.x * 0.9f, backSize.y * 0.9f };
			back->SetSize(selectSize);
			back->SetAlpha(selectAlpha);
			if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
				isPause = !isPause;
			}
		}
		else {
			back->SetSize(backSize);
			back->SetAlpha(normalAlpha);
		}

		if (IsMouseHitSprite(mousePos, restart->GetPosition(), restartSize.x, restartSize.y)) {
			selectSize = { restartSize.x * 0.9f, restartSize.y * 0.9f };
			restart->SetSize(selectSize);
			restart->SetAlpha(selectAlpha);
			if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
				isRestart = true;
				isSceneChangeStart = true;
			}
		}
		else {
			restart->SetSize(restartSize);
			restart->SetAlpha(normalAlpha);
		}
	}

	light->Update();
	//object1->Update();

	if (isSceneChangeComplete) {
		SceneChangeCompleteEffect();
	}
	if (isSceneChangeStart) {
		SceneChangeEffect();
	}

	//シーン切り替え
	if (isSceneChange) {
		if (isDead && !isClear) {
			SceneManager::AddScore(score);
			SceneManager::SceneChange(SceneManager::GameOver);
		}
		else if (isClear && !isDead) {
			SceneManager::AddScore(score);
			if (SceneManager::GetStageNo() == 1) {
				SceneManager::SceneChange(SceneManager::Stage1_Boss);
			}
			else if (SceneManager::GetStageNo() == 2) {
				SceneManager::SceneChange(SceneManager::Stage2_Boss);
			}
			SoundManager::GetIns()->StopBGM(SoundManager::STAGE1_RAIL);
		}
		else if (isTitleBack) {
			SceneManager::SceneChange(SceneManager::Title);
		}
		else if (isRestart) {
			if (SceneManager::GetStageNo() == 1) {
				SceneManager::SceneChange(SceneManager::Stage1_Rail);
			}
			else if (SceneManager::GetStageNo() == 2) {
				SceneManager::SceneChange(SceneManager::Stage2_Rail);
			}
		}
	}

	if (KeyInput::GetIns()->TriggerKey(DIK_N)) {
		SceneManager::AddScore(score);
		SceneManager::SceneChange(SceneManager::Stage1_Boss);
	}

	//player->SetEnemies(enemies);
}

void RailScene::Draw() {
	//背景色
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };
	bool isRoop = false;

	if (player->GetIsDamage()) {
		postEffectNo = PostEffect::DAMAGE;
	}
	else {
		postEffectNo = PostEffect::NORMAL;
		isRoop = true;
	}

	if (player->GetIsBomb()) {
		postEffectNo = PostEffect::SLOW;
		isRoop = false;
	}

	postEffect->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//スプライト描画処理(背景)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	//background->Draw();
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	ground->Draw();
	celetialSphere->Draw();

	if (!isDead) {
		player->ObjectDraw();
	}
	for (std::unique_ptr<BaseEnemy>& enemy : enemies) {
		enemy->Draw();
	}
	for (std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets) {
		enemyBullet->Draw();
	}
	for (std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
		playerBullet->Draw();
	}
	for (std::unique_ptr<Bomb>& bomb : bombs) {
		bomb->Draw();
	}
	for (std::unique_ptr<Object3d>& building : buildings) {
		building->Draw();
	}
	enemyParticle->Draw(DirectXSetting::GetIns()->GetCmdList());
	bombParticle->Draw(DirectXSetting::GetIns()->GetCmdList());
	//object1->Draw(DirectXSetting::GetIns()->GetCmdList());
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	scoreSprite->Draw();
	for (int i = 0; i < 6; i++) {
		scoreNumber[i]->Draw();
	}
	if (!isPause) {
		textWindow->Draw();
		faceWindow->Draw();
		switch (faceType) {
		case FaceGraphics::OPE_NORMALFACE:
			opeNormal[opeAnimeCount]->Draw();
			break;
		case FaceGraphics::OPE_SURPRISEFACE:
			opeSurprise[opeAnimeCount]->Draw();
			break;
		case FaceGraphics::OPE_SMILEFACE:
			opeSmile[opeAnimeCount]->Draw();
			break;
		}
	}

	player->SpriteDraw();
	for (std::unique_ptr<BaseEnemy>& enemy : enemies) {
		enemy->SpriteDraw();
	}
	for (std::unique_ptr<Particle2d>& particle2d : particles2d) {
		particle2d->Draw();
	}
	if (isPause) {
		pause->Draw();
		titleBack->Draw();
		back->Draw();
		restart->Draw();

	}
	//debugText.DrawAll(DirectXSetting::GetIns()->GetCmdList());
	SceneChangeEffectDraw();
	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	if (!isPause) {
		TextMessageDraw();
	}
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo, isRoop);
	DirectXSetting::GetIns()->PostDraw();
}

void RailScene::Finalize() {
	player->Finalize();
	safe_delete(player);
	safe_delete(ground);
	safe_delete(background);
	safe_delete(celetialSphere);
	safe_delete(camera);
	safe_delete(object1);
	safe_delete(mapchip);
	safe_delete(railCamera);
	safe_delete(postEffect);
	safe_delete(pause);
	safe_delete(titleBack);
	safe_delete(back);
	safe_delete(restart);
	safe_delete(scoreSprite);
	safe_delete(light);
	safe_delete(bombParticle);
	safe_delete(enemyParticle);
	safe_delete(textDraw);
	safe_delete(textWindow);
	safe_delete(faceWindow);
	for (int i = 0; i < 3; i++) {
		safe_delete(opeNormal[i]);
		safe_delete(opeSurprise[i]);
		safe_delete(opeSmile[i]);
	}
	for (int i = 0; i < 6; i++) {
		safe_delete(scoreNumber[i]);
	}
	//FbxLoader::GetInstance()->Finalize();
}

void RailScene::LoadEnemyData(const std::string filename) {
	//ファイルストリーム
	std::ifstream file;
	enemyData.str("");
	enemyData.clear(std::stringstream::goodbit);
	enemies.clear();

	const std::string directory = "Engine/Resources/GameData/";
	file.open(directory + filename);
	if (file.fail()) {
		assert(0);
	}

	enemyData << file.rdbuf();

	file.close();
}

void RailScene::EnemyDataUpdate() {
	std::string line;
	Vector3 pos{};
	Vector3 rot{};
	Vector3 scale{};
	std::string type;
	bool isPos = false;
	bool isRot = false;
	bool isStyle = false;

	if (isWait) {
		waitTimer--;
		if (waitTimer <= 0) {
			isWait = false;
		}
		return;
	}

	while (getline(enemyData, line)) {
		std::istringstream line_stream(line);
		std::string word;
		//半角区切りで文字列を取得
		getline(line_stream, word, ' ');
		if (word == "#") {
			continue;
		}
		if (word == "Pos") {
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;
			isPos = true;
		}
		if (word == "Rot") {
			line_stream >> rot.x;
			line_stream >> rot.y;
			line_stream >> rot.z;
			isRot = true;
		}
		if (word == "Type") {
			line_stream >> type;
			isStyle = true;
		}
		if (word == "Wait") {
			isWait = true;
			line_stream >> waitTimer;

			break;
		}

		if (isPos && isRot && isStyle) {

			if (type == "STR") {
				std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<StraightEnemy>();
				newEnemy->Initialize(ModelManager::Enemy, pos, rot);
				newEnemy->SetRailScene(this);
				enemies.push_back(std::move(newEnemy));
			}
			if (type == "HOM") {
				std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<HomingEnemy>();
				newEnemy->Initialize(ModelManager::Enemy, pos, rot);
				newEnemy->SetRailScene(this);
				newEnemy->SetPlayer(player);
				enemies.push_back(std::move(newEnemy));
			}

			isPos = false;
			isRot = false;
			isStyle = false;
		}
	}
}

void RailScene::AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet) {
	enemyBullets.push_back(std::move(enemyBullet));
}

void RailScene::AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet) {
	playerBullets.push_back(std::move(playerBullet));
}

void RailScene::AddBomb(std::unique_ptr<Bomb> bomb) {
	bombs.push_back(std::move(bomb));
}

void RailScene::LoadRailPoint(const std::string filename) {
	//ファイルストリーム
	std::ifstream file;
	std::stringstream railcameraPointsData;
	railcameraPointsData.str("");
	railcameraPointsData.clear(std::stringstream::goodbit);
	points.clear();

	const std::string directory = "Engine/Resources/GameData/";
	file.open(directory + filename);
	if (file.fail()) {
		assert(0);
	}

	railcameraPointsData << file.rdbuf();

	file.close();

	std::string line;
	Vector3 pos{};
	Vector3 rot{};
	rot = { 0, 0, 0 };
	Vector3 startPos{};
	bool isStart = false;
	bool isEnd = false;
	bool isRoop = false;
	bool isCameraRoop = false;
	bool isPoint = false;
	bool isTime = false;
	bool isRot = false;
	float splineTime = 0;
	int stringCount = 0;

	while (getline(railcameraPointsData, line)) {
		std::istringstream line_stream(line);
		std::string word;
		//半角区切りで文字列を取得
		getline(line_stream, word, ' ');
		if (word == "#") {
			continue;
		}
		if (word == "Start") {
			line_stream >> startPos.x;
			line_stream >> startPos.y;
			line_stream >> startPos.z;
			isStart = true;
		}

		if (word == "Pos") {
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;
			isPoint = true;
		}

		if (word == "End") {
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;
			isEnd = true;
		}

		if (word == "Roop") {
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;
			isRoop = true;
		}

		if (word == "Time") {
			line_stream >> splineTime;
			isTime = true;
		}

		if (word == "Rot") {
			line_stream >> rot.x;
			line_stream >> rot.y;
			line_stream >> rot.z;
			isRot = true;
		}

		if (isStart) {
			points.push_back(startPos);
			points.push_back(startPos);
			isStart = false;
		}
		else if (isEnd) {
			points.push_back(pos);
			points.push_back(pos);
			isEnd = false;
		}
		else if (isRoop) {
			points.push_back(pos);
			points.push_back(startPos);
			points.push_back(startPos);
			isRoop = false;
			isCameraRoop = true;
		}
		else if (isTime) {
			splineTime *= 1000;
			isTime = false;
		}
		else if (isPoint) {
			points.push_back(pos);
		}

		stringCount++;
	}

	assert(splineTime != 0);
	railCamera->Initialize(startPos, rot, points, splineTime, isCameraRoop);

}

void RailScene::LoadTextMessage(const std::string fileName)
{
	//ファイルストリーム
	std::ifstream file;
	textData.str("");
	textData.clear(std::stringstream::goodbit);

	const std::string directory = "Engine/Resources/GameData/";
	file.open(directory + fileName);
	if (file.fail()) {
		assert(0);
	}

	textData << file.rdbuf();

	file.close();
}

void RailScene::TextMessageUpdate()
{
	std::string line;
	std::string face;
	std::string messageData;
	std::wstring messageDataW;

	if (isMessageWait) {
		if (isTextDraw) {
			waitMessageTimer--;
		}
		if (waitMessageTimer <= 0) {
			isMessageWait = false;
			textCount = 0;
			message.clear();
			drawMessage.clear();
		}
		return;
	}

	while (getline(textData, line)) {
		std::istringstream line_stream(line);
		std::string word;
		//半角区切りで文字列を取得
		getline(line_stream, word, ' ');
		if (word == "#") {
			continue;
		}
		if (word == "OPEN") {
			isTextWindowOpen = true;
		}
		if (word == "FACE") {
			line_stream >> face;
			if (face == "OPE_NORMAL") {
				faceType = FaceGraphics::OPE_NORMALFACE;
			}
			else if (face == "OPE_SURPRISE") {
				faceType = FaceGraphics::OPE_SURPRISEFACE;
			}
			else if (face == "OPE_SMILE") {
				faceType = FaceGraphics::OPE_SMILEFACE;
			}
		}
		if (word == "TEXT") {
			line_stream >> messageData;
			messageDataW = StringToWstring(messageData);
			message = messageDataW;
		}
		if (word == "SPEED") {
			line_stream >> textSpeed;
		}
		if (word == "WAIT") {
			isMessageWait = true;
			line_stream >> waitMessageTimer;
			break;
		}
		if (word == "CLOSE") {
			isTextWindowOpen = false;
		}
	}
}

void RailScene::TextMessageDraw()
{

	if (textSpeed <= 0) {
		textSpeed = 1;
	}

	D2D1_RECT_F textDrawPos = {
		200, 560, 950, 700
	};

	textAddTimer++;
	isTextDraw = false;
	if (textAddTimer >= textSpeed) {
		textAddTimer = 0;
		if (textCount < message.size()) {
			if (message.substr(textCount, 1) != L"/") {
				drawMessage += message.substr(textCount, 1);
			}
			else {
				drawMessage += L"\n";
			}
			textCount++;
		}

		if (textCount >= message.size()) {
			isTextDraw = true;
		}
	}

	textDraw->Draw("meiryo", "white", drawMessage, textDrawPos);
}

std::wstring RailScene::StringToWstring(const std::string& text)
{
	//文字サイズを取得
	int iBufferSize = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, (wchar_t*)NULL, 0);
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];
	//SJISからwstringに変換
	MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, cpUCS2, iBufferSize);
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

	delete[] cpUCS2;

	return oRet;
}

bool RailScene::IsTargetCheck(XMFLOAT2 enemyPos, XMFLOAT2 aimPos) {
	const float aimPosCorrection = 20.0f;
	return (enemyPos.x >= aimPos.x - aimPosCorrection && enemyPos.x <= aimPos.x + aimPosCorrection && enemyPos.y >= aimPos.y - aimPosCorrection && enemyPos.y <= aimPos.y + aimPosCorrection);
}