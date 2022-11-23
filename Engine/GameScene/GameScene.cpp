#include "GameScene.h"
#include "FBXObject3d.h"
#include <algorithm>
#include <fstream>

void GameScene::Initialize(DirectXCommon* dxCommon, Sound* sound) {
	assert(dxCommon);
	assert(sound);

	this->dxCommon = dxCommon;
	this->sound = sound;
	input = KeyInput::GetIns();

	//this->sound->PlayWave("Engine/Resources/Sound/BGM/Speace_World.wav", true, 0.2f);

	//カメラ初期化
	camera = new Camera;
	camera->SetEye(XMFLOAT3(50, 1, -100));
	camera->SetTarget(XMFLOAT3(50, 0, 0));
	railCamera = new RailCamera;

	LoadRailPoint();

	//Sprite & DebugTextの初期化
	Sprite::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);

	Sprite::LoadTexture(debugTextNumber, L"Engine/Resources/Images/debugfont.png");
	debugText.Initialize(debugTextNumber);

	ImageManager::GetIns()->Initialize();

	background = Sprite::Create(ImageManager::ImageName::background, { 0, 0 });
	title = Sprite::Create(ImageManager::ImageName::title, { 0, 0 });
	gameover = Sprite::Create(ImageManager::ImageName::gameover, { 0, 0 });
	clear = Sprite::Create(ImageManager::ImageName::clear, { 0, 0 });

	//Object3dの初期化
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);
	ModelManager::GetIns()->Initialize();

	ground = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Ground));
	groundPos = { 0, -50, 0 };
	ground->SetPosition(groundPos);
	groundScale = { 10, 10, 10 };
	ground->SetScale(groundScale);

	celetialSphere = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::CelestialSphere));
	celetialSphere->SetPosition(spherePos);
	celetialSphere->SetScale(sphereScale);

	player = new Player();
	player->Initialize(camera, sound, clearTime);
	player->SetGameScene(this);

	LoadEnemyData();

	//FBXの初期化
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDev());
	FBXObject3d::SetDevice(dxCommon->GetDev());
	FBXObject3d::SetCamera(camera);
	FBXObject3d::CreateGraphicsPipeline();
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(model1);
	object1->SetScale({ 5.0f, 5.0f, 5.0f });
	object1->PlayAnimation();

	//PostEffectの初期化
	postEffect = new PostEffect();
	postEffect->Initialize();

	//ゲームシーン用変数の初期化
	isDead = false;
	isClear = false;
	isTitle = true;
	isWait = false;

	clearTimer = clearTime;

	referenceCount = std::chrono::steady_clock::now();
}

void GameScene::Update() {
	// DirectX毎フレーム処理　ここから
	const int32_t noneHP = 0;

	enemies.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->IsDead(); });
	enemyBullets.remove_if([](std::unique_ptr<EnemyBullet>& enemyBullet) { return enemyBullet->IsDead(); });
	playerBullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });
	particles2d.remove_if([](std::unique_ptr<Particle2d>& particle) {return particle->IsDelete(); });
	bombs.remove_if([](std::unique_ptr<Bomb>& bomb) {return bomb->GetIsDead(); });

	if (isTitle) {
		if (input->GetIns()->TriggerKey(DIK_SPACE) || MouseInput::GetIns()->TriggerClick(MouseInput::GetIns()->LEFT_CLICK)) {
			isTitle = false;
			railCamera->SetStartTime(GetTickCount64());
		}
	}

	if (!isTitle && !isClear && !isDead) {

		char xPos[256];
		char yPos[256];
		char isSlowCheck[256];
		sprintf_s(xPos, "Xpoint : %f, YPoint : %f", player->GetAimPos().x, player->GetAimPos().y);
		sprintf_s(yPos, "Xpoint : %d, YPoint : %d", MouseInput::GetIns()->GetMousePoint().x, MouseInput::GetIns()->GetMousePoint().y);
		if (!player->GetIsBomb()) {
			sprintf_s(isSlowCheck, "false");
		}
		else {
			sprintf_s(isSlowCheck, "true");
		}
		debugText.Print(xPos, 0, 0, 2.0f);
		debugText.Print(yPos, 0, 50, 2.0f);
		debugText.Print(isSlowCheck, 0, 100, 2.0f);

		if (input->GetIns()->TriggerKey(DIK_R) && input->GetIns()->PushKey(DIK_LSHIFT)) {
			Reset();
		}

		for (const std::unique_ptr<Enemy>& enemy : enemies) {
			for (const std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
				if (Collision::GetIns()->OBJSphereCollision(playerBullet->GetBulletObj(), enemy->GetEnemyObj(), 1.0f, 5.0f)) {
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

		for (const std::unique_ptr<Enemy>& enemy : enemies) {
			for (const std::unique_ptr<Bomb>& bomb : bombs) {
				if (Collision::GetIns()->OBJSphereCollision(enemy->GetEnemyObj(), bomb->GetBullet(), 5.0f, 1.0f)) {
					enemy->OnCollision();
					bomb->OnCollision();
				}
			}
		}

		for (std::unique_ptr<Enemy>& enemy : enemies) {
			XMVECTOR enemy3dPos = { enemy->GetEnemyObj()->GetMatWorld().r[3] }; //ワールド座標
			XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
			enemy3dPos = XMVector3TransformCoord(enemy3dPos, matVPV); //スクリーン座標

			XMFLOAT2 enemy2dPos = { enemy3dPos.m128_f32[0], enemy3dPos.m128_f32[1] };

			XMFLOAT2 targetCheckHitPos = { enemy2dPos.x - player->GetAimPos().x, enemy2dPos.y - player->GetAimPos().y };

			if (IsTargetCheck(enemy2dPos, player->GetAimPos()) && player->GetIsBomb()) {
				enemy->SetTarget(true);
			}

			if (enemy->IsDead()) {
				std::unique_ptr<Particle2d> new2DParticle = std::make_unique<Particle2d>();
				new2DParticle->Initialize(enemy2dPos, { 50, 50 }, 24, ImageManager::enemyDead, { 0, 0 }, 8, { 0, 0 }, { 32, 32 });
				particles2d.push_back(std::move(new2DParticle));
			}
		}

		EnemyDataUpdate();

		if (enemies.empty()) {
			clearTimer--;
		}
		if (clearTimer <= 0) {
			isClear = true;
		}

		if (player->GetHPCount() <= noneHP && !isPlayerDead) {
			XMVECTOR playerPos = { player->GetPlayerPos().x, player->GetPlayerPos().y, player->GetPlayerPos().z };
			XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
			playerPos = XMVector3TransformCoord(playerPos, matVPV);

			XMFLOAT2 player2dPos = { playerPos.m128_f32[0] - 100.0f, playerPos.m128_f32[1] - 90.0f };
			std::unique_ptr<Particle2d> new2DParticle = std::make_unique<Particle2d>();
			new2DParticle->Initialize(player2dPos, { 200, 200 }, 80, ImageManager::enemyDead, { 0, 0 }, 8, { 0, 0 }, { 32, 32 });
			particles2d.push_back(std::move(new2DParticle));
			isPlayerDead = true;
		}

		if (player->GetIsDead()) {
			isDead = true;
		}

		celetialSphere->Update();
		ground->Update();
		player->Update(enemies.empty());

		float delayCount = 0.0f;

		if (player->GetIsBomb()) {
			delayCount = 3.0f;
		}

		if (player->GetHPCount() > 0) {
			if (!enemies.empty()) {
				railCamera->Update(delayCount);
			}
			for (std::unique_ptr<Enemy>& enemy : enemies) {
				enemy->Update(player->GetPlayerPos(), delayCount);
			}
			for (std::unique_ptr<Bomb>& bomb : bombs) {
				bomb->Update();
			}
		}

		for (std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets) {
			enemyBullet->Update(delayCount);
		}
		for (std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
			playerBullet->Update(delayCount);
		}
		for (std::unique_ptr<Particle2d>& particle2d : particles2d) {
			particle2d->Update();
		}

		//player->SetEnemies(enemies);

		object1->Update();
	}

	if (isClear) {
		if (input->GetIns()->TriggerKey(DIK_SPACE)) {
			Reset();
		}
	}

	if (isDead) {
		if (input->GetIns()->TriggerKey(DIK_SPACE)) {
			Reset();
		}
	}
}

void GameScene::Draw() {
	//背景色
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };
	static int postEffectNo = 0;

	if (player->GetIsDamage()) {
		postEffectNo = 1;
	}
	else {
		postEffectNo = 0;
	}

	postEffect->PreDrawScene(dxCommon->GetCmdList());

	//スプライト描画処理(背景)
	Sprite::PreDraw(dxCommon->GetCmdList());
	//background->Draw();
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(dxCommon->GetCmdList());
	ground->Draw();
	celetialSphere->Draw();

	if (!isDead) {
		player->ObjectDraw();
	}
	for (std::unique_ptr<Enemy>& enemy : enemies) {
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
	//object1->Draw(dxCommon->GetCmdList());
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(dxCommon->GetCmdList());
	player->SpriteDraw();
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->SpriteDraw();
	}
	for (std::unique_ptr<Particle2d>& particle2d : particles2d) {
		particle2d->Draw();
	}
	if (isTitle) {
		title->Draw();
	}
	if (isDead) {
		gameover->Draw();
	}
	if (isClear) {
		clear->Draw();
	}
	debugText.DrawAll(dxCommon->GetCmdList());
	Sprite::PostDraw();

	postEffect->PostDrawScene(dxCommon->GetCmdList());

	dxCommon->PreDraw(backColor);
	postEffect->Draw(dxCommon->GetCmdList(), postEffectNo);
	dxCommon->PostDraw();
}

void GameScene::Finalize() {
	player->Finalize();
	safe_delete(player);
	safe_delete(ground);
	safe_delete(background);
	safe_delete(title);
	safe_delete(gameover);
	safe_delete(clear);
	safe_delete(celetialSphere);
	safe_delete(camera);
	safe_delete(object1);
	safe_delete(model1);
	safe_delete(mapchip);
	safe_delete(railCamera);
	safe_delete(postEffect);
	FbxLoader::GetInstance()->Finalize();
}

void GameScene::Reset() {
	LoadRailPoint();
	railCamera->Reset(points);

	clearTimer = clearTime;
	isDead = false;
	isClear = false;
	isTitle = true;
	isPlayerDead = false;

	for (const std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
		playerBullet->OnCollision();
	}
	for (const std::unique_ptr<Bomb>& bomb : bombs) {
		bomb->OnCollision();
	}

	player->Reset();

	LoadEnemyData();
}

void GameScene::LoadEnemyData() {
	//ファイルストリーム
	std::ifstream file;
	enemyData.str("");
	enemyData.clear(std::stringstream::goodbit);
	enemies.clear();

	const std::string filename = "EnemySet.aid";
	const std::string directory = "Engine/Resources/GameData/";
	file.open(directory + filename);
	if (file.fail()) {
		assert(0);
	}

	enemyData << file.rdbuf();

	file.close();
}

void GameScene::EnemyDataUpdate() {
	std::string line;
	Vector3 pos{};
	Vector3 rot{};
	Vector3 scale{};
	std::string type;
	bool isPos = false;
	bool isScale = false;
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
		if (word == "Scale") {
			line_stream >> scale.x;
			line_stream >> scale.y;
			line_stream >> scale.z;
			isScale = true;
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

		if (isPos && isScale && isStyle) {
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize("Enemy", pos, scale, type);
			newEnemy->SetGamaScene(this);
			enemies.push_back(std::move(newEnemy));
			isPos = false;
			isScale = false;
			isStyle = false;
		}
	}
}

void GameScene::AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet) {
	enemyBullets.push_back(std::move(enemyBullet));
}

void GameScene::AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet) {
	playerBullets.push_back(std::move(playerBullet));
}

void GameScene::AddBomb(std::unique_ptr<Bomb> bomb) {
	bombs.push_back(std::move(bomb));
}

void GameScene::LoadRailPoint() {
	//ファイルストリーム
	std::ifstream file;
	std::stringstream railcameraPointsData;
	railcameraPointsData.str("");
	railcameraPointsData.clear(std::stringstream::goodbit);
	points.clear();

	const std::string filename = "RailCameraPoints.aid";
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


	}

	assert(splineTime != 0);
	railCamera->Initialize(startPos, rot, points, splineTime, isCameraRoop);

}

bool GameScene::IsTargetCheck(XMFLOAT2 enemyPos, XMFLOAT2 aimPos) {
	const float aimPosCorrection = 20.0f;
	return (enemyPos.x >= aimPos.x - aimPosCorrection && enemyPos.x <= aimPos.x + aimPosCorrection && enemyPos.y >= aimPos.y - aimPosCorrection && enemyPos.y <= aimPos.y + aimPosCorrection);
}

int GameScene::GetBombTarget() {
	int enemyTargetCount = 0;
	for (const std::unique_ptr<Enemy>& enemy : enemies) {
		if (enemy->GetIsTarget()) {
			enemyTargetCount++;
		}
	}

	return enemyTargetCount;
}