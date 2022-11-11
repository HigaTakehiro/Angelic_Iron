#include "Player.h"
#include "SafeDelete.h"
#include "MotionMath.h"

void Player::Initialize(Camera* camera, Sound* sound) {
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

void Player::Update() {
	const int deadHp = 0;
	const int noneBulletCount = 0;
	const int reloadTimeOver = 0;
	const int shotCoolTimeOver = 0;
	static float angle = 0.0f;
	Vector3 gunPos = { 0.0f, 0.0f, 0.0f };

	angle++;
	if (angle >= 360.0f) {
		angle = 0;
	}

	gunPos = MotionMath::GetIns()->CircularMotion(playerWPos, gunPos, angle, 10.0f, MotionMath::Z);
	//gun->SetPosition(gunPos);

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
	Move();

	playerWPos = player->GetMatWorld().r[3];

	AimUpdate();

	if (MouseInput::GetIns()->PushClick(MouseInput::GetIns()->LEFT_CLICK) && !isShot && bulletCount > noneBulletCount && shotCoolTimer <= shotCoolTimeOver) {
		isShot = true;
	}
	if (KeyInput::GetIns()->TriggerKey(DIK_R) && bulletCount != maxBulletCount) {
		bulletCount = noneBulletCount;
	}

	if (isShot) {
		Shot();
	}

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
	player->Draw();
	aim3d->Draw();
	gun->Draw();
}

void Player::Move() {
	const float moveSpeed = 2.0f;
	const float autoSpeed = 0.2;
	const float playerAngle = 180.0f;
	const float stopAngleY = 45.0f;
	const float stopAngleX = 30.0f;
	const float stopPosX = 40.0f;
	const float stopPosY = 20.0f;

	//aimPos3d.z = -100.0f;

	if (KeyInput::GetIns()->PushKey(DIK_W) && playerLPos.y <= stopPosY) {
		playerLPos.y += moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_S) && playerLPos.y >= -stopPosY) {
		playerLPos.y -= moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_A) && playerLPos.x <= stopPosX) {
		playerLPos.x += moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_D) && playerLPos.x >= -stopPosX) {
		playerLPos.x -= moveSpeed;
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
	//aim3d->SetPosition(aimPos3d);
}

void Player::Shot() {
	const float bulletSpeed = 5.0f;
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

	player->SetPosition(playerLPos);
	bulletCount = 0;
	hpCount = maxHp;
	reloadTimer = reloadTime;
	isDead = false;
	isDamage = false;
	damageEffectTimer = damageEffectTime;
}

void Player::AimUpdate() {

	//3D→2D
	//const float kDistancePlayerTo3DRaticle = 50.0f;
	//XMVECTOR offset = { 0, 0, 1.0f };
	//offset = MatCalc::GetIns()->VecDivided(offset, player->GetMatWorld());
	//offset = XMVector3Normalize(offset) * kDistancePlayerTo3DRaticle;

	//aimPos3d = playerWPos + offset;

	//XMVECTOR raticle2D = { aim3d->GetMatWorld().r[3] }; //ワールド座標
	//XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
	//raticle2D = MatCalc::GetIns()->WDivided(raticle2D, matViewProjectionViewport); //スクリーン座標

	//aimPos = { raticle2D.m128_f32[0], raticle2D.m128_f32[1] };

	//2D→3D
	aimPos = XMFLOAT2(MouseInput::GetIns()->GetMousePoint().x, MouseInput::GetIns()->GetMousePoint().y);

	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
	XMMATRIX matInverseVPV = XMMatrixInverse(nullptr, matVPV); //ビュープロジェクションビューポート逆行列
	XMVECTOR posNear = { aimPos.x, aimPos.y, 0}; //スクリーン座標
	XMVECTOR posFar = { aimPos.x, aimPos.y, 1 }; //スクリーン座標

	posNear = MatCalc::GetIns()->PosDivided(posNear, XMMatrixInverse(nullptr, camera->GetMatViewPort())); //正規化デバイス座標
	posNear = MatCalc::GetIns()->PosDivided(posNear, XMMatrixInverse(nullptr, camera->GetMatProjection())); //プロジェクション座標
	posNear = MatCalc::GetIns()->WDivision(posNear, true);
	posNear = MatCalc::GetIns()->PosDivided(posNear, XMMatrixInverse(nullptr, camera->GetMatView()));
	posNear.m128_f32[2] = 0;

	posFar = MatCalc::GetIns()->PosDivided(posFar, XMMatrixInverse(nullptr, camera->GetMatViewPort()));
	posFar = MatCalc::GetIns()->PosDivided(posFar, XMMatrixInverse(nullptr, camera->GetMatProjection())); //正規化デバイス座標
	posFar = MatCalc::GetIns()->WDivision(posFar, true);
	posFar = MatCalc::GetIns()->PosDivided(posFar, XMMatrixInverse(nullptr, camera->GetMatView()));

	XMVECTOR mouseDirection = posFar - posNear; //ベクトル
	mouseDirection = XMVector3Normalize(mouseDirection);

	const float kDistanceTestObject = 100.0f; //ベクトルの方向にいくら進ませるか

	XMVECTOR raticle3D;
	raticle3D = posNear - mouseDirection * kDistanceTestObject;
	//raticle3D = MatCalc::GetIns()->PosDivided(raticle3D, player->GetMatWorld());
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
	static int32_t deadTime = 60.0f;

	if (deadTime <= deadTimeOver) {
		deadTime = 60.0f;
	}

	deadTime--;

	if (deadTime <= deadTimeOver) {
		isDead = true;
	}
}