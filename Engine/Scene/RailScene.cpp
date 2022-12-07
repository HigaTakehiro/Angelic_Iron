#include "RailScene.h"
#include "FBXObject3d.h"
#include <algorithm>
#include <fstream>

void RailScene::Initialize() {

	//this->sound->PlayWave("Engine/Resources/Sound/BGM/Speace_World.wav", true, 0.2f);

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
	back = Sprite::Create(ImageManager::ImageName::Back, { 640, 500 });
	back->SetAnchorPoint({ 0.5f, 0.5f });
	backSize = back->GetSize();

	ground = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Ground));
	groundPos = { 0, -50, 0 };
	ground->SetPosition(groundPos);
	groundScale = { 10, 10, 10 };
	ground->SetScale(groundScale);

	celetialSphere = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::CelestialSphere));
	celetialSphere->SetPosition(spherePos);
	celetialSphere->SetScale(sphereScale);

	player = new Player();
	player->Initialize(camera, Sound::GetIns(), clearTime);
	player->SetRailScene(this);

	int stageNo;
	stageNo = SceneManager::GetStageNo();
	if (stageNo == 1) {
		LoadRailPoint("Stage1RailPoints.aid");
		LoadEnemyData("Stage1EnemyData.aid");
	}
	else if (stageNo == 2) {
		LoadRailPoint("Stage2RailPoints.aid");
		LoadEnemyData("Stage2EnemyData.aid");
	}

	//FBXの初期化
	/*FbxLoader::GetInstance()->Initialize(dxCommon->GetDev());
	FBXObject3d::SetDevice(dxCommon->GetDev());
	FBXObject3d::SetCamera(camera);
	FBXObject3d::CreateGraphicsPipeline();
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(model1);
	object1->SetScale({ 5.0f, 5.0f, 5.0f });
	object1->PlayAnimation();*/

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

	clearTimer = clearTime;

	referenceCount = std::chrono::steady_clock::now();
}

void RailScene::Update() {
	// DirectX毎フレーム処理　ここから
	const int32_t noneHP = 0;

	enemies.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->IsDead(); });
	enemyBullets.remove_if([](std::unique_ptr<EnemyBullet>& enemyBullet) { return enemyBullet->IsDead(); });
	playerBullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });
	particles2d.remove_if([](std::unique_ptr<Particle2d>& particle) {return particle->IsDelete(); });
	bombs.remove_if([](std::unique_ptr<Bomb>& bomb) {return bomb->GetIsDead(); });

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
			score += 100;
			std::unique_ptr<Particle2d> new2DParticle = std::make_unique<Particle2d>();
			new2DParticle->Initialize(enemy2dPos, { 50, 50 }, 24, ImageManager::enemyDead, { 0, 0 }, 8, { 0, 0 }, { 32, 32 });
			particles2d.push_back(std::move(new2DParticle));
		}
	}

	EnemyDataUpdate();

	if (railCamera->GetIsEnd()) {
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

	float delayCount = 0.0f;

	if (player->GetIsBomb()) {
		delayCount = 3.0f;
	}

	if (!isPause) {
		celetialSphere->Update();
		ground->Update();

		if (player->GetHPCount() > 0) {
			if (!railCamera->GetIsEnd()) {
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

		player->Update(railCamera->GetIsEnd());
	}
	else {
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
	}

	//シーン切り替え
	if (isDead && !isClear) {
		SceneManager::SetScore(score);
		SceneManager::SceneChange(SceneManager::GameOver);
	}
	else if (isClear && !isDead) {
		SceneManager::SetScore(score);
		if (SceneManager::GetStageNo() == 1) {
			SceneManager::SceneChange(SceneManager::Stage1_Boss);
		}
		else if (SceneManager::GetStageNo() == 2) {
			SceneManager::SceneChange(SceneManager::Stage2_Boss);
		}
	}
	else if (isTitleBack) {
		SceneManager::SceneChange(SceneManager::Title);
	}

	if (KeyInput::GetIns()->TriggerKey(DIK_N)) {
		SceneManager::SetScore(score);
		SceneManager::SceneChange(SceneManager::Stage1_Boss);
	}

	//player->SetEnemies(enemies);

	//object1->Update();

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
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	player->SpriteDraw();
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->SpriteDraw();
	}
	for (std::unique_ptr<Particle2d>& particle2d : particles2d) {
		particle2d->Draw();
	}
	if (isPause) {
		pause->Draw();
		titleBack->Draw();
		back->Draw();
	}
	debugText.DrawAll(DirectXSetting::GetIns()->GetCmdList());
	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

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
	safe_delete(model1);
	safe_delete(mapchip);
	safe_delete(railCamera);
	safe_delete(postEffect);
	safe_delete(pause);
	safe_delete(titleBack);
	safe_delete(back);
	//FbxLoader::GetInstance()->Finalize();
}

//void RailScene::Reset() {
//	LoadRailPoint();
//	railCamera->Reset(points);
//
//	clearTimer = clearTime;
//	isDead = false;
//	isClear = false;
//	isPlayerDead = false;
//
//	for (const std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
//		playerBullet->OnCollision();
//	}
//	for (const std::unique_ptr<Bomb>& bomb : bombs) {
//		bomb->OnCollision();
//	}
//
//	player->Reset();
//
//	LoadEnemyData();
//}

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
			newEnemy->SetRailScene(this);
			enemies.push_back(std::move(newEnemy));
			isPos = false;
			isScale = false;
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

bool RailScene::IsTargetCheck(XMFLOAT2 enemyPos, XMFLOAT2 aimPos) {
	const float aimPosCorrection = 20.0f;
	return (enemyPos.x >= aimPos.x - aimPosCorrection && enemyPos.x <= aimPos.x + aimPosCorrection && enemyPos.y >= aimPos.y - aimPosCorrection && enemyPos.y <= aimPos.y + aimPosCorrection);
}