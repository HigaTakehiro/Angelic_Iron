#include "GameScene.h"
#include "FBXObject3d.h"
#include <algorithm>

GameScene::GameScene() {

}

GameScene::~GameScene() {
	safe_delete(sprite);
	player->Finalize();
	safe_delete(player);
	enemy->Finalize();
	safe_delete(enemy);
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

	//Object3dの初期化
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);

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

	enemy = new Enemy();
	enemy->Initialize();

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
	enemyDeadCount = 0;
	for (int i = 0; i < 3; i++) {
		isEnemyDead[i] = false;
	}

	
}

void GameScene::Update() {
	// DirectX毎フレーム処理　ここから
	aimPosX = MouseInput::GetIns()->GetMousePoint().x;
	aimPosY = MouseInput::GetIns()->GetMousePoint().y;

	//デバッグテキスト
	//if (input->TriggerKey(DIK_SPACE) || MouseInput::GetIns()->TriggerClick(MouseInput::GetIns()->LEFT_CLICK) || PadInput::GetIns()->TriggerButton(PadInput::GetIns()->Button_A)) {
	//	if (object1->GetIsAnimation() == true) {
	//		object1->StopAnimation();
	//	}
	//	else {
	//		object1->PlayAnimation();
	//	}
	//}

	if (isTitle) {
		if (input->GetIns()->TriggerKey(DIK_SPACE)) {
			isTitle = false;
		}
	}

	if (!isTitle && !isClear && !isDead) {

		if (input->PushKey(DIK_RIGHT)) {
			camera->CameraMoveEyeVector({ +2.0f, 0.0f, 0.0f });
		}
		if (input->PushKey(DIK_LEFT)) {
			camera->CameraMoveEyeVector({ -2.0f, 0.0f, 0.0f });
		}
		if (input->PushKey(DIK_UP)) {
			camera->CameraMoveEyeVector({ 0.0f, 0.0f, +2.0f });
		}
		if (input->PushKey(DIK_DOWN)) {
			camera->CameraMoveEyeVector({ 0.0f, 0.0f, -2.0f });
		}

		camera->CameraMoveVector({ 0.0f, 0.0f, +0.2f });

		char xPos[256];
		char yPos[256];
		sprintf_s(xPos, "Xpoint : %f, YPoint : %f, ZPoint : %f", player->GetPlayerPos().x, player->GetPlayerPos().y, player->GetPlayerPos().z);
		sprintf_s(yPos, "Xpoint : %d, YPoint : %d", MouseInput::GetIns()->GetMousePoint().x, MouseInput::GetIns()->GetMousePoint().y);
		debugText.Print(xPos, 100, 300, 2.0f);
		debugText.Print(yPos, 100, 400, 2.0f);

		for (int i = 0; i < 3; i++) {
			if (Collision::GetIns()->SphereCollision(player->GetShotObject(), enemy->GetEnemy(i))) {
				isEnemyDead[i] = true;
			}

			if (Collision::GetIns()->SphereCollision(player->GetPlayerObject(), enemy->GetEnemy(i))) {
				if (!isEnemyDead[i]) {
					isDead = true;
				}
			}
		}

		if (player->GetPlayerObject()->GetPosition().z > enemy->GetEnemy(2)->GetPosition().z) {
			isDead = true;
		}

		for (int i = 0; i < 3; i++) {
			if (isEnemyDead[0] && isEnemyDead[1] && isEnemyDead[2]) {
				isClear = true;
			}
		}

		celetialSphere->Update();
		ground->Update();
		player->Update();
		enemy->Update();
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
	
	/*for (auto object : objects) {
		object->Draw();
	}
	for (auto object : objects2) {
		object->Draw();
	}*/
	enemy->Draw(isEnemyDead);
	if (!isDead) {
		player->ObjectDraw();
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
	//debugText.DrawAll(dxCommon->GetCmdList());
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
	enemyDeadCount = 0;
	for (int i = 0; i < 3; i++) {
		isEnemyDead[i] = false;
	}
}