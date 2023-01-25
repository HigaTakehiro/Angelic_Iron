#include "Player.h"
#include "SafeDelete.h"
#include "MotionMath.h"
#include "Easing.h"

void Player::Initialize(Camera* camera, float clearTime) {
	this->camera = camera;

	aim = Sprite::Create(ImageManager::ImageName::aim, { 0, 0 });
	aim->SetSize(XMFLOAT2(100.0f, 100.0f));
	aim->SetAnchorPoint({ 0.5f, 0.5f });
	playerUI = Sprite::Create(ImageManager::ImageName::playerUI, { 1000, 650 });
	for (int i = 0; i < maxHp; i++) {
		float hpUiXPos = 1178.0f;
		hpUiXPos -= (float)(i * 87);
		hpUI[i] = Sprite::Create(ImageManager::ImageName::playerHP, { hpUiXPos, 688 });
	}
	for (int i = 0; i < maxBulletCount; i++) {
		float bulletUiPos = 1242.0f;
		bulletUiPos -= (float)(i * 16);
		bulletUI[i] = Sprite::Create(ImageManager::ImageName::playerBullet, { bulletUiPos, 652 });
	}
	reloadUI = Sprite::Create(ImageManager::ImageName::reload, { 1065, 652 });

	player = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Player_Normal));
	playerScale = { 2, 2, 2 };
	playerLPos = { 0, 200, 50 };
	playerRot = { 90, 0, 0 };
	player->SetScale(playerScale);
	player->SetPosition(playerLPos);
	player->SetRotation(playerRot);
	player->SetCameraParent(camera);

	for (int i = 0; i < 3; i++) {
		bomb[i] = Sprite::Create(ImageManager::Bomb, { 1050.0f + (float)(i * 80), 600.0f });
		bomb[i]->SetAnchorPoint({ 0.5f, 0.5f });
	}

	gun = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Gun));
	gun->SetPosition(Vector3(1, 0.6, 1.1));
	gun->SetParent(player);

	bulletCount = 0;
	hpCount = maxHp;
	reloadTimer = reloadTime;
	damageEffectTimer = damageEffectTime;
	shotCoolTimer = 0;

	bombCount = 3;

	this->clearTime = clearTime;
	clearTimer = this->clearTime;
	deadTimer = deadTime;
	startTimer = 0;
	returnTimer = 0;
	for (int i = 0; i < 4; i++) {
		holdTimer[i] = 0;
	}
}

void Player::Finalize() {
	safe_delete(player);
	safe_delete(gun);
	safe_delete(aim);
	safe_delete(playerUI);
	for (int i = 0; i < 3; i++) {
		safe_delete(bomb[i]);
	}
	for (int i = 0; i < maxHp; i++) {
		safe_delete(hpUI[i]);
	}
	for (int i = 0; i < maxBulletCount; i++) {
		safe_delete(bulletUI[i]);
	}
	safe_delete(reloadUI);
}

void Player::Update(bool isClear) {
	const int deadHp = 0;
	const int noneBulletCount = 0;
	const int reloadTimeOver = 0;
	const int shotCoolTimeOver = 0;

	startTimer++;
	if (startTimer >= startTime) {
		startTimer = startTime;
		isStart = true;
	}
	if (!isStart) {
		playerLPos.y = Easing::easeIn(startTimer, startTime, 0, playerLPos.y);
		playerRot.x = Easing::easeIn(startTimer, startTime * 2, 0, playerRot.x);
	}

	if (!isClear) {
		if (hpCount <= deadHp) {
			DeadPerformance();
		}
		if (bulletCount <= noneBulletCount && !isReload) {
			isReload = true;
			//sound->PlayWave("Engine/Resources/Sound/SE/reload.wav", false, 0.05f);
		}
		if (isReload) {
			reloadTimer--;
		}
		if (reloadTimer <= reloadTimeOver) {
			isReload = false;
			bulletCount = maxBulletCount;
			reloadTimer = reloadTime;
		}
		if (shotCoolTimer > shotCoolTimeOver) {
			shotCoolTimer--;
		}
		else if (shotCoolTimer <= shotCoolTimeOver) {
			isShot = false;
			shotCoolTimer = 0.0f;
		}

		if ((MouseInput::GetIns()->PushClick(MouseInput::LEFT_CLICK)) && !isShot && bulletCount > noneBulletCount && !isBomb) {
			isShot = true;
			Shot();
		}
		if (KeyInput::GetIns()->TriggerKey(DIK_R) && bulletCount != maxBulletCount) {
			bulletCount = noneBulletCount;
		}

		if (MouseInput::GetIns()->TriggerClick(MouseInput::RIGHT_CLICK) && bombCount > 0) {
			isBomb = !isBomb;
			for (std::unique_ptr<BaseEnemy>& enemy : railScene->GetEnemyObj()) {
				enemy->SetTarget(false);
			}
		}

		if (isBomb && MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
			BombShot();
		}

		if (isDamage) {
			DamageEffect();
		}
		if (hpCount > deadHp && isStart) {
			Move();
		}

		playerWPos = player->GetMatWorld().r[3];

		player->SetPosition(playerLPos);
		player->SetRotation(playerRot);
	}
	else {
		ClearPerformance();
	}

	AimUpdate();
	player->Update();
	gun->Update();
}

void Player::SpriteDraw() {
	playerUI->Draw();
	for (int i = 0; i < hpCount; i++) {
		hpUI[i]->Draw();
	}
	for (int i = 0; i < bulletCount; i++) {
		bulletUI[i]->Draw();
	}
	for (int i = 0; i < bombCount; i++) {
		bomb[i]->Draw();
	}
	if (isReload) {
		reloadUI->Draw();
	}
	aim->Draw();
}

void Player::ObjectDraw() {
	const int32_t liveTime = deadTime / 1.2;
	if (deadTimer >= liveTime) {
		player->Draw();
		gun->Draw();
	}
}

void Player::Move() {
	const float moveSpeed = 1.0f;
	const float stopPosX = 40.0f;
	const float stopPosY = 20.0f;
	const float stopRotX = 30.0f;
	const float stopRotY = 50.0f;
	const Vector3 initRot = { 0, 0, 0 };
	const float timeOver = 100.0f;
	const float initTime = 0.0f;

	if (KeyInput::GetIns()->HoldKey(DIK_W)) {
		if (holdTimer[0] <= timeOver) {
			holdTimer[0]++;
		}
		if (playerLPos.y <= stopPosY) {
			playerLPos.y += moveSpeed;
		}
		playerRot.x = Easing::easeOut(holdTimer[0], timeOver, initRot.x - stopRotX, playerRot.x);
	}
	else {
		holdTimer[0] = initTime;
	}
	if (KeyInput::GetIns()->HoldKey(DIK_S)) {
		if (holdTimer[1] <= timeOver) {
			holdTimer[1]++;
		}
		if (playerLPos.y >= -stopPosY) {
			playerLPos.y -= moveSpeed;
		}
		playerRot.x = Easing::easeOut(holdTimer[1], timeOver, initRot.x + stopRotX, playerRot.x);
	}
	else {
		holdTimer[1] = initTime;
	}
	if (KeyInput::GetIns()->HoldKey(DIK_A)) {
		if (holdTimer[2] <= timeOver) {
			holdTimer[2]++;
		}
		if (playerLPos.x >= -stopPosX) {
			playerLPos.x -= moveSpeed;
		}
		playerRot.y = Easing::easeOut(holdTimer[2], timeOver, initRot.y - stopRotY, playerRot.y);
	}
	else {
		holdTimer[2] = initTime;
	}
	if (KeyInput::GetIns()->HoldKey(DIK_D)) {
		if (holdTimer[3] <= timeOver) {
			holdTimer[3]++;
		}
		if (playerLPos.x <= stopPosX) {
			playerLPos.x += moveSpeed;
		}
		playerRot.y = Easing::easeOut(holdTimer[3], timeOver, initRot.y + stopRotX, playerRot.y);
	}
	else {
		holdTimer[3] = initTime;
	}

	if (!KeyInput::GetIns()->HoldKey(DIK_W) && !KeyInput::GetIns()->HoldKey(DIK_S) && !KeyInput::GetIns()->HoldKey(DIK_A) && !KeyInput::GetIns()->HoldKey(DIK_D)) {
		if (returnTimer <= timeOver * 2) {
			returnTimer++;
		}
		playerRot.x = Easing::easeInOut(returnTimer, timeOver * 2, initRot.x, playerRot.x);
		playerRot.y = Easing::easeInOut(returnTimer, timeOver * 2, initRot.y, playerRot.y);
	}
	else {
		returnTimer = initTime;
	}

}

void Player::Shot() {
	const float bulletSpeed = 5.0f;
	XMVECTOR velocity;
	velocity = { aimPos3d.x - playerWPos.x, aimPos3d.y - playerWPos.y, aimPos3d.z - playerWPos.z };
	velocity = XMVector3Normalize(velocity) * bulletSpeed;

	std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
	newBullet->Initialize(playerWPos, velocity);

	Vector3 gunPos = gun->GetMatWorld().r[3];
	XMVECTOR gunForward = { 0.0f, 0.0f, 1.0f };
	gunForward = XMVector3TransformNormal( gunForward, gun->GetMatWorld() );
	velocity = { 1.0f, 0.4f, 0.0f };
	velocity = XMVector3TransformNormal(velocity, camera->GetMatWorld());

	std::unique_ptr<BulletCase> newBulletCase = std::make_unique<BulletCase>();
	newBulletCase->Initialize(gunPos, velocity, gunForward);

	railScene->AddPlayerBullet(std::move(newBullet));
	railScene->AddBulletCase(std::move(newBulletCase));

	bulletCount--;
	shotCoolTimer = shotCoolTime;
	//sound->PlayWave("Engine/Resources/Sound/SE/short_bomb.wav", false, 0.01f);
}

void Player::BombShot() {
	for (std::unique_ptr<BaseEnemy>& enemy : railScene->GetEnemyObj()) {
		if (enemy->GetIsTarget()) {
			std::unique_ptr<Bomb> newBomb = std::make_unique<Bomb>();
			newBomb->Initialize(playerWPos, enemy->GetEnemyObj());

			railScene->AddBomb(std::move(newBomb));
		}
	}
	
	bombCount--;
	isBomb = false;
}

void Player::Reset() {
	playerScale = { 2, 2, 2 };
	playerLPos = { 0, 0, -50 };
	playerRot = { 0, 180, 0 };

	if (player->GetCameraParent() == nullptr) {
		player->SetCameraParent(camera);
	}
	player->SetPosition(playerLPos);
	player->SetRotation(playerRot);
	bulletCount = 0;
	hpCount = maxHp;
	reloadTimer = reloadTime;
	isDead = false;
	isDamage = false;
	damageEffectTimer = damageEffectTime;
	deadTimer = deadTime;
	clearTimer = clearTime;
}

void Player::AimUpdate() {

	//2D→3D
	aimPos = XMFLOAT2(MouseInput::GetIns()->GetMousePoint().x, MouseInput::GetIns()->GetMousePoint().y);

	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
	XMMATRIX matInverseVPV = XMMatrixInverse(nullptr, matVPV); //ビュープロジェクションビューポート逆行列
	XMVECTOR posNear = { aimPos.x, aimPos.y, 0}; //スクリーン座標
	XMVECTOR posFar = { aimPos.x, aimPos.y, 1 }; //スクリーン座標

	posNear = XMVector3TransformCoord(posNear, matInverseVPV);	
	posFar = XMVector3TransformCoord(posFar, matInverseVPV);

	XMVECTOR mouseDirection = posFar - posNear; //ベクトル
	mouseDirection = XMVector3Normalize(mouseDirection);

	const float kDistanceTestObject = 200.0f; //ベクトルの方向にいくら進ませるか

	XMVECTOR raticle3D;
	raticle3D = posNear + mouseDirection * kDistanceTestObject;
	aimPos3d = raticle3D;

	aim->SetPosition(XMFLOAT2(aimPos.x, aimPos.y));
}

void Player::OnCollision() {
	hpCount--;
	//sound->PlayWave("Engine/Resources/Sound/SE/damage.wav", false, 0.1f);
	//sound->PlayWave("Engine/Resources/Sound/SE/noise.wav", false, 0.1f);
	isDamage = true;
}

void Player::DamageEffect() {
	const int damageEffectTimeOver = 0;

	if (--damageEffectTimer <= damageEffectTimeOver) {
		isDamage = false;
		damageEffectTimer = damageEffectTime;
	}
}

void Player::DeadPerformance() {
	const int32_t deadTimeOver = 0.0f;

	deadTimer--;

	if (deadTimer <= deadTimeOver) {
		isDead = true;
	}

	playerRot.z += 2.0f;
	player->SetRotation(playerRot);
}

void Player::ClearPerformance() {
	const Vector3 endPos = { 0.0f, -40.0f, 0.0f };
	clearTimer--;
	playerWPos.x = Easing::easeInOut(clearTimer, clearTime, playerWPos.x, endPos.x);
	playerWPos.y = Easing::easeOutBack(clearTimer, clearTime, playerWPos.y, endPos.y, 1);
	playerWPos.z = Easing::easeInOut(clearTimer, clearTime, playerWPos.z, endPos.z);
	player->SetCameraParent(nullptr);
	player->SetPosition(playerWPos);
	player->SetRotation(playerRot);
	camera->SetTarget(playerWPos);
}