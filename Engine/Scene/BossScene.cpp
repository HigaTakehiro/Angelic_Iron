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

	player = new BossScenePlayer;
	player->Initialize(camera, Sound::GetIns());
	player->SetBossScene(this);

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

	score = 0;

	isPause = false;
	isTitleBack = false;
}

void BossScene::Update()
{
	playerBullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });
	bossBullets.remove_if([](std::unique_ptr<EnemyBullet>& bossBullet) { return bossBullet->IsDead(); });
	particles2d.remove_if([](std::unique_ptr<Particle2d>& particle2d) {return particle2d->IsDelete(); });

	const int delayTime = 0;
	const int noneHP = 0;

	if (KeyInput::GetIns()->TriggerKey(DIK_ESCAPE)) {
		isPause = !isPause;
	}

	if (!isPause) {
		ground->Update();
		celetialSphere->Update();
		player->Update();

		if (player->GetHPCount() <= noneHP) {
			XMVECTOR playerPos = player->GetPlayerObj()->GetMatWorld().r[3];
			XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
			playerPos = XMVector3TransformCoord(playerPos, matVPV);

			XMFLOAT2 player2dPos = { playerPos.m128_f32[0], playerPos.m128_f32[1] };
			std::unique_ptr<Particle2d> new2DParticle = std::make_unique<Particle2d>();
			new2DParticle->Initialize(player2dPos, { 200, 200 }, 80, ImageManager::enemyDead, { 0.5f, 0.5f }, 8, { 0, 0 }, { 32, 32 });
			particles2d.push_back(std::move(new2DParticle));
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
					if (Collision::GetIns()->OBJSphereCollision(playerBullet->GetBulletObj(), firstBoss->GetLeftHandObj(), 1.0f, 20.0f)) {
						score += 100;
						firstBoss->LeftHandOnCollision();
						playerBullet->OnCollision();
					}
				}

				if (!firstBoss->GetIsRightHandDead()) {
					if (Collision::GetIns()->OBJSphereCollision(playerBullet->GetBulletObj(), firstBoss->GetRightHandObj(), 1.0f, 20.0f)) {
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

	if (isTitleBack) {
		SceneManager::SceneChange(SceneManager::Title);
	}

	if (player->GetIsDead()) {
		SceneManager::AddScore(score);
		SceneManager::SceneChange(SceneManager::GameOver);
	}

	if (KeyInput::GetIns()->TriggerKey(DIK_N)) {
		SceneManager::AddScore(score);
		SceneManager::SceneChange(SceneManager::Result);
	}
}

void BossScene::Draw()
{
	//”wŒiF
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };
	bool isRoop = false;

	postEffectNo = PostEffect::NORMAL;
	if (player->GetIsDamage()) {
		postEffectNo = PostEffect::DAMAGE;
	}
	isRoop = true;

	postEffect->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//ƒXƒvƒ‰ƒCƒg•`‰æˆ—(”wŒi)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());

	Sprite::PostDraw();

	//3DƒIƒuƒWƒFƒNƒg•`‰æˆ—
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

	//ƒXƒvƒ‰ƒCƒg•`‰æˆ—(UI“™)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	player->SpriteDraw();
	if (isPause) {
		pause->Draw();
		titleBack->Draw();
		back->Draw();
	}
	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

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
}

void BossScene::AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet)
{
	playerBullets.push_back(std::move(playerBullet));
}

void BossScene::AddEnemyBullet(std::unique_ptr<EnemyBullet> bossBullet)
{
	bossBullets.push_back(std::move(bossBullet));
}
