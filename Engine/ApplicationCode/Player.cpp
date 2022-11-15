#include "Player.h"
#include "SafeDelete.h"
#include "MotionMath.h"
#include "Easing.h"

void Player::Initialize(Camera* camera, Sound* sound, float clearTime) {
	this->camera = camera;
	this->sound = sound;

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
	playerLPos = { 0, 0, -50 };
	playerRot = { 0, 180, 0 };
	player->SetScale(playerScale);
	player->SetPosition(playerLPos);
	player->SetRotation(playerRot);
	player->SetCameraParent(camera);

	aim3d = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Shot));
	aim3d->SetScale(Vector3(3, 3, 3));
	aim3d->SetPosition(Vector3(0, 0, -100));
	aim3d->SetRotation(Vector3(0, 0, 0));
	//aim3d->SetParent(player);
	//aim3d->SetCameraParent(camera);

	gun = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Gun));
	gun->SetPosition(Vector3(1, 0.6, 1.1));
	gun->SetParent(player);

	bulletCount = 0;
	hpCount = maxHp;
	reloadTimer = reloadTime;
	damageEffectTimer = damageEffectTime;
	shotCoolTimer = 0;

	this->clearTime = clearTime;
	clearTimer = this->clearTime;
	deadTimer = deadTime;
	returnTimer = 0;
	for (int i = 0; i < 4; i++) {
		holdTimer[i] = 0;
	}
}

void Player::Finalize() {
	safe_delete(player);
	safe_delete(gun);
	safe_delete(aim);
	safe_delete(aim3d);
	safe_delete(playerUI);
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

	if (!isClear) {
		if (hpCount <= deadHp) {
			DeadPerformance();
		}
		if (bulletCount <= noneBulletCount && !isReload) {
			isReload = true;
			sound->PlayWave("Engine/Resources/Sound/SE/reload.wav", false, 0.05f);
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

		if (isDamage) {
			DamageEffect();
		}
		if (hpCount > deadHp) {
			Move();
		}

		playerWPos = player->GetMatWorld().r[3];


		if ((KeyInput::GetIns()->PushKey(DIK_SPACE) || MouseInput::GetIns()->PushClick(MouseInput::LEFT_CLICK)) && !isShot && bulletCount > noneBulletCount && shotCoolTimer <= shotCoolTimeOver) {
			isShot = true;
		}
		if (KeyInput::GetIns()->TriggerKey(DIK_R) && bulletCount != maxBulletCount) {
			bulletCount = noneBulletCount;
		}

		if (isShot) {
			Shot();
		}
	}
	else {
		ClearPerformance();
	}

	AimUpdate();

	aim3d->Update();
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
	aim3d->Draw();
}

void Player::Move() {
	const float moveSpeed = 1.0f;
	const float stopPosX = 40.0f;
	const float stopPosY = 20.0f;
	const float stopRotX = 30.0f;
	const float stopRotY = 50.0f;
	const Vector3 initRot = { 0, 180, 0 };
	const float timeOver = 100.0f;
	const float initTime = 0.0f;

	if (KeyInput::GetIns()->HoldKey(DIK_W)) {
		if (holdTimer[0] <= timeOver) {
			holdTimer[0]++;
		}
		if (playerLPos.y <= stopPosY) {
			playerLPos.y += moveSpeed;
		}
		playerRot.x = Easing::GetIns()->easeOut(holdTimer[0], timeOver, initRot.x - stopRotX, playerRot.x);
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
		playerRot.x = Easing::GetIns()->easeOut(holdTimer[1], timeOver, initRot.x + stopRotX, playerRot.x);
	}
	else {
		holdTimer[1] = initTime;
	}
	if (KeyInput::GetIns()->HoldKey(DIK_A)) {
		if (holdTimer[2] <= timeOver) {
			holdTimer[2]++;
		}
		if (playerLPos.x <= stopPosX) {
			playerLPos.x += moveSpeed;
		}
		playerRot.y = Easing::GetIns()->easeOut(holdTimer[2], timeOver, initRot.y - stopRotY, playerRot.y);
	}
	else {
		holdTimer[2] = initTime;
	}
	if (KeyInput::GetIns()->HoldKey(DIK_D)) {
		if (holdTimer[3] <= timeOver) {
			holdTimer[3]++;
		}
		if (playerLPos.x >= -stopPosX) {
			playerLPos.x -= moveSpeed;
		}
		playerRot.y = Easing::GetIns()->easeOut(holdTimer[3], timeOver, initRot.y + stopRotX, playerRot.y);
	}
	else {
		holdTimer[3] = initTime;
	}

	if (!KeyInput::GetIns()->HoldKey(DIK_W) && !KeyInput::GetIns()->HoldKey(DIK_S) && !KeyInput::GetIns()->HoldKey(DIK_A) && !KeyInput::GetIns()->HoldKey(DIK_D)) {
		if (returnTimer <= timeOver * 2) {
			returnTimer++;
		}
		playerRot.x = Easing::GetIns()->easeInOut(returnTimer, timeOver * 2, initRot.x, playerRot.x);
		playerRot.y = Easing::GetIns()->easeInOut(returnTimer, timeOver * 2, initRot.y, playerRot.y);
	}
	else {
		returnTimer = initTime;
	}
	//if (KeyInput::GetIns()->PushKey(DIK_LEFT) && aimPos3d.x <= stopPosX * 2) {
	//	aimPos3d.x += moveSpeed;
	//}
	//if (KeyInput::GetIns()->PushKey(DIK_RIGHT) && aimPos3d.x >= -stopPosX * 2) {
	//	aimPos3d.x -= moveSpeed;
	//}
	//if (KeyInput::GetIns()->PushKey(DIK_UP) && aimPos3d.y <= stopPosY * 2) {
	//	aimPos3d.y += moveSpeed;
	//}
	//if (KeyInput::GetIns()->PushKey(DIK_DOWN) && aimPos3d.y >= -stopPosY * 2) {
	//	aimPos3d.y -= moveSpeed;
	//}

	player->SetPosition(playerLPos);
	player->SetRotation(playerRot);
	//aim3d->SetPosition(aimPos3d);
}

void Player::Shot() {
	const float bulletSpeed = 10.0f;
	XMVECTOR velocity;
	velocity = { aim3d->GetMatWorld().r[3] - player->GetMatWorld().r[3] };
	velocity = XMVector3Normalize(velocity) * bulletSpeed;

	std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
	newBullet->Initialize(playerWPos, velocity);

	gameScene->AddPlayerBullet(std::move(newBullet));

	bulletCount--;
	shotCoolTimer = shotCoolTime;
	sound->PlayWave("Engine/Resources/Sound/SE/short_bomb.wav", false, 0.01f);
	isShot = false;
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

	XMMATRIX proj = Camera::GetMatProjection();

	posNear = XMVector3TransformCoord(posNear, matInverseVPV);	
	posFar = XMVector3TransformCoord(posFar, matInverseVPV);

	XMVECTOR mouseDirection = posFar - posNear; //ベクトル
	mouseDirection = XMVector3Normalize(mouseDirection);

	const float kDistanceTestObject = 1000.0f; //ベクトルの方向にいくら進ませるか

	XMVECTOR raticle3D;
	raticle3D = posNear + mouseDirection * kDistanceTestObject;
	aimPos3d = raticle3D;

	aim->SetPosition(XMFLOAT2(aimPos.x, aimPos.y));
	aim3d->SetPosition(aimPos3d);

}

void Player::OnCollision() {
	hpCount--;
	sound->PlayWave("Engine/Resources/Sound/SE/damage.wav", false, 0.1f);
	sound->PlayWave("Engine/Resources/Sound/SE/noise.wav", false, 0.1f);
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
	playerWPos.y = Easing::GetIns()->easeOutBack(clearTimer, clearTime, playerWPos.y, endPos.y);
	player->SetCameraParent(nullptr);
	player->SetPosition(playerWPos);
	player->SetRotation(playerRot);
	camera->SetTarget(playerWPos);
}