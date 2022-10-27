#include "Player.h"
#include "SafeDelete.h"

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

	player = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Player));
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

	bulletCount = 0;
	hpCount = maxHp;
	reloadTimer = reloadTime;
	damageEffectTimer = damageEffectTime;
	shotCoolTimer = 0;
}

void Player::Finalize() {
	safe_delete(player);
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

	if (hpCount <= deadHp) {
		isDead = true;
	}
	if (bulletCount <= noneBulletCount && !isReload) {
		isReload = true;
		sound->PlayWave("Engine/Resources/Sound/SE/reload.wav", false, 0.2f);
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

	if (!isDamage) {
		Move();
	}
	else {
		DamageEffect();
	}

	playerWPos = player->GetMatWorld().r[3];

	AimUpdate();

	if (MouseInput::GetIns()->PushClick(MouseInput::GetIns()->LEFT_CLICK) && !isShot && bulletCount > noneBulletCount && shotCoolTimer <= shotCoolTimeOver) {
		isShot = true;
	}
	if (KeyInput::GetIns()->TriggerKey(DIK_R)) {
		bulletCount = noneBulletCount;
	}

	if (isShot) {
		Shot();
	}

	aim3d->Update();
	player->Update();
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
	sound->PlayWave("Engine/Resources/Sound/SE/short_bomb.wav", false, 0.1f);
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

	//3D��2D
	//const float kDistancePlayerTo3DRaticle = 50.0f;
	//XMVECTOR offset = { 0, 0, 1.0f };
	//offset = MatCalc::GetIns()->VecDivided(offset, player->GetMatWorld());
	//offset = XMVector3Normalize(offset) * kDistancePlayerTo3DRaticle;

	//aimPos3d = playerWPos + offset;

	//XMVECTOR raticle2D = { aim3d->GetMatWorld().r[3] }; //���[���h���W
	//XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //�r���[�v���W�F�N�V�����r���[�|�[�g�s��
	//raticle2D = MatCalc::GetIns()->Wdivided(raticle2D, matViewProjectionViewport); //�X�N���[�����W

	//aimPos = { raticle2D.m128_f32[0], raticle2D.m128_f32[1] };

	//2D��3D
	Vector3 cameraWPos = camera->GetMatWorld().r[3];
	cameraWPos.x = camera->GetEye().x;
	cameraWPos.y = camera->GetEye().y;
	cameraWPos.z = camera->GetEye().z;

	aimPos = XMFLOAT2(MouseInput::GetIns()->GetMousePoint().x, MouseInput::GetIns()->GetMousePoint().y);

	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //�r���[�v���W�F�N�V�����r���[�|�[�g�s��
	XMMATRIX matInverseVPV = XMMatrixInverse(nullptr, matVPV); //�r���[�v���W�F�N�V�����r���[�|�[�g�t�s��
	XMVECTOR posNear = { aimPos.x, aimPos.y, 0}; //���K���f�o�C�X���W
	XMVECTOR posFar = { aimPos.x, aimPos.y, 1 }; //���K���f�o�C�X���W

	posNear = MatCalc::GetIns()->Wdivided(posNear, matInverseVPV); //���[���h���W
	posFar = MatCalc::GetIns()->Wdivided(posFar, matInverseVPV); //���[���h���W

	XMVECTOR mouseDirection = posFar + posNear; //����(�x�N�g��)
	mouseDirection = XMVector3Normalize(mouseDirection);

	const float kDistanceTestObject = 100.0f; //�x�N�g���̕����ɂ�����i�܂��邩
	//mouseDirection = MatCalc::GetIns()->VecDivided(mouseDirection, camera->GetMatWorld());
	aimPos3d = (posNear + mouseDirection * kDistanceTestObject) - cameraWPos;

	aim->SetPosition(XMFLOAT2(aimPos.x, aimPos.y));
	aim3d->SetPosition(-aimPos3d);

}

void Player::OnCollision() {
	//hpCount--;
	sound->PlayWave("Engine/Resources/Sound/SE/damage.wav", false, 0.2f);
	isDamage = true;
}

void Player::DamageEffect() {
	const int damageEffectTimeOver = 0;
	static Vector3 oldPos;

	if (oldPos.x == 0 && oldPos.y == 0 && oldPos.z == 0) {
		oldPos = playerLPos;
	}

	damageEffectTimer--;

	if (damageEffectTimer >= damageEffectTimeOver) {
		playerLPos.x = playerLPos.x + (2 - rand() % 4);
		playerLPos.y = playerLPos.y + (2 - rand() % 4);
		playerLPos.z = playerLPos.z + (2 - rand() % 4);
	}
	else {
		isDamage = false;
		damageEffectTimer = damageEffectTime;
		playerLPos = oldPos;
		oldPos = { 0, 0, 0 };
	}
}