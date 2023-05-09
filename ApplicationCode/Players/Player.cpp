#include "Player.h"
#include "SafeDelete.h"
#include "MotionMath.h"
#include "Easing.h"

void Player::Initialize(Camera* camera, float clearTime) {
	camera_ = camera;

	playerUI_ = Sprite::Create((UINT)ImageManager::ImageName::playerUI, { 1000, 650 });
	for (int i = 0; i < maxHp; i++) {
		float hpUiXPos = 1178.0f;
		hpUiXPos -= (float)(i * 87);
		hpUI_[i] = Sprite::Create((UINT)ImageManager::ImageName::playerHP, { hpUiXPos, 688 });
	}
	for (int i = 0; i < maxBulletCount; i++) {
		float bulletUiPos = 1242.0f;
		bulletUiPos -= (float)(i * 16);
		bulletUI_[i] = Sprite::Create((UINT)ImageManager::ImageName::playerBullet, { bulletUiPos, 652 });
	}
	reloadUI_ = Sprite::Create((UINT)ImageManager::ImageName::reload, { 1065, 652 });

	player_ = Object3d::Create(ModelManager::GetIns()->GetModel("player_Normal"));
	playerScale_ = { 2, 2, 2 };
	playerLPos_ = { 0, 200, 50 };
	playerRot_ = { 90, 0, 0 };
	player_->SetScale(playerScale_);
	player_->SetPosition(playerLPos_);
	player_->SetRotation(playerRot_);
	player_->SetCameraParent(camera_);

	for (int i = 0; i < 3; i++) {
		bomb_[i] = Sprite::Create((UINT)ImageManager::ImageName::Bomb, { 1050.0f + (float)(i * 80), 600.0f });
		bomb_[i]->SetAnchorPoint({ 0.5f, 0.5f });
	}

	gun_ = Object3d::Create(ModelManager::GetIns()->GetModel("gun"));
	gun_->SetPosition(Vector3(1.0f, 0.6f, 1.1f));
	gun_->SetParent(player_);

	bulletCount_ = 0;
	hpCount_ = maxHp;
	reloadTimer_ = reloadTime;
	damageEffectTimer_ = damageEffectTime;
	shotCoolTimer_ = 0;

	bombCount_ = 3;
	bombTimer_ = bombTime;

	clearTime_ = clearTime;
	clearTimer_ = clearTime_;
	deadTimer_ = deadTime;
	startTimer_ = 0;
	returnTimer_ = 0;
	for (int i = 0; i < 4; i++) {
		holdTimer_[i] = 0;
	}

	shotDistance_ = 200.0f;
	controller_ = new KeyInputHandler;
	controller_->Initialize(this);
}

void Player::Finalize() {
	safe_delete(player_);
	safe_delete(gun_);
	safe_delete(playerUI_);
	for (int i = 0; i < 3; i++) {
		safe_delete(bomb_[i]);
	}
	for (int i = 0; i < maxHp; i++) {
		safe_delete(hpUI_[i]);
	}
	for (int i = 0; i < maxBulletCount; i++) {
		safe_delete(bulletUI_[i]);
	}
	safe_delete(reloadUI_);
	safe_delete(controller_);
}

void Player::Update(bool isClear) {
	const int32_t deadHp = 0;
	const int32_t reloadTimeOver = 0;
	const int32_t shotCoolTimeOver = 0;

	if (isBomb_) {
		controller_->KeyBindChange_LeftClick(KeyInputHandler::Commands::None);
	}
	else {
		controller_->KeyBindChange_LeftClick(KeyInputHandler::Commands::Shot);
	}

	StartPerformance();

	if (!isClear) {
		PlayerPosCorrection();
		if (hpCount_ <= deadHp) {
			DeadPerformance();
		}
		if (bulletCount_ <= noneBulletCount && !isReload_) {
			isReload_ = true;
			//sound->PlayWave("Engine/Resources/Sound/SE/reload.wav", false, 0.05f);
		}
		if (isReload_) {
			reloadTimer_--;
		}
		if (reloadTimer_ <= reloadTimeOver) {
			isReload_ = false;
			bulletCount_ = maxBulletCount;
			reloadTimer_ = reloadTime;
		}
		if (shotCoolTimer_ > shotCoolTimeOver) {
			shotCoolTimer_--;
		}
		else if (shotCoolTimer_ <= shotCoolTimeOver) {
			isShot_ = false;
			shotCoolTimer_ = 0;
		}

		if (isBomb_) {
			bombTimer_--;
			if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::LEFT_CLICK) || bombTimer_ <= 0) {
				BombShot();
			}
		}

		if (isDamage_) {
			DamageEffect();
		}
		if (hpCount_ > deadHp && isStart_) {
			controller_->PlayerHandleInput();
		}

		playerWPos_ = player_->GetMatWorld().r[3];

		player_->SetPosition(playerLPos_);
		player_->SetRotation(playerRot_);
	}
	else {
		ClearPerformance();
	}

	AimUpdate();
	player_->Update();
	gun_->Update();
}

void Player::SpriteDraw() {
	playerUI_->Draw();
	for (int i = 0; i < hpCount_; i++) {
		hpUI_[i]->Draw();
	}
	for (int i = 0; i < bulletCount_; i++) {
		bulletUI_[i]->Draw();
	}
	for (int i = 0; i < bombCount_; i++) {
		bomb_[i]->Draw();
	}
	if (isReload_) {
		reloadUI_->Draw();
	}
}

void Player::ObjectDraw() {
	const int32_t liveTime = (int32_t)(deadTime / 1.2);
	if (deadTimer_ >= liveTime) {
		player_->Draw();
		gun_->Draw();
	}
}

void Player::Shot() {
	if (bulletCount_ <= noneBulletCount) return;
	if (isBomb_) return;
	if (isShot_) return;

	const float bulletSpeed = 5.0f;
	XMVECTOR velocity;
	velocity = { aimPos3d_.x - playerWPos_.x, aimPos3d_.y - playerWPos_.y, aimPos3d_.z - playerWPos_.z };
	velocity = XMVector3Normalize(velocity) * bulletSpeed;

	std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
	newBullet->Initialize(playerWPos_, velocity);

	Vector3 gunPos = gun_->GetMatWorld().r[3];
	XMVECTOR gunForward = { 0.0f, 0.0f, 1.0f };
	gunForward = XMVector3TransformNormal( gunForward, gun_->GetMatWorld() );
	velocity = { 1.0f, 0.4f, 0.0f };
	velocity = XMVector3TransformNormal(velocity, camera_->GetMatWorld());

	std::unique_ptr<BulletCase> newBulletCase = std::make_unique<BulletCase>();
	newBulletCase->Initialize(gunPos, velocity, gunForward);

	railScene_->AddPlayerBullet(std::move(newBullet));
	railScene_->AddBulletCase(std::move(newBulletCase));

	bulletCount_--;
	shotCoolTimer_ = shotCoolTime;
	//sound->PlayWave("Engine/Resources/Sound/SE/short_bomb.wav", false, 0.01f);
	isShot_ = true;
}

void Player::SetBombMode()
{
	const int32_t noneBomb = 0;
	if(bombCount_ > noneBomb) isBomb_ = true;
}

void Player::Reload()
{
	if (bulletCount_ < maxBulletCount && bulletCount_ > noneBulletCount) bulletCount_ = noneBulletCount;
}

void Player::BombShot() {
	bombTimer_ = bombTime;

	for (std::unique_ptr<BaseEnemy>& enemy : railScene_->GetEnemyObj()) {
		if (enemy->GetIsTarget()) {
			std::unique_ptr<Bomb> newBomb = std::make_unique<Bomb>();
			newBomb->Initialize(playerWPos_, enemy->GetEnemyObj());

			railScene_->AddBomb(std::move(newBomb));
		}
	}
	
	bombCount_--;
	isBomb_ = false;
}

void Player::Reset() {
	playerScale_ = { 2, 2, 2 };
	playerLPos_ = { 0, 0, -50 };
	playerRot_ = { 0, 180, 0 };

	if (player_->GetCameraParent() == nullptr) {
		player_->SetCameraParent(camera_);
	}
	player_->SetPosition(playerLPos_);
	player_->SetRotation(playerRot_);
	bulletCount_ = 0;
	hpCount_ = maxHp;
	reloadTimer_ = reloadTime;
	isDead_ = false;
	isDamage_ = false;
	damageEffectTimer_ = damageEffectTime;
	deadTimer_ = deadTime;
	clearTimer_ = clearTime_;
}

void Player::AimUpdate() {

	//2D→3D
	aimPos_ = XMFLOAT2((float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y);

	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
	XMMATRIX matInverseVPV = XMMatrixInverse(nullptr, matVPV); //ビュープロジェクションビューポート逆行列
	XMVECTOR posNear = { aimPos_.x, aimPos_.y, 0}; //スクリーン座標
	XMVECTOR posFar = { aimPos_.x, aimPos_.y, 1 }; //スクリーン座標

	posNear = XMVector3TransformCoord(posNear, matInverseVPV);	
	posFar = XMVector3TransformCoord(posFar, matInverseVPV);

	XMVECTOR mouseDirection = posFar - posNear; //ベクトル
	mouseDirection = XMVector3Normalize(mouseDirection);

	XMVECTOR raticle3D;
	raticle3D = posNear + mouseDirection * shotDistance_;
	aimPos3d_ = raticle3D;

}

void Player::OnCollision() {
	hpCount_--;
	//sound->PlayWave("Engine/Resources/Sound/SE/damage.wav", false, 0.1f);
	//sound->PlayWave("Engine/Resources/Sound/SE/noise.wav", false, 0.1f);
	isDamage_ = true;
}

void Player::DamageEffect() {
	const int damageEffectTimeOver = 0;

	if (--damageEffectTimer_ <= damageEffectTimeOver) {
		isDamage_ = false;
		damageEffectTimer_ = damageEffectTime;
	}
}

void Player::DeadPerformance() {
	const int32_t deadTimeOver = 0;

	deadTimer_--;

	if (deadTimer_ <= deadTimeOver) {
		isDead_ = true;
	}

	playerRot_.z += 2.0f;
	player_->SetRotation(playerRot_);
}

void Player::ClearPerformance() {
	clearTimer_--;
	playerWPos_.x = Easing::easeInOut(clearTimer_, clearTime_, playerWPos_.x, clearPos_.x);
	playerWPos_.y = Easing::easeOutBack(clearTimer_, clearTime_, playerWPos_.y, clearPos_.y, 1);
	playerWPos_.z = Easing::easeInOut(clearTimer_, clearTime_, playerWPos_.z, clearPos_.z);
	player_->SetCameraParent(nullptr);
	player_->SetPosition(playerWPos_);
	player_->SetRotation(playerRot_);
	camera_->SetTarget(playerWPos_);
}

void Player::StartPerformance()
{
	startTimer_++;
	if (startTimer_ >= startTime) {
		startTimer_ = startTime;
		isStart_ = true;
	}
	if (!isStart_) {
		playerLPos_.y = Easing::easeIn((float)startTimer_, (float)startTime, 0, playerLPos_.y);
		playerRot_.x = Easing::easeIn((float)startTimer_, (float)startTime * 2, 0, playerRot_.x);
	}
}

void Player::PlayerPosCorrection()
{
	const float playerWidth = 4.0f;
	const float playerHeight = 8.0f;
	const float moveRangeLeft = 200.0f;
	const float moveRangeRight = 1100.0f;
	const float moveRangeTop = 100.0f;
	const float moveRangeBottom = 600.0f;

	//プレイヤーの画面上の位置を求める
	XMVECTOR playerPos = { player_->GetMatWorld().r[3].m128_f32[0], player_->GetMatWorld().r[3].m128_f32[1], player_->GetMatWorld().r[3].m128_f32[2] };
	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
	playerPos = XMVector3TransformCoord(playerPos, matVPV);
	XMFLOAT2 player2dPos = { playerPos.m128_f32[0], playerPos.m128_f32[1] };

	if (isStart_) {
		if (player2dPos.x < moveRangeLeft + playerWidth) playerLPos_ = prePos;
		if (player2dPos.x > moveRangeRight - playerWidth) playerLPos_ = prePos;
		if (player2dPos.y < moveRangeTop + playerHeight) playerLPos_ = prePos;
		if (player2dPos.y > moveRangeBottom - playerHeight) playerLPos_ = prePos;
	}

	prePos = playerLPos_;
}
