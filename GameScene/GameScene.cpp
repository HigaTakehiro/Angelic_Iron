#include "GameScene.h"
#include "FBXObject3d.h"
#include <algorithm>
#include <fstream>

GameScene::GameScene() {

}

GameScene::~GameScene() {
	safe_delete(sprite);
	player->Finalize();
	safe_delete(player);
	safe_delete(map1_a);
	safe_delete(map1_b);
	safe_delete(ground);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Sound* sound) {
	assert(dxCommon);
	assert(sound);

	this->dxCommon = dxCommon;
	this->sound = sound;
	input = KeyInput::GetIns();

	//カメラ初期化
	camera = new Camera;
	camera->SetEye(XMFLOAT3(50, 1, -100));
	camera->SetTarget(XMFLOAT3(50, 0, 0));
	railCamera = new RailCamera;
	cameraPos = { 50.0f, 1.0f, -100.0f };
	cameraRot = { 0.0f, 180.0f, 0.0f };
	points = { start, start, p2, p3, end, start, start };
	railCamera->Initialize(cameraPos, cameraRot, points, maxTime);

	//Sprite & DebugTextの初期化
	Sprite::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);

	Sprite::LoadTexture(debugTextNumber, L"Resources/debugfont.png");
	debugText.Initialize(debugTextNumber);

	//Sprite::LoadTexture(1, L"Resources/Aim.png");
	//sprite = Sprite::Create(1, { 0, 0 });
	Sprite::LoadTexture(2, L"Resources/background.png");
	background = Sprite::Create(2, { 0, 0 });

	Sprite::LoadTexture(4, L"Resources/Title.png");
	title = Sprite::Create(4, { 0, 0 });

	Sprite::LoadTexture(5, L"Resources/Gameover.png");
	gameover = Sprite::Create(5, { 0, 0 });

	Sprite::LoadTexture(6, L"Resources/Clear.png");
	clear = Sprite::Create(6, { 0, 0 });

	aimPosX = 0;
	aimPosY = 0;

	//Object3dの初期化
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);
	ModelManager::GetIns()->Initialize();

	groundModel = Model::CreateModel("ground");
	ground = Object3d::Create(groundModel);
	groundPos = { 0, -50, 0 };
	ground->SetPosition(groundPos);
	groundScale = { 10, 10, 10 };
	ground->SetScale(groundScale);

	celestialSphereModel = Model::CreateModel("CelestialSphere");
	celetialSphere = Object3d::Create(celestialSphereModel);
	celetialSphere->SetPosition(spherePos);
	celetialSphere->SetScale(sphereScale);

	player = new Player();
	player->Initialize(camera);

	LoadEnemyData();

	//MapChipの初期化
	mapchip = new MapChip;
	mapchip->MapChipInitialize();
	map1_a = mapchip->MapLoad("test1", 7, 4);
	map1_b = mapchip->MapLoad("test2", 7, 4);
	objects = mapchip->MapSet(map1_a, 7, 4, 0);
	objects2 = mapchip->MapSet(map1_b, 7, 4, 1);

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

	isDead = false;
	isClear = false;
	isTitle = true;

}

void GameScene::Update() {
	enemies.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->IsDead(); });

	// DirectX毎フレーム処理　ここから
	aimPosX = MouseInput::GetIns()->GetMousePoint().x;
	aimPosY = MouseInput::GetIns()->GetMousePoint().y;

	if (isTitle) {
		if (input->GetIns()->TriggerKey(DIK_SPACE)) {
			isTitle = false;
		}
	}

	if (!isTitle && !isClear && !isDead) {
		railCamera->Update();

		char xPos[256];
		char yPos[256];
		sprintf_s(xPos, "Xpoint : %f, YPoint : %d, ZPoint : %f", player->GetPlayerPos().x, player->GetPlayerPos().y, player->GetPlayerPos().z);
		sprintf_s(yPos, "Xpoint : %d, YPoint : %d", MouseInput::GetIns()->GetMousePoint().x, MouseInput::GetIns()->GetMousePoint().y);
		debugText.Print(xPos, 0, 0, 2.0f);
		debugText.Print(yPos, 0, 50, 2.0f);

		const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player->GetBullet();

		for (const std::unique_ptr<Enemy>& enemy : enemies) {
			for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
				if (Collision::GetIns()->OBJSphereCollision(bullet->GetBulletObj(), enemy->GetEnemyObj(), 1.0f, 5.0f)) {
					enemy->OnCollision();
				}
			}
		}

		EnemyDataUpdate();

		if (enemies.empty()) {
			isClear = true;
		}

		for (std::unique_ptr<Enemy>& enemy : enemies) {
			enemy->Update();
		}

		celetialSphere->Update();
		ground->Update();
		player->Update();
		object1->Update();

		for (auto object : objects) {
			object->Update();
		}
		for (auto object : objects2) {
			object->Update();
		}
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
	//object1->Draw(dxCommon->GetCmdList());
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(dxCommon->GetCmdList());
	player->SpriteDraw();
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

	// ４．描画コマンドここまで
}

void GameScene::Finalize() {
	safe_delete(camera);
	mapchip->MapChipFinalize();
	objects.clear();
	objects.shrink_to_fit();
	objects2.clear();
	objects2.shrink_to_fit();
	points.clear();
	points.shrink_to_fit();
	safe_delete(mapchip);
	safe_delete(object1);
	safe_delete(model1);
	FbxLoader::GetInstance()->Finalize();
}

void GameScene::Reset() {
	camera->SetEye(XMFLOAT3(50, 1, -100));
	camera->SetTarget(XMFLOAT3(50, 0, 0));

	player->Reset();

	isDead = false;
	isClear = false;
	isTitle = true;

	LoadEnemyData();
}

void GameScene::LoadEnemyData() {
	//ファイルストリーム
	std::ifstream file;
	enemyData.str("");
	enemyData.clear(std::stringstream::goodbit);
	enemies.clear();

	const std::string filename = "EnemySet.aid";
	const std::string directory = "Resources/";
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
	bool isRot = false;
	bool isScale = false;
	bool isStile = false;

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
		if (word == "Scale") {
			line_stream >> scale.x;
			line_stream >> scale.y;
			line_stream >> scale.z;
			isScale = true;
		}
		//if (word == "Type") {
		//	line_stream >> type;
		//	isStile = true;
		//}

		if (isPos && isRot && isScale) {
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize("Enemy", pos, rot, scale);
			enemies.push_back(std::move(newEnemy));
			isPos = false;
			isRot = false;
			isScale = false;
		}
	}
}