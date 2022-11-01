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
	cameraPos = { 50.0f, 1.0f, 100.0f };
	cameraRot = { 0.0f, 180.0f, 0.0f };
	points = { start, start, p2, p3, p4, p5, end, start, start };
	railCamera->Initialize(cameraPos, cameraRot, points, maxTime);

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
	player->Initialize(camera, sound);
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

}

void GameScene::Update() {
	enemies.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->IsDead(); });
	enemyBullets.remove_if([](std::unique_ptr<EnemyBullet>& enemyBullet) { return enemyBullet->IsDead(); });
	playerBullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });

	// DirectX毎フレーム処理　ここから
	if (isTitle) {
		if (input->GetIns()->TriggerKey(DIK_SPACE) || MouseInput::GetIns()->TriggerClick(MouseInput::GetIns()->LEFT_CLICK)) {
			isTitle = false;
			railCamera->SetStartTime(GetTickCount64());
		}
	}

	if (!isTitle && !isClear && !isDead) {
		railCamera->Update();

		char xPos[256];
		char yPos[256];
		sprintf_s(xPos, "Xpoint : %f, YPoint : %f, ZPoint : %f", player->GetAimPos().x, player->GetAimPos().y, player->GetAimPos().z);
		sprintf_s(yPos, "Xpoint : %d, YPoint : %d", MouseInput::GetIns()->GetMousePoint().x, MouseInput::GetIns()->GetMousePoint().y);
		debugText.Print(xPos, 0, 0, 2.0f);
		debugText.Print(yPos, 0, 50, 2.0f);

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
				if (!player->GetIsDamage()) {
					player->OnCollision();
				}
				enemyBullet->OnCollision();
				railCamera->SetIsDamage();
			}
		}

		EnemyDataUpdate();

		if (enemies.empty()) {
			//isClear = true;
		}
		if (player->GetIsDead()) {
			isDead = true;
		}

		for (std::unique_ptr<Enemy>& enemy : enemies) {
			enemy->Update(player->GetPlayerPos());
		}
		for (std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets) {
			enemyBullet->Update();
		}
		for (std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
			playerBullet->Update();
		}

		celetialSphere->Update();
		ground->Update();
		player->Update();
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
	//object1->Draw(dxCommon->GetCmdList());
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(dxCommon->GetCmdList());
	player->SpriteDraw();
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->SpriteDraw();
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
	railCamera->Reset();

	player->Reset();

	isDead = false;
	isClear = false;
	isTitle = true;

	for (const std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
		playerBullet->OnCollision();
	}

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