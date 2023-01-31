#include "BossScenePlayer.h"

const int32_t BossScenePlayer::rotationTime = 30;
const int32_t BossScenePlayer::dashTime = 30;
const int32_t BossScenePlayer::shotCoolTime = 10;
const int32_t BossScenePlayer::reloadTime = 60;
const float BossScenePlayer::boostReloadTime = 80.0f;
const int32_t BossScenePlayer::damageTime = 40;
const int32_t BossScenePlayer::deadTime = 120;

void BossScenePlayer::Initialize(Camera* camera)
{
	//カメラをセット
	this->camera = camera;

	player = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Player_Normal));
	player->SetCameraParent(this->camera);
	pos = { 0.0f, -10.0f, -25.0f };
	rot = { 0.0f, 90.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };

	gun = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Gun));
	gun->SetPosition(Vector3(1.0f, 0.6f, 1.1f));
	gun->SetParent(player);

	aimPos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };
	aim = Sprite::Create(ImageManager::aim, aimPos, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	aim->SetSize(XMFLOAT2(100.0f, 100.0f));
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
	for (int i = 0; i < maxBoostCount; i++) {
		float boostUIPos = 1198.0f;
		boostUIPos -= (float)(i * 87);
		boostUI[i] = Sprite::Create(ImageManager::Boost, { boostUIPos, 616 });
	}
	reloadUI = Sprite::Create(ImageManager::ImageName::reload, { 1065, 652 });

	cameraAngle = 0.0f;
	cameraPos = { 0, -20.0f, 0 };
	cameraPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos, cameraAngle, 250.0f, MotionMath::Y);

	damageTimer = 0;

	camera->SetTarget({ 0.0f, 0.0f, 0.0f });
	camera->SetEye(cameraPos);
	player->SetPosition(pos);
	player->SetRotation(rot);
	player->SetScale(scale);

	rotationTimer = 0;
	shotCoolTimer = 0;
	boostReloadTimer = 0;
	damageTimer = 0;
	reloadTimer = 0;
	jumpPower = 0.0f;
	bulletCount = maxBulletCount;
	boostCount = maxBoostCount;
	hpCount = maxHp;
	deadTimer = 0;
	isDash = false;
	isLeftDash = false;
	isRightDash = false;
	isJump = false;
	isShot = false;
	isReload = false;
	isDead = false;
}

void BossScenePlayer::Update()
{
	const float lowerLimit = -10.0f;
	const int noneHP = 0;

	camera->SetTarget({ 0.0f, 0.0f, 0.0f });
	camera->SetEye(cameraPos);
	player->SetPosition(pos);
	player->SetRotation(rot);
	player->Update();
	playerWPos = player->GetMatWorld().r[3];
	gun->Update();

	if (hpCount > noneHP) {
		if (!isDash) {
			Move();
			Jump();
		}
		Dash();
		AimUpdate();
	}
	
	if (isDamage) {
		DamageEffect();
	}
	if (hpCount <= noneHP) {
		DeadPerformance();
	}
}

void BossScenePlayer::Draw()
{
	const int32_t liveTime = deadTime / 3;
	if (deadTimer <= liveTime) {
		player->Draw();
		gun->Draw();
	}
}

void BossScenePlayer::SpriteDraw()
{
	playerUI->Draw();
	for (int i = 0; i < hpCount; i++) {
		hpUI[i]->Draw();
	}
	for (int i = 0; i < bulletCount; i++) {
		bulletUI[i]->Draw();
	}
	for (int i = 0; i < maxBoostCount; i++) {
		boostUI[i]->Draw();
	}
	if (isReload) {
		reloadUI->Draw();
	}
	aim->Draw();
}

void BossScenePlayer::Finalize() {
	safe_delete(player);
	safe_delete(gun);
	safe_delete(aim);
	safe_delete(playerUI);
	for (int i = 0; i < maxHp; i++) {
		safe_delete(hpUI[i]);
	}
	for (int i = 0; i < maxBulletCount; i++) {
		safe_delete(bulletUI[i]);
	}
	for (int i = 0; i < maxBoostCount; i++) {
		safe_delete(boostUI[i]);
	}
	safe_delete(reloadUI);
}

void BossScenePlayer::OnCollision()
{
	hpCount--;
	//sound->PlayWave("Engine/Resources/Sound/SE/damage.wav", false, 0.1f);
	//sound->PlayWave("Engine/Resources/Sound/SE/noise.wav", false, 0.1f);
	isDamage = true;
}

void BossScenePlayer::Move() {
	const float stopNear = -25.0f;
	const float stopFar = -50.0f;
	const float moveSpeed = 0.5f;

	if (KeyInput::GetIns()->HoldKey(DIK_A) && !KeyInput::GetIns()->HoldKey(DIK_D)) {
		const float leftRot = 90.0f;

		if (rotationTime <= rotationTime) {
			rotationTimer++;
		}
		cameraAngle -= moveSpeed;
		if (cameraAngle <= 0.0f) {
			cameraAngle = 360.0f;
		}
		cameraPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos, cameraAngle, 250.0f, MotionMath::Y);

		if (rot.y <= leftRot) {
			rot.y = Easing::easeIn((float)rotationTimer, (float)rotationTime, leftRot, rot.y);
		}
		else {
			rot.y = leftRot;
		}
	}
	else if (KeyInput::GetIns()->HoldKey(DIK_D) && !KeyInput::GetIns()->HoldKey(DIK_A)) {
		const float rightRot = -90.0f;

		if (rotationTime <= rotationTime) {
			rotationTimer++;
		}
		cameraAngle += moveSpeed;
		if (cameraAngle >= 360.0f) {
			cameraAngle = 0.0f;
		}
		cameraPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos, cameraAngle, 250.0f, MotionMath::Y);

		if (rot.y >= rightRot) {
			rot.y = Easing::easeIn((float)rotationTimer, (float)rotationTime, rightRot, rot.y);
		}
		else {
			rot.y = rightRot;
		}
	}
	else {
		rotationTimer = 0;
	}

	if (KeyInput::GetIns()->HoldKey(DIK_W) && pos.z >= stopFar) {
		pos.z -= moveSpeed;
		player->SetPosition(pos);
	}

	if (KeyInput::GetIns()->HoldKey(DIK_S) && pos.z <= stopNear) {
		pos.z += moveSpeed;
		player->SetPosition(pos);
	}
}

void BossScenePlayer::Dash()
{
	const float moveAngle = 50.0f;
	const int noneBoost = 0;

	if (boostCount < maxBoostCount) {
		const float maxAlpha = 1.0f;
		const float lowerAlpha = 0.1f;
		float alpha = 0;
		int alphaBoost = 2;
		boostReloadTimer++;
		alpha = boostReloadTimer / boostReloadTime;
		if (alpha < lowerAlpha) {
			alpha = lowerAlpha;
		}
		if (boostCount != 2) {
			boostUI[boostCount + 1]->SetAlpha(lowerAlpha);
		}
		boostUI[boostCount]->SetAlpha(alpha);

		if (boostReloadTimer >= boostReloadTime) {
			boostUI[boostCount]->SetAlpha(maxAlpha);
			boostCount++;
			boostReloadTimer = 0;
		}
	}

	if (KeyInput::GetIns()->PushKey(DIK_A) && KeyInput::GetIns()->TriggerKey(DIK_LSHIFT) && !isDash) {
		if (boostCount > noneBoost) {
			isDash = true;
			isLeftDash = true;
			boostReloadTimer = 0;
			boostCount--;
			initAngle = cameraAngle;
		}
	}
	else if (KeyInput::GetIns()->PushKey(DIK_D) && KeyInput::GetIns()->TriggerKey(DIK_LSHIFT) && !isDash) {
		if (boostCount > noneBoost) {
			isDash = true;
			isRightDash = true;
			boostReloadTimer = 0;
			boostCount--;
			initAngle = cameraAngle;
		}
	}

	if (isLeftDash) {
		rot.y = 90.0f;
		dashTimer++;
		if (dashTimer >= dashTime) {
			isDash = false;
			isLeftDash = false;
			dashTimer = 0;
			if (cameraAngle <= 0.0f) {
				cameraAngle = 360.0f + cameraAngle;
			}
		}
		cameraAngle = Easing::easeIn((float)dashTimer, (float)dashTime, initAngle - moveAngle, cameraAngle);
		cameraPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos, cameraAngle, 250.0f, MotionMath::Y);
	}
	if (isRightDash) {
		rot.y = -90.0f;
		dashTimer++;
		if (dashTimer >= dashTime) {
			isDash = false;
			isRightDash = false;
			dashTimer = 0;
			if (cameraAngle >= 360.0f) {
				cameraAngle = cameraAngle - 360.0f;
			}
		}
		cameraAngle = Easing::easeIn((float)dashTimer, (float)dashTime, initAngle + moveAngle, cameraAngle);
		cameraPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos, cameraAngle, 250.0f, MotionMath::Y);
	}

}

void BossScenePlayer::Jump()
{
	const float lowerLimit = -10.0f;

	if (KeyInput::GetIns()->TriggerKey(DIK_SPACE) && !isJump) {
		isJump = true;
		jumpPower = 2.0f;
	}

	pos.y += jumpPower;

	jumpPower -= 0.2f;

	if (pos.y <= lowerLimit) {
		isJump = false;
		pos.y = lowerLimit;
	}
}

void BossScenePlayer::AimUpdate()
{
	const int noneBullet = 0;

	aimPos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };

	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
	XMMATRIX matInverseVPV = XMMatrixInverse(nullptr, matVPV); //ビュープロジェクションビューポート逆行列
	XMVECTOR posNear = { aimPos.x, aimPos.y, 0 }; //スクリーン座標
	XMVECTOR posFar = { aimPos.x, aimPos.y, 1 }; //スクリーン座標

	posNear = XMVector3TransformCoord(posNear, matInverseVPV);
	posFar = XMVector3TransformCoord(posFar, matInverseVPV);

	XMVECTOR mouseDirection = posFar - posNear; //ベクトル
	mouseDirection = XMVector3Normalize(mouseDirection);

	const float kDistanceTestObject = 200.0f; //ベクトルの方向にいくら進ませるか

	XMVECTOR raticle3D;
	raticle3D = posNear + mouseDirection * kDistanceTestObject;
	aim3dPos = raticle3D;

	if (isShot) {
		shotCoolTimer++;
		if (shotCoolTimer >= shotCoolTime) {
			isShot = false;
			shotCoolTimer = 0;
		}
	}

	if (bulletCount < maxBulletCount && KeyInput::GetIns()->TriggerKey(DIK_R)) {
		bulletCount = 0;
	}

	if (bulletCount <= noneBullet) {
		if (!isReload) {
			isReload = true;
			//sound->PlayWave("Engine/Resources/Sound/SE/reload.wav", false, 0.05f);
		}
		reloadTimer++;
		if (reloadTimer >= reloadTime) {
			isReload = false;
			bulletCount = maxBulletCount;
			reloadTimer = 0;
		}
	}

	if (MouseInput::GetIns()->PushClick(MouseInput::LEFT_CLICK) && !isShot && !isReload) {
		isShot = true;
		Shot(aim3dPos);
	}

	aim->SetPosition(aimPos);

}

void BossScenePlayer::Shot(Vector3 mouse3dPos)
{
	const float bulletSpeed = 5.0f;
	XMVECTOR velocity;
	velocity = { aim3dPos.x - playerWPos.x, aim3dPos.y - playerWPos.y, aim3dPos.z - playerWPos.z };
	velocity = XMVector3Normalize(velocity) * bulletSpeed;

	std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
	newBullet->Initialize(playerWPos, velocity);

	bossScene->AddPlayerBullet(std::move(newBullet));

	bulletCount--;
	//sound->PlayWave("Engine/Resources/Sound/SE/short_bomb.wav", false, 0.01f);
}

void BossScenePlayer::DamageEffect()
{
	if (++damageTimer >= damageTime) {
		isDamage = false;
		damageTimer = 0;
	}
}

void BossScenePlayer::DeadPerformance() {
	deadTimer++;
	rot.x -= 2.0f;

	if (deadTimer >= deadTime) {
		isDead = true;
	}
}