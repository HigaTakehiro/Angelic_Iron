#include "BossScene.h"

void BossScene::Initialize()
{
	camera = new Camera;
	camera->SetEye(XMFLOAT3(0, 100, 0));
	camera->SetTarget(XMFLOAT3(0, 10, 0));

	for (int i = 0; i < 36; i++) {
		Vector3 pos = { 0, 20, 0 };
		Vector3 rot = { 0, 270, 0 };
		Vector3 scale = { 20, 20, 20 };
		float angle = 20;
		float length = 300;
		if (i > 17) {
			angle = 25;
			length = 500;
		}
		pos = MotionMath::GetIns()->CircularMotion({ 0, 0, 0 }, pos, angle * i, length, MotionMath::Y);
		pos.y = rand() % 20 - 30;
		rot.y -= angle * i;
		std::unique_ptr<Object3d> newBuilding;
		newBuilding = (std::unique_ptr<Object3d>)Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Building));
		newBuilding->SetPosition(pos);
		newBuilding->SetRotation(rot);
		newBuilding->SetScale(scale);
		buildings.push_back(std::move(newBuilding));
	}

	ground = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Ground));
	groundPos = { 0, -50, 0 };
	ground->SetPosition(groundPos);
	groundScale = { 10, 10, 10 };
	ground->SetScale(groundScale);

	celetialSphere = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::CelestialSphere));
	celetialSphere->SetPosition(spherePos);
	celetialSphere->SetScale(sphereScale);

	postEffect = new PostEffect();
	postEffect->Initialize();

	postEffectNo = PostEffect::NORMAL;
	postEffectNo = PostEffect::NORMAL;

	player = new BossScenePlayer;
	player->Initialize(camera, Sound::GetIns());
	player->SetBossScene(this);

	int stageNo = 0;
	stageNo = SceneManager::GetStageNo();
	if (stageNo == 1) {
		LoadTextMessage("Stage1BossText.aid");
	}

	textWindow = Sprite::Create(ImageManager::TextWindow, { 580, 630 });
	textWindow->SetAlpha(0.4f);
	textWindowSize = textWindow->GetSize();
	textWindow->SetAnchorPoint({ 0.5f, 0.5f });
	faceWindow = Sprite::Create(ImageManager::FaceWindow, { 90, 630 });
	faceWindowSize = faceWindow->GetSize();
	faceWindow->SetAlpha(0.4f);
	faceWindow->SetAnchorPoint({ 0.5f, 0.5f });
	for (int i = 0; i < 3; i++) {
		opeNormal[i] = Sprite::Create(ImageManager::OPE_NORMAL, { 90, 630 });
		opeNormal[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeNormal[i]->SetSize({ 160, 160 });
		opeNormal[i]->SetColor({ 2, 2, 2 });
		opeNormal[i]->SetAnchorPoint({ 0.5f, 0.5f });
		//opeNormal[i]->SetAlpha(0.8f);
	}
	textAddTimer = 0;
	textSpeed = 1;
	//boss = new FirstBoss;
	//boss->Initialize(ModelManager::BossBody, { 0, 0, 0 });

	firstBoss = new FirstBoss;
	firstBoss->Initialize(ModelManager::BossBody, { 0, 0, 0 });
	firstBoss->SetBossScene(this);
	firstBoss->SetPlayer(player);

	pause = Sprite::Create(ImageManager::ImageName::Pause, { 640, 100 });
	pause->SetAnchorPoint({ 0.5f, 0.5f });
	titleBack = Sprite::Create(ImageManager::ImageName::TitleBack, { 640, 300 });
	titleBack->SetAnchorPoint({ 0.5f, 0.5f });
	titleBackSize = titleBack->GetSize();
	back = Sprite::Create(ImageManager::ImageName::Back, { 640, 450 });
	back->SetAnchorPoint({ 0.5f, 0.5f });
	backSize = back->GetSize();
	scoreText = Sprite::Create(ImageManager::score, { 1180, 50 });
	scoreText->SetAnchorPoint({ 0.5f, 0.5f });
	scoreText->SetSize({ scoreText->GetSize().x / 2.0f, scoreText->GetSize().y / 2.0f });
	for (int i = 0; i < 6; i++) {
		scoreNumber[i] = Sprite::Create(ImageManager::scoreNumbers, { 1252 - ((float)i * 30), 100 });
		scoreNumber[i]->SetAnchorPoint({ 0.5f, 0.5f });
		scoreNumber[i]->SetTextureRect({ nine, 0.0f }, { 64, 64 });
		scoreNumber[i]->SetSize({ 32, 32 });
	}
	score = 0;

	light = LightGroup::Create();
	for (int i = 0; i < 3; i++) {
		light->SetDirLightActive(0, true);
		light->SetPointLightActive(i, false);
		light->SetSpotLightActive(i, false);
	}
	light->SetCircleShadowActive(0, true);
	Object3d::SetLight(light);

	isPause = false;
	isTitleBack = false;
	isDead = false;
}

void BossScene::Update()
{
	playerBullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });
	bossBullets.remove_if([](std::unique_ptr<EnemyBullet>& bossBullet) { return bossBullet->IsDead(); });
	particles2d.remove_if([](std::unique_ptr<Particle2d>& particle2d) {return particle2d->IsDelete(); });

	const int delayTime = 0;
	const int noneHP = 0;

	XMFLOAT3 playerPos = { player->GetPlayerObj()->GetMatWorld().r[3].m128_f32[0], player->GetPlayerObj()->GetMatWorld().r[3].m128_f32[1], player->GetPlayerObj()->GetMatWorld().r[3].m128_f32[2] };
	light->SetCircleShadowCasterPos(0, playerPos);
	light->SetDirLightDirection(0, { 0, -1, 0 });
	light->SetCircleShadowDir(0, { 0, -1, 0 });
	light->SetCircleShadowAtten(0, { 0.0f, 0.01f, 0.0f });
	light->SetCircleShadowDistanceCasterLight(0, 1000.0f);
	light->SetCircleShadowAngle(0, { 0.0f, 0.5f });

	if (KeyInput::GetIns()->TriggerKey(DIK_ESCAPE)) {
		isPause = !isPause;
	}

	for (int i = 0; i < 6; i++) {
		scoreNumber[i]->SetTextureRect({ (float)JudgeDigitNumber(score + SceneManager::GetScore(), i), 0}, {64, 64});
	}

	if (isMessageEnd) {
		closeWindowTimer++;
		if (closeWindowTimer >= closeWindowTime) {
			closeWindowTimer = closeWindowTime;
		}
		textWindowSize.y = Easing::GetIns()->easeInOut(closeWindowTimer, closeWindowTime, 0, textWindowSize.y);
		faceWindowSize.y = Easing::GetIns()->easeInOut(closeWindowTimer, closeWindowTime, 0, faceWindowSize.y);
		operatorSize.y = Easing::GetIns()->easeInOut(closeWindowTimer, closeWindowTime, 0, operatorSize.y);

		textWindow->SetSize(textWindowSize);
		faceWindow->SetSize(faceWindowSize);
		for (int i = 0; i < 3; i++) {
			opeNormal[i]->SetSize(operatorSize);
		}
	}

	if (!isPause) {
		TextMessageUpdate();

		ground->Update();
		celetialSphere->Update();
		player->Update();

		if (player->GetHPCount() <= noneHP && !isDead) {
			XMVECTOR playerPos = player->GetPlayerObj()->GetMatWorld().r[3];
			XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
			playerPos = XMVector3TransformCoord(playerPos, matVPV);

			XMFLOAT2 player2dPos = { playerPos.m128_f32[0], playerPos.m128_f32[1] };
			std::unique_ptr<Particle2d> new2DParticle = std::make_unique<Particle2d>();
			new2DParticle->Initialize(player2dPos, { 200, 200 }, 100, ImageManager::enemyDead, { 0.5f, 0.5f }, 8, { 0, 0 }, { 32, 32 });
			particles2d.push_back(std::move(new2DParticle));
			isDead = true;
		}

		for (std::unique_ptr<Particle2d>& particle2d : particles2d) {
			particle2d->Update();
		}

		if (player->GetHPCount() > noneHP) {
			firstBoss->Update(player->GetPlayerObj()->GetMatWorld().r[3]);

			for (std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
				playerBullet->Update(delayTime);
			}

			for (std::unique_ptr<Object3d>& building : buildings) {
				building->Update();
			}

			for (std::unique_ptr<EnemyBullet>& bossBullet : bossBullets) {
				bossBullet->Update(0);
			}

			for (const std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
				if (Collision::GetIns()->OBJSphereCollision(playerBullet->GetBulletObj(), firstBoss->GetBossObj(), 1.0f, 100.0f)) {
					score += 100;
					firstBoss->OnCollision();
					playerBullet->OnCollision();
				}

				if (!firstBoss->GetIsLeftHandDead()) {
					if (Collision::GetIns()->OBJSphereCollision(playerBullet->GetBulletObj(), firstBoss->GetLeftHandObj(), 1.0f, 30.0f)) {
						score += 100;
						firstBoss->LeftHandOnCollision();
						playerBullet->OnCollision();
					}
				}

				if (!firstBoss->GetIsRightHandDead()) {
					if (Collision::GetIns()->OBJSphereCollision(playerBullet->GetBulletObj(), firstBoss->GetRightHandObj(), 1.0f, 30.0f)) {
						score += 100;
						firstBoss->RightHandOnCollision();
						playerBullet->OnCollision();
					}
				}
			}

			for (const std::unique_ptr<EnemyBullet>& bossBullet : bossBullets) {
				if (Collision::GetIns()->OBJSphereCollision(bossBullet->GetEnemyBulletObj(), player->GetPlayerObj(), 2.0f, 5.0f)) {
					bossBullet->OnCollision();
					if (!player->GetIsDamage() && player->GetHPCount() > noneHP) {
						player->OnCollision();
					}
				}
			}

			if (Collision::GetIns()->OBJSphereCollision(firstBoss->GetLeftHandObj(), player->GetPlayerObj(), 2.0f, 30.0f)) {
				if (!player->GetIsDamage() && player->GetHPCount() > noneHP) {
					player->OnCollision();
				}
			}
			if (Collision::GetIns()->OBJSphereCollision(firstBoss->GetRightHandObj(), player->GetPlayerObj(), 2.0f, 30.0f)) {
				if (!player->GetIsDamage() && player->GetHPCount() > noneHP) {
					player->OnCollision();
				}
			}
		}

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

	light->Update();

	//シーン変更
	if (player->GetIsDead()) {
		SceneManager::AddScore(score);
		SceneManager::SceneChange(SceneManager::GameOver);
	}
	else if (firstBoss->GetIsDead()) {
		SceneManager::AddScore(score);
		SceneManager::SceneChange(SceneManager::Result);
	}
	else if (isTitleBack) {
		SceneManager::SceneChange(SceneManager::Title);
	}

	//if (KeyInput::GetIns()->TriggerKey(DIK_N)) {
	//	SceneManager::AddScore(score);
	//	SceneManager::SceneChange(SceneManager::Result);
	//}
}

void BossScene::Draw()
{
	//背景色
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };
	bool isRoop = false;

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

	postEffectNo = PostEffect::NORMAL;
	if (player->GetIsDamage()) {
		postEffectNo = PostEffect::DAMAGE;
	}
	isRoop = true;

	postEffect->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//スプライト描画処理(背景)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	ground->Draw();
	celetialSphere->Draw();
	player->Draw();
	firstBoss->Draw();
	for (std::unique_ptr<Object3d>& building : buildings) {
		building->Draw();
	}
	for (std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
		playerBullet->Draw();
	}
	for (std::unique_ptr<EnemyBullet>& bossBullet : bossBullets) {
		bossBullet->Draw();
	}
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	scoreText->Draw();
	for (int i = 0; i < 6; i++) {
		scoreNumber[i]->Draw();
	}
	player->SpriteDraw();
	if (isPause) {
		pause->Draw();
		titleBack->Draw();
		back->Draw();
	}
	for (std::unique_ptr<Particle2d>& particle2d : particles2d) {
		particle2d->Draw();
	}
	if (!isPause) {
		textWindow->Draw();
		faceWindow->Draw();
		opeNormal[opeAnimeCount]->Draw();
	}
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

void BossScene::Finalize()
{
	safe_delete(ground);
	safe_delete(celetialSphere);
	safe_delete(camera);
	safe_delete(postEffect);
	safe_delete(pause);
	safe_delete(titleBack);
	safe_delete(back);
	firstBoss->Finalize();
	safe_delete(firstBoss);
	player->Finalize();
	safe_delete(player);
	safe_delete(scoreText);
	safe_delete(light);
	safe_delete(textDraw);
	safe_delete(textWindow);
	safe_delete(faceWindow);
	for (int i = 0; i < 3; i++) {
		safe_delete(opeNormal[i]);
	}
	for (int i = 0; i < 6; i++) {
		safe_delete(scoreNumber[i]);
	}
}

void BossScene::AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet)
{
	playerBullets.push_back(std::move(playerBullet));
}

void BossScene::AddEnemyBullet(std::unique_ptr<EnemyBullet> bossBullet)
{
	bossBullets.push_back(std::move(bossBullet));
}

void BossScene::LoadTextMessage(const std::string fileName)
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

void BossScene::TextMessageUpdate()
{
	std::string line;
	std::string messageData;
	std::wstring messageDataW;

	if (isMessageWait) {
		if (isTextDraw) {
			waitMessageTimer--;
		}
		if (waitMessageTimer <= 0) {
			isMessageWait = false;
			isTextDraw = false;
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
		if (word == "END") {
			isMessageEnd = true;
		}
	}
}

void BossScene::TextMessageDraw()
{
	if (textSpeed <= 0) {
		textSpeed = 1;
	}

	D2D1_RECT_F textDrawPos = {
		200, 560, 950, 700
	};

	textAddTimer++;
	if (textAddTimer >= textSpeed) {
		textAddTimer = 0;
		if (textCount < message.size()) {
			drawMessage += message.substr(textCount, 1);
			textCount++;
		}

		if (textCount >= message.size()) {
			isTextDraw = true;
		}
	}

	textDraw->Draw("default", "default", drawMessage, textDrawPos);
}

std::wstring BossScene::StringToWstring(const std::string& text)
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
