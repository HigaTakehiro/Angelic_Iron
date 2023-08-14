#include "BossScenePlayer.h"

using namespace DirectX;

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
	camera_ = camera;

	player_ = Object3d::Create(ModelManager::GetIns()->GetModel("player_Normal"));
	player_->SetCameraParent(camera_);
	player_->SetObjType((int32_t)Object3d::OBJType::Player);
	player_->SetHitRadius(5.0f);
	player_->SetColType(Object3d::CollisionType::Sphere);
	pos_ = { 0.0f, -10.0f, -25.0f };
	rot_ = { 0.0f, 90.0f, 0.0f };
	scale_ = { 1.0f, 1.0f, 1.0f };

	gun_ = Object3d::Create(ModelManager::GetIns()->GetModel("gun"));
	gun_->SetPosition(Vector3(1.0f, 0.6f, 1.1f));
	gun_->SetParent(player_);

	aimPos_ = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };
	playerUI_ = Sprite::Create((UINT)ImageManager::ImageName::playerUI, { 1000, 650 });
	for (int32_t i = 0; i < maxHp; i++) {
		float hpUiXPos = 1178.0f;
		hpUiXPos -= (float)(i * 87);
		hpUI_[i] = Sprite::Create((UINT)ImageManager::ImageName::playerHP, { hpUiXPos, 688 });
	}
	for (int32_t i = 0; i < maxBulletCount; i++) {
		float bulletUiPos = 1242.0f;
		bulletUiPos -= (float)(i * 16);
		bulletUI_[i] = Sprite::Create((UINT)ImageManager::ImageName::playerBullet, { bulletUiPos, 652 });
	}
	for (int32_t i = 0; i < maxBoostCount; i++) {
		float boostUIPos = 1198.0f;
		boostUIPos -= (float)(i * 87);
		boostUI_[i] = Sprite::Create((UINT)ImageManager::ImageName::Boost, { boostUIPos, 616 });
	}
	reloadUI_ = Sprite::Create((UINT)ImageManager::ImageName::reload, { 1065, 652 });

	cameraAngle_ = 0.0f;
	cameraPos_ = { 0, -20.0f, 0 };
	cameraPos_ = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos_, cameraAngle_, 250.0f, MotionMath::Y);

	camera_->SetTarget({ 0.0f, 0.0f, 0.0f });
	camera_->SetEye(cameraPos_);
	player_->SetPosition(pos_);
	player_->SetRotation(rot_);
	player_->SetScale(scale_);

	rotationTimer_ = 0;
	shotCoolTimer_ = 0;
	boostReloadTimer_ = 0;
	damageTimer_ = 0;
	reloadTimer_ = 0;
	jumpPower_ = 0.0f;
	bulletCount_ = maxBulletCount;
	boostCount_ = maxBoostCount;
	hpCount_ = maxHp;
	deadTimer_ = 0;
	isDash_ = false;
	isLeftDash_ = false;
	isRightDash_ = false;
	isJump_ = false;
	isShot_ = false;
	isReload_ = false;
	isDead_ = false;
}

void BossScenePlayer::Update()
{
	const float lowerLimit = -10.0f;
	const int32_t noneHP = 0;

	camera_->SetTarget({ 0.0f, 0.0f, 0.0f });
	camera_->SetEye(cameraPos_);
	player_->SetPosition(pos_);
	player_->SetRotation(rot_);
	playerWPos_ = player_->GetMatWorld().r[3];

	if (player_->GetIsHit()) {
		OnCollision();
	}

	if (hpCount_ > noneHP) {
		if (!isDash_) {
			Move();
			Jump();
		}
		Dash();
		AimUpdate();
	}
	
	if (isDamage_) {
		DamageEffect();
	}
	if (hpCount_ <= noneHP) {
		DeadPerformance();
	}

	player_->Update();
	gun_->Update();
}

void BossScenePlayer::Draw()
{
	const int32_t liveTime = deadTime / 3;
	if (deadTimer_ <= liveTime) {
		player_->Draw();
		gun_->Draw();
	}
}

void BossScenePlayer::SpriteDraw()
{
	playerUI_->Draw();
	for (int32_t i = 0; i < hpCount_; i++) {
		hpUI_[i]->Draw();
	}
	for (int32_t i = 0; i < bulletCount_; i++) {
		bulletUI_[i]->Draw();
	}
	for (int32_t i = 0; i < maxBoostCount; i++) {
		boostUI_[i]->Draw();
	}
	if (isReload_) {
		reloadUI_->Draw();
	}
}

void BossScenePlayer::Finalize() {
	safe_delete(player_);
	safe_delete(gun_);
	safe_delete(playerUI_);
	for (int32_t i = 0; i < maxHp; i++) {
		safe_delete(hpUI_[i]);
	}
	for (int32_t i = 0; i < maxBulletCount; i++) {
		safe_delete(bulletUI_[i]);
	}
	for (int32_t i = 0; i < maxBoostCount; i++) {
		safe_delete(boostUI_[i]);
	}
	safe_delete(reloadUI_);
}

void BossScenePlayer::OnCollision()
{
	if (!isDamage_) {
		hpCount_--;
		//sound->PlayWave("Engine/Resources/Sound/SE/damage.wav", false, 0.1f);
		//sound->PlayWave("Engine/Resources/Sound/SE/noise.wav", false, 0.1f);
		isDamage_ = true;
	}
}

void BossScenePlayer::Move() {
	const float stopNear = -25.0f;
	const float stopFar = -50.0f;
	const float moveSpeed = 0.5f;

	if (KeyInput::GetIns()->HoldKey(DIK_A) && !KeyInput::GetIns()->HoldKey(DIK_D)) {
		const float leftRot = 90.0f;

		if (rotationTime <= rotationTime) {
			rotationTimer_++;
		}
		cameraAngle_ -= moveSpeed;
		if (cameraAngle_ <= 0.0f) {
			cameraAngle_ = 360.0f;
		}
		cameraPos_ = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos_, cameraAngle_, 250.0f, MotionMath::Y);

		if (rot_.y <= leftRot) {
			rot_.y = Easing::easeIn((float)rotationTimer_, (float)rotationTime, leftRot, rot_.y);
		}
		else {
			rot_.y = leftRot;
		}
	}
	else if (KeyInput::GetIns()->HoldKey(DIK_D) && !KeyInput::GetIns()->HoldKey(DIK_A)) {
		const float rightRot = -90.0f;

		if (rotationTime <= rotationTime) {
			rotationTimer_++;
		}
		cameraAngle_ += moveSpeed;
		if (cameraAngle_ >= 360.0f) {
			cameraAngle_ = 0.0f;
		}
		cameraPos_ = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos_, cameraAngle_, 250.0f, MotionMath::Y);

		if (rot_.y >= rightRot) {
			rot_.y = Easing::easeIn((float)rotationTimer_, (float)rotationTime, rightRot, rot_.y);
		}
		else {
			rot_.y = rightRot;
		}
	}
	else {
		rotationTimer_ = 0;
	}

	if (KeyInput::GetIns()->HoldKey(DIK_W) && pos_.z >= stopFar) {
		pos_.z -= moveSpeed;
		player_->SetPosition(pos_);
	}

	if (KeyInput::GetIns()->HoldKey(DIK_S) && pos_.z <= stopNear) {
		pos_.z += moveSpeed;
		player_->SetPosition(pos_);
	}
}

void BossScenePlayer::Dash()
{
	const float moveAngle = 50.0f;
	const int32_t noneBoost = 0;

	if (boostCount_ < maxBoostCount) {
		const float maxAlpha = 1.0f;
		const float lowerAlpha = 0.1f;
		float alpha = 0;
		int32_t alphaBoost = 2;
		boostReloadTimer_++;
		alpha = boostReloadTimer_ / boostReloadTime;
		if (alpha < lowerAlpha) {
			alpha = lowerAlpha;
		}
		if (boostCount_ != 2) {
			boostUI_[boostCount_ + 1]->SetAlpha(lowerAlpha);
		}
		boostUI_[boostCount_]->SetAlpha(alpha);

		if (boostReloadTimer_ >= boostReloadTime) {
			boostUI_[boostCount_]->SetAlpha(maxAlpha);
			boostCount_++;
			boostReloadTimer_ = 0;
		}
	}

	if (KeyInput::GetIns()->PushKey(DIK_A) && KeyInput::GetIns()->TriggerKey(DIK_LSHIFT) && !isDash_) {
		if (boostCount_ > noneBoost) {
			isDash_ = true;
			isLeftDash_ = true;
			boostReloadTimer_ = 0;
			boostCount_--;
			initAngle_ = cameraAngle_;
		}
	}
	else if (KeyInput::GetIns()->PushKey(DIK_D) && KeyInput::GetIns()->TriggerKey(DIK_LSHIFT) && !isDash_) {
		if (boostCount_ > noneBoost) {
			isDash_ = true;
			isRightDash_ = true;
			boostReloadTimer_ = 0;
			boostCount_--;
			initAngle_ = cameraAngle_;
		}
	}

	if (isLeftDash_) {
		rot_.y = 90.0f;
		dashTimer_++;
		if (dashTimer_ >= dashTime) {
			isDash_ = false;
			isLeftDash_ = false;
			dashTimer_ = 0;
			if (cameraAngle_ <= 0.0f) {
				cameraAngle_ = 360.0f + cameraAngle_;
			}
		}
		cameraAngle_ = Easing::easeIn((float)dashTimer_, (float)dashTime, initAngle_ - moveAngle, cameraAngle_);
		cameraPos_ = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos_, cameraAngle_, 250.0f, MotionMath::Y);
	}
	if (isRightDash_) {
		rot_.y = -90.0f;
		dashTimer_++;
		if (dashTimer_ >= dashTime) {
			isDash_ = false;
			isRightDash_ = false;
			dashTimer_ = 0;
			if (cameraAngle_ >= 360.0f) {
				cameraAngle_ = cameraAngle_ - 360.0f;
			}
		}
		cameraAngle_ = Easing::easeIn((float)dashTimer_, (float)dashTime, initAngle_ + moveAngle, cameraAngle_);
		cameraPos_ = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos_, cameraAngle_, 250.0f, MotionMath::Y);
	}

}

void BossScenePlayer::Jump()
{
	const float lowerLimit = -10.0f;

	if (KeyInput::GetIns()->TriggerKey(DIK_SPACE) && !isJump_) {
		isJump_ = true;
		jumpPower_ = 2.0f;
	}

	pos_.y += jumpPower_;

	jumpPower_ -= 0.2f;

	if (pos_.y <= lowerLimit) {
		isJump_ = false;
		pos_.y = lowerLimit;
	}
}

void BossScenePlayer::AimUpdate()
{
	const int32_t noneBullet = 0;

	aimPos_ = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };

	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
	XMMATRIX matInverseVPV = XMMatrixInverse(nullptr, matVPV); //ビュープロジェクションビューポート逆行列
	XMVECTOR posNear = { aimPos_.x, aimPos_.y, 0 }; //スクリーン座標
	XMVECTOR posFar = { aimPos_.x, aimPos_.y, 1 }; //スクリーン座標

	posNear = XMVector3TransformCoord(posNear, matInverseVPV);
	posFar = XMVector3TransformCoord(posFar, matInverseVPV);

	XMVECTOR mouseDirection = posFar - posNear; //ベクトル
	mouseDirection = XMVector3Normalize(mouseDirection);

	const float kDistanceTestObject = 200.0f; //ベクトルの方向にいくら進ませるか

	XMVECTOR raticle3D;
	raticle3D = posNear + mouseDirection * kDistanceTestObject;
	aim3dPos_ = raticle3D;

	if (isShot_) {
		shotCoolTimer_++;
		if (shotCoolTimer_ >= shotCoolTime) {
			isShot_ = false;
			shotCoolTimer_ = 0;
		}
	}

	if (bulletCount_ < maxBulletCount && KeyInput::GetIns()->TriggerKey(DIK_R)) {
		bulletCount_ = 0;
	}

	if (bulletCount_ <= noneBullet) {
		if (!isReload_) {
			isReload_ = true;
			//sound->PlayWave("Engine/Resources/Sound/SE/reload.wav", false, 0.05f);
		}
		reloadTimer_++;
		if (reloadTimer_ >= reloadTime) {
			isReload_ = false;
			bulletCount_ = maxBulletCount;
			reloadTimer_ = 0;
		}
	}

	if (MouseInput::GetIns()->PushClick(MouseInput::MouseState::LEFT_CLICK) && !isShot_ && !isReload_) {
		isShot_ = true;
		Shot(aim3dPos_);
	}

}

void BossScenePlayer::Shot(Vector3 mouse3dPos)
{
	const float bulletSpeed = 5.0f;
	XMVECTOR velocity;
	velocity = { aim3dPos_.x - playerWPos_.x, aim3dPos_.y - playerWPos_.y, aim3dPos_.z - playerWPos_.z };
	velocity = XMVector3Normalize(velocity) * bulletSpeed;

	std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
	newBullet->Initialize(playerWPos_, velocity);

	bulletManager_->AddPlayerBullet(std::move(newBullet));

	bulletCount_--;
	//sound->PlayWave("Engine/Resources/Sound/SE/short_bomb.wav", false, 0.01f);
}

void BossScenePlayer::DamageEffect()
{
	if (++damageTimer_ >= damageTime) {
		isDamage_ = false;
		damageTimer_ = 0;
	}
}

void BossScenePlayer::DeadPerformance() {
	deadTimer_++;
	rot_.x -= 2.0f;

	if (deadTimer_ >= deadTime) {
		isDead_ = true;
	}
}