#include "FirstBoss.h"

void FirstBoss::Initialize(const std::string modelKey, const Vector3& pos_) {
	boss_ = Object3d::Create(ModelManager::GetIns()->GetModel(modelKey));
	this->pos_ = pos_;
	scale_ = { 10, 10, 10 };
	rot_ = { 0, 90, 0 };
	hp_ = 100;
	attackPower_ = 1;
	actionCoolTimer_ = 0;
	actionPattern_ = 1;
	rotationTimer_ = 0;
	actionPreTimer_ = 0;
	deadTimer_ = 0;
	isMovie_ = true;

	boss_->SetPosition(pos_);
	boss_->SetRotation(rot_);
	boss_->SetScale(scale_);

	leftHand_ = Object3d::Create(ModelManager::GetIns()->GetModel("boss1_Hand"));
	rightHand_ = Object3d::Create(ModelManager::GetIns()->GetModel("boss1_Hand"));
	leftHandShadow_ = Object3d::Create(ModelManager::GetIns()->GetModel("shadow"));
	rightHandShadow_ = Object3d::Create(ModelManager::GetIns()->GetModel("shadow"));
	leftHandShadow_->SetScale({ 30.0f, 30.0f, 30.0f });
	rightHandShadow_->SetScale({ 30.0f, 30.0f, 30.0f });

	leftHandPos_ = { 15.0f, 0.0f, 0.0f };
	leftHandScale_ = { 1.0f, 1.0f, 1.0f };
	leftHandRot_ = { -90.0f, 0.0f, 0.0f };
	leftHandHP_ = 50;
	leftHandDamageTimer_ = 0;
	leftHandDeadTimer_ = 0;
	leftHand_->SetParent(boss_);
	leftHand_->SetPosition(leftHandPos_);
	leftHand_->SetScale(leftHandScale_);
	leftHand_->SetRotation(leftHandRot_);

	rightHandPos_ = { -15.0f, 0.0f, 0.0f };
	rightHandScale_ = { 1.0f, 1.0f, 1.0f };
	rightHandRot_ = { -90.0f, 0.0f, 0.0f };
	rightHandHP_ = 50;
	rightHandDamageTimer_ = 0;
	rightHandDeadTimer_ = 0;
	rightHand_->SetParent(boss_);
	rightHand_->SetPosition(rightHandPos_);
	rightHand_->SetRotation(rightHandRot_);
	rightHand_->SetScale(rightHandScale_);

	rollingShotTimer_ = 0;
	leftHandAngle_ = 0.0f;
	rightHandAngle_ = 180.0f;

	hpBar_ = Sprite::Create(ImageManager::HPBar, { 0.0f, 0.0f }, { 0.0f, 0.7f, 0.0f, 1.0f });
	hpBar_->SetAnchorPoint({ 0.5f, 0.5f });
	hpBar_->SetLeftSizeCorrection(false);
	hpBar_->SetColor({ 0.0f, 0.7f, 0.0f });
	hpRedBar_ = Sprite::Create(ImageManager::HPBar, { 0.0f, 0.0f }, { 0.7f, 0.0f, 0.0f, 1.0f });
	hpRedBar_->SetAnchorPoint({ 0.5f, 0.5f });
	hpRedBar_->SetLeftSizeCorrection(false);
	hpRedBar_->SetColor({ 0.7f, 0.0f, 0.0f });

	leftHpBar_ = Sprite::Create(ImageManager::HPBar, { 0.0f, 0.0f }, { 0.0f, 0.7f, 0.0f, 1.0f });
	leftHpBar_->SetAnchorPoint({ 0.5f, 0.5f });
	leftHpBar_->SetLeftSizeCorrection(false);
	leftHpBar_->SetColor({ 0.0f, 0.7f, 0.0f });
	leftHpRedBar_ = Sprite::Create(ImageManager::HPBar, { 0.0f, 0.0f }, { 0.7f, 0.0f, 0.0f, 1.0f });
	leftHpRedBar_->SetAnchorPoint({ 0.5f, 0.5f });
	leftHpRedBar_->SetLeftSizeCorrection(false);
	leftHpRedBar_->SetColor({ 0.7f, 0.0f, 0.0f });

	rightHpBar_ = Sprite::Create(ImageManager::HPBar, { 0.0f, 0.0f }, { 0.0f, 0.7f, 0.0f, 1.0f });
	rightHpBar_->SetAnchorPoint({ 0.5f, 0.5f });
	rightHpBar_->SetLeftSizeCorrection(false);
	rightHpBar_->SetColor({ 0.0f, 0.7f, 0.0f });
	rightHpRedBar_ = Sprite::Create(ImageManager::HPBar, { 0.0f, 0.0f }, { 0.7f, 0.0f, 0.0f, 1.0f });
	rightHpRedBar_->SetAnchorPoint({ 0.5f, 0.5f });
	rightHpRedBar_->SetLeftSizeCorrection(false);
	rightHpRedBar_->SetColor({ 0.7f, 0.0f, 0.0f });
}

void FirstBoss::Update(const Vector3& playerPos, const int32_t delayTime)
{
	leftHandShadowPos_ = leftHand_->GetMatWorld().r[3];
	rightHandShadowPos_ = rightHand_->GetMatWorld().r[3];
	leftHandShadowPos_.y = -50.0f;
	rightHandShadowPos_.y = -50.0f;

	if (isMovie_) {
		MovieAction();
	}
	else {
		playerPos_ = playerPos;
		if (leftHandHP_ <= deadHP) {
			LeftHandDeadReaction();
		}
		if (rightHandHP_ <= deadHP) {
			RightHandDeadReaction();
		}

		if (hp_ > deadHP) {
			Action();
			DamageReaction();
			LeftHandDamageReaction();
			RightHandDamageReaction();
		}
		else {
			leftHandHP_ = deadHP;
			rightHandHP_ = deadHP;
			DeadReaction();
		}
	}

	HPBarUpdate();
	boss_->Update();
	boss_->SetPosition(pos_);
	boss_->SetRotation(rot_);
	leftHand_->SetPosition(leftHandPos_);
	rightHand_->SetPosition(rightHandPos_);
	leftHandShadow_->SetPosition(leftHandShadowPos_);
	rightHandShadow_->SetPosition(rightHandShadowPos_);
	leftHand_->SetRotation(leftHandRot_);
	rightHand_->SetRotation(rightHandRot_);
	leftHand_->Update();
	rightHand_->Update();
	leftHandShadow_->Update();
	rightHandShadow_->Update();
}

void FirstBoss::Draw()
{
	boss_->Draw();
	if (leftHandHP_ > deadHP) {
		leftHandShadow_->Draw();
	}
	if (rightHandHP_ > deadHP) {
		rightHandShadow_->Draw();
	}
	if (!isLeftHandDead_) {
		leftHand_->Draw();
	}
	if (!isRightHandDead_) {
		rightHand_->Draw();
	}
}

void FirstBoss::SpriteDraw()
{
	if (!isDead_) {
		hpRedBar_->Draw();
		hpBar_->Draw();
	}
	if (!isLeftHandDead_) {
		leftHpRedBar_->Draw();
		leftHpBar_->Draw();
	}
	if (!isRightHandDead_) {
		rightHpRedBar_->Draw();
		rightHpBar_->Draw();
	}
}

void FirstBoss::Finalize()
{
	safe_delete(boss_);
	safe_delete(leftHand_);
	safe_delete(rightHand_);
	safe_delete(leftHandShadow_);
	safe_delete(rightHandShadow_);
	safe_delete(hpBar_);
	safe_delete(hpRedBar_);
	safe_delete(leftHpBar_);
	safe_delete(leftHpRedBar_);
	safe_delete(rightHpBar_);
	safe_delete(rightHpRedBar_);
}

void FirstBoss::Action()
{
	actionCoolTimer_++;
	if (leftHandHP_ > deadHP) {
		leftHandPos_ = { 15.0f, 0.0f, 0.0f };
		leftHandScale_ = { 1.0f, 1.0f, 1.0f };
		leftHandRot_ = { -90.0f, 0.0f, 0.0f };
	}
	if (rightHandHP_ > deadHP) {
		rightHandPos_ = { -15.0f, 0.0f, 0.0f };
		rightHandScale_ = { 1.0f, 1.0f, 1.0f };
		rightHandRot_ = { -90.0f, 0.0f, 0.0f };
	}
	if (actionCoolTimer_ >= actionCoolTime) {
		switch (actionPattern_)
		{
		case 1:
			RollingShot(20);
			break;
		case 2:
			Guard(40);
			break;
		default:
			break;
		}
	}
}

void FirstBoss::MovieAction()
{
	//初期座標
	const Vector3 initLeftHandPos = { 15.0f, 0.0f, 0.0f };
	const Vector3 initRightHandPos = { -15.0f, 0.0f, 0.0f };
	const Vector3 initHandRot = { -90.0f, 0.0f, 0.0f };
	//移動する各ポイント
	const Vector3 movieLeftHandPointPos_1 = { 7.0f, 0.0f, 15.0f };
	const Vector3 movieRightHandPointPos_1 = { -7.0f, 0.0f, 15.0f };
	const Vector3 movieLeftHandPointPos_2 = { 18.0f, 0.0f, -5.0f };
	const Vector3 movieRightHandPointPos_2 = { -18.0f, 0.0f, -5.0f };
	//各ポイント角度
	const Vector3 movieLeftHandPointRot_1 = { -135.0f, -90.0f, 0.0f };
	const Vector3 movieRightHandPointRot_1 = { -135.0f, 90.0f, 0.0f };
	const Vector3 movieLeftHandPointRot_2 = { 45.0f, -90.0f, 0.0f };
	const Vector3 movieRightHandPointRot_2 = { 45.0f, 90.0f, 0.0f };

	int32_t movieTime = 0;

	movieTimer_++;
	if (!isMoviePoint_1_) {
		movieTime = 120;
	}
	else if (!isMoviePoint_2_) {
		movieTime = 40;
	}
	else if (!isMoviePoint_3_) {
		movieTime = 120;
	}

	if (movieTimer_ >= movieTime / 2 && isMoviePoint_2_) {
		isCameraMoveTiming_ = true;
	}
	if (movieTimer_ >= movieTime) {
		if (!isMoviePoint_1_) {
			movieTimer_ = 0;
			isMoviePoint_1_ = true;
		}
		else if (!isMoviePoint_2_) {
			movieTimer_ = 0;
			isMoviePoint_2_ = true;
		}
		else if (!isMoviePoint_3_) {
			movieTimer_ = 0;
			isMoviePoint_3_ = true;
			isMovie_ = false;
		}
	}

	float timeRate = min((float)movieTimer_ / (float)movieTime, 1.0f);
	if (!isMoviePoint_1_) {
		leftHandPos_ = easeIn(initLeftHandPos, movieLeftHandPointPos_1, timeRate);
		rightHandPos_ = easeIn(initRightHandPos, movieRightHandPointPos_1, timeRate);
		leftHandRot_ = easeIn(initHandRot, movieLeftHandPointRot_1, timeRate);
		rightHandRot_ = easeIn(initHandRot, movieRightHandPointRot_1, timeRate);
	}
	else if (!isMoviePoint_2_) {
		leftHandPos_ = easeIn(movieLeftHandPointPos_1, movieLeftHandPointPos_2, timeRate);
		rightHandPos_ = easeIn(movieRightHandPointPos_1, movieRightHandPointPos_2, timeRate);
		leftHandRot_ = easeIn(movieLeftHandPointRot_1, movieLeftHandPointRot_2, timeRate);
		rightHandRot_ = easeIn(movieRightHandPointRot_1, movieRightHandPointRot_2, timeRate);
	}
	else if (!isMoviePoint_3_) {
		leftHandPos_ = easeIn(movieLeftHandPointPos_2, initLeftHandPos, timeRate);
		rightHandPos_ = easeIn(movieRightHandPointPos_2, initRightHandPos, timeRate);
		leftHandRot_ = easeIn(movieLeftHandPointRot_2, initHandRot, timeRate);
		rightHandRot_ = easeIn(movieRightHandPointRot_2, initHandRot, timeRate);
	}
}

void FirstBoss::LeftHandOnCollision()
{
	leftHandHP_--;
	isLeftHandDamage_ = true;
}

void FirstBoss::RightHandOnCollision()
{
	rightHandHP_--;
	isRightHandDamage_ = true;
}

void FirstBoss::LeftHandDamageReaction()
{
	if (isLeftHandDamage_) {
		leftHandDamageTimer_++;
		leftHand_->SetColor(damageColor);
	}

	if (leftHandDamageTimer_ >= damageTime) {
		isLeftHandDamage_ = false;
		leftHandDamageTimer_ = 0;
		leftHand_->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	}
}

void FirstBoss::RightHandDamageReaction()
{
	if (isRightHandDamage_) {
		rightHandDamageTimer_++;
		rightHand_->SetColor(damageColor);
	}

	if (rightHandDamageTimer_ >= damageTime) {
		isRightHandDamage_ = false;
		rightHandDamageTimer_ = 0;
		rightHand_->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	}
}

void FirstBoss::Guard(const int32_t actionPreTime)
{
	actionPreTimer_++;
	if (actionPreTimer_ >= actionPreTime) {
		isActionPos_ = true;
	}

	if (isActionPos_) {
		guardTimer_++;
		if (guardTimer_ >= guardTime) {
			isActionPos_ = false;
			isActionPost_ = true;
		}

		const float direction = 180.0f;

		Vector3 distance = pos_ - playerPos_;

		float angle = (atan2(distance.x, distance.z)) * 180.0f / 3.14f + direction;

		rot_.y = angle;

		if (leftHandHP_ > deadHP) {
			leftHandPos_.x = 2.0f;
			leftHandPos_.z = 15.0f;
			leftHandRot_.x = -180.0f;
		}

		if (rightHandHP_ > deadHP) {
			rightHandPos_.x = -2.0f;
			rightHandPos_.z = 15.0f;
			rightHandRot_.x = -180.0f;
		}
	}
	else {
		const float direction = 180.0f;

		Vector3 distance = pos_ - playerPos_;

		float angle = (atan2(distance.x, distance.z)) * 180.0f / 3.14f + direction;

		rot_.y = Easing::easeIn((float)actionPreTimer_, (float)actionPreTime, angle, rot_.y);

		if (leftHandHP_ > deadHP) {
			leftHandPos_.x = Easing::easeIn((float)actionPreTimer_, (float)actionPreTime, 2.0f, leftHandPos_.x);
			leftHandPos_.z = Easing::easeIn((float)actionPreTimer_, (float)actionPreTime, 15.0f, leftHandPos_.z);
			leftHandRot_.x = Easing::easeIn((float)actionPreTimer_, (float)actionPreTime, -180.0f, leftHandRot_.x);
		}
		
		if (rightHandHP_ > deadHP) {
			rightHandPos_.x = Easing::easeIn((float)actionPreTimer_, (float)actionPreTime, 2.0f, rightHandPos_.x);
			rightHandPos_.z = Easing::easeIn((float)actionPreTimer_, (float)actionPreTime, 15.0f, rightHandPos_.z);
			rightHandRot_.x = Easing::easeIn((float)actionPreTimer_, (float)actionPreTime, -180.0f, rightHandRot_.x);
		}
	}

	if (isActionPost_) {
		const Vector3 initLeftHandPos = { 15.0f, 0.0f, 0.0f };
		const Vector3 initRightHandPos = { -15.0f, 0.0f, 0.0f };
		const Vector3 initHandRot = { -90.0f, 0.0f, 0.0f };

		if (leftHandHP_ > deadHP) {
			leftHandPos_.x = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initLeftHandPos.x, leftHandPos_.x);
			leftHandPos_.y = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initLeftHandPos.y, leftHandPos_.y);
			leftHandPos_.z = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initLeftHandPos.z, leftHandPos_.z);

			leftHandRot_.x = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initHandRot.x, leftHandRot_.x);
			leftHandRot_.y = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initHandRot.y, leftHandRot_.y);
			leftHandRot_.z = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initHandRot.z, leftHandRot_.z);
		}

		if (rightHandHP_ > deadHP) {
			rightHandPos_.x = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initRightHandPos.x, rightHandPos_.x);
			rightHandPos_.y = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initRightHandPos.y, rightHandPos_.y);
			rightHandPos_.z = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initRightHandPos.z, rightHandPos_.z);

			rightHandRot_.x = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initHandRot.x, rightHandRot_.x);
			rightHandRot_.y = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initHandRot.y, rightHandRot_.y);
			rightHandRot_.z = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initHandRot.z, rightHandRot_.z);
		}

		actionPostTimer_++;
		if (actionPostTimer_ >= actionPreTime) {
			actionCoolTimer_ = 0;
			actionPattern_ = 1;
			guardTimer_ = 0;
			actionPreTimer_ = 0;
			actionPostTimer_ = 0;
			isActionPost_ = false;
		}
	}
}

void FirstBoss::RollingShot(const int32_t actionPreTime) {
	const float bulletSpeed = 0.001f;

	actionPreTimer_++;
	if (actionPreTimer_ >= actionPreTime) {
		isActionPos_ = true;
	}

	if (isActionPos_) {
		rollingShotTimer_++;
		if (rollingShotTimer_ >= rollingShotTime) {
			isActionPos_ = false;
			isActionPost_ = true;
		}

		if (leftHandHP_ > deadHP) {
			leftHandAngle_++;
			if (leftHandAngle_ >= 360.0f) {
				leftHandAngle_ = 0;
			}

			leftHandPos_ = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, leftHandPos_, leftHandAngle_, 15, MotionMath::Y);
			leftHandPos_.y = -3.5f;

			leftHandRot_.y = -leftHandAngle_;

			XMVECTOR velocity = { 0, -1, 0 };
			velocity = XMVector3TransformNormal(velocity, leftHand_->GetMatWorld());
			std::unique_ptr<EnemyBullet> newLeftBullet = std::make_unique<EnemyBullet>();
			newLeftBullet->Initialize(leftHand_->GetMatWorld().r[3], velocity);
			bossScene_->AddEnemyBullet(std::move(newLeftBullet));
		}

		if (rightHandHP_ > deadHP) {
			rightHandAngle_++;
			if (rightHandAngle_ >= 360.0f) {
				rightHandAngle_ = 0;
			}

			rightHandPos_.y = -3.5f;
			rightHandPos_ = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, rightHandPos_, rightHandAngle_, 15, MotionMath::Y);

			rightHandRot_.y = -rightHandAngle_;

			XMVECTOR velocity = { 0, -1, 0 };
			velocity = XMVector3TransformNormal(velocity, rightHand_->GetMatWorld());
			std::unique_ptr<EnemyBullet> newRightBullet = std::make_unique<EnemyBullet>();
			newRightBullet->Initialize(rightHand_->GetMatWorld().r[3], velocity);
			bossScene_->AddEnemyBullet(std::move(newRightBullet));
		}
	}
	else {
		Vector3 leftHandActionPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, leftHandActionPos, leftHandAngle_, 15, MotionMath::Y);
		leftHandActionPos.y = -3.5f;
		Vector3 rightHandActionPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, rightHandActionPos, rightHandAngle_, 15, MotionMath::Y);
		rightHandActionPos.y = -3.5f;

		if (leftHandHP_ > deadHP) {
			leftHandPos_.x = Easing::easeIn((float)actionPreTimer_, (float)actionPreTime, leftHandActionPos.x, leftHandPos_.x);
			leftHandPos_.y = Easing::easeIn((float)actionPreTimer_, (float)actionPreTime, leftHandActionPos.y, leftHandPos_.y);
			leftHandPos_.z = Easing::easeIn((float)actionPreTimer_, (float)actionPreTime, leftHandActionPos.z, leftHandPos_.z);
		}
		
		if (rightHandHP_ > deadHP) {
			rightHandPos_.x = Easing::easeIn((float)actionPreTimer_, (float)actionPreTime, rightHandActionPos.x, rightHandPos_.x);
			rightHandPos_.y = Easing::easeIn((float)actionPreTimer_, (float)actionPreTime, rightHandActionPos.y, rightHandPos_.y);
			rightHandPos_.z = Easing::easeIn((float)actionPreTimer_, (float)actionPreTime, rightHandActionPos.z, rightHandPos_.z);
		}
	}

	if (isActionPost_) {
		const Vector3 initLeftHandPos = { 15.0f, 0.0f, 0.0f };
		const Vector3 initRightHandPos = { -15.0f, 0.0f, 0.0f };
		const Vector3 initHandRot = { -90.0f, 0.0f, 0.0f };
		
		if (leftHandHP_ > deadHP) {
			leftHandPos_.x = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initLeftHandPos.x, leftHandPos_.x);
			leftHandPos_.y = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initLeftHandPos.y, leftHandPos_.y);
			leftHandPos_.z = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initLeftHandPos.z, leftHandPos_.z);

			leftHandRot_.x = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initHandRot.x, leftHandRot_.x);
			leftHandRot_.y = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initHandRot.y, leftHandRot_.y);
			leftHandRot_.z = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initHandRot.z, leftHandRot_.z);
		}
		
		if (rightHandHP_ > deadHP) {
			rightHandPos_.x = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initRightHandPos.x, rightHandPos_.x);
			rightHandPos_.y = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initRightHandPos.y, rightHandPos_.y);
			rightHandPos_.z = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initRightHandPos.z, rightHandPos_.z);

			rightHandRot_.x = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initHandRot.x, rightHandRot_.x);
			rightHandRot_.y = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initHandRot.y, rightHandRot_.y);
			rightHandRot_.z = Easing::easeIn((float)actionPostTimer_, (float)actionPreTime, initHandRot.z, rightHandRot_.z);
		}

		actionPostTimer_++;
		if (actionPostTimer_ >= actionPreTime) {
			actionCoolTimer_ = 0;
			actionPattern_ = 2;
			rollingShotTimer_ = 0;
			actionPreTimer_ = 0;
			actionPostTimer_ = 0;
			isActionPost_ = false;
		}
		
	}
}

void FirstBoss::Stomp()
{
	stompTimer_++;
	if (stompTimer_ <= 50) {
		leftHandAngle_ = player_->GetAngle();
		leftHandPos_ = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, leftHandPos_, leftHandAngle_, 15, MotionMath::Y);
		leftHandPos_.y = 10.0f;
		leftHandRot_.x = 0.0f;
	}
	else {
		leftHandPos_.y -= 3.0f;
	}

	if (stompTimer_ >= stompTime) {
		actionCoolTimer_ = 0;
		stompTimer_ = 0;
		actionPattern_ = 1;
	}

	if (rightHandHP_ > deadHP) {
		rightHandAngle_++;
		if (rightHandAngle_ >= 360.0f) {
			rightHandAngle_ = 0;
		}

		rightHandPos_.y = -3.5f;
		rightHandPos_ = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, rightHandPos_, rightHandAngle_, 15, MotionMath::Y);

		rightHandRot_.y = -rightHandAngle_;

		XMVECTOR velocity = { 0, -1, 0 };
		velocity = XMVector3TransformNormal(velocity, rightHand_->GetMatWorld());
		std::unique_ptr<EnemyBullet> newRightBullet = std::make_unique<EnemyBullet>();
		newRightBullet->Initialize(rightHand_->GetMatWorld().r[3], velocity);
		bossScene_->AddEnemyBullet(std::move(newRightBullet));
	}
}

void FirstBoss::Lariat()
{
	punchTimer_++;
	if (punchTimer_ >= punchTime) {
		actionCoolTimer_ = 0;
		actionPattern_ = 1;
		punchTimer_ = 0;
	}

	if (leftHandHP_ > deadHP) {
		leftHandAngle_ += 2.0f;
		if (leftHandAngle_ >= 360.0f) {
			leftHandAngle_ = 0;
		}

		leftHandPos_ = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, leftHandPos_, leftHandAngle_, 18, MotionMath::Y);
		leftHandPos_.y = -3.5f;

		leftHandRot_.y = -leftHandAngle_ + 60;

		leftHandScale_ = { 0.8f, 0.8f, 0.8f };
	}

	if (rightHandHP_ > deadHP) {
		rightHandAngle_ += 2.0f;
		if (rightHandAngle_ >= 360.0f) {
			rightHandAngle_ = 0;
		}

		rightHandPos_.y = -3.5f;
		rightHandPos_ = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, rightHandPos_, rightHandAngle_, 18, MotionMath::Y);

		rightHandRot_.y = -rightHandAngle_ + 60;

		rightHandScale_ = { 0.8f, 0.8f, 0.8f };
	}
}

void FirstBoss::DeadReaction()
{

	deadTimer_++;
	pos_.y -= 1.0f;
	rightHandPos_.y -= 0.1f;
	boss_->SetColor(damageColor);
	if (deadTimer_ >= deadTime) {
		isDead_ = true;
	}
}

void FirstBoss::LeftHandDeadReaction()
{
	if (leftHandDeadTimer_ >= leftHandDeadTime) {
		isLeftHandDead_ = true;
	}
	else {
		leftHandPos_.y -= 0.1f;
		leftHandDeadTimer_++;
		leftHand_->SetColor(damageColor);
	}
}

void FirstBoss::RightHandDeadReaction()
{
	if (rightHandDeadTimer_ >= rightHandDeadTime) {
		isRightHandDead_ = true;
	}
	else {
		rightHandPos_.y -= 0.1f;
		rightHandDeadTimer_++;
		rightHand_->SetColor(damageColor);
	}
}

void FirstBoss::HPBarUpdate()
{
	//最大HP(後々外部ファイルで管理するので仮)
	const int32_t handMaxHp = 50;
	const int32_t bossMaxHp = 100;
	//HPバーサイズセット用変数
	XMFLOAT2 bossHpBarSize = { 100.0f, 20.0f };
	XMFLOAT2 leftHandHpBarSize = { 50.0f, 20.0f };
	XMFLOAT2 rightHandHpBarSize = { 50.0f, 20.0f };
	XMFLOAT2 hpBarPos = { 0.0f, 0.0f };

	//HPバーサイズセット
	bossHpBarSize.x *= 10.0f;
	leftHandHpBarSize.x *= 5.0f;
	rightHandHpBarSize.x *= 5.0f;

	hpRedBar_->SetSize(bossHpBarSize);
	leftHpRedBar_->SetSize(leftHandHpBarSize);
	rightHpRedBar_->SetSize(rightHandHpBarSize);

	bossHpBarSize.x = (float)bossMaxHp * (float)(hp_ / bossMaxHp) * 10.0f;
	hpBar_->SetSize(bossHpBarSize);
	leftHandHpBarSize.x = (float)handMaxHp * ((float)leftHandHP_ / (float)handMaxHp) * 5.0f;
	leftHpBar_->SetSize(leftHandHpBarSize);
	rightHandHpBarSize.x = (float)handMaxHp * ((float)rightHandHP_ / (float)handMaxHp) * 5.0f;
	rightHpBar_->SetSize(rightHandHpBarSize);

	//HPバー座標計算&セット
	XMVECTOR bossPos = { boss_->GetMatWorld().r[3].m128_f32[0], boss_->GetMatWorld().r[3].m128_f32[1], boss_->GetMatWorld().r[3].m128_f32[2]};
	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
	bossPos = XMVector3TransformCoord(bossPos, matVPV);
	hpBarPos = { bossPos.m128_f32[0] - 250.0f, bossPos.m128_f32[1] - 300.0f };
	hpBar_->SetPosition(hpBarPos);
	hpRedBar_->SetPosition(hpBarPos);

	XMVECTOR handPos = { leftHand_->GetMatWorld().r[3].m128_f32[0], leftHand_->GetMatWorld().r[3].m128_f32[1], leftHand_->GetMatWorld().r[3].m128_f32[2] };
	handPos = XMVector3TransformCoord(handPos, matVPV);
	hpBarPos = { handPos.m128_f32[0] - 100.0f, handPos.m128_f32[1] - 100.0f };
	leftHpBar_->SetPosition(hpBarPos);
	leftHpRedBar_->SetPosition(hpBarPos);

	handPos = { rightHand_->GetMatWorld().r[3].m128_f32[0], rightHand_->GetMatWorld().r[3].m128_f32[1], rightHand_->GetMatWorld().r[3].m128_f32[2] };
	handPos = XMVector3TransformCoord(handPos, matVPV);
	hpBarPos = { handPos.m128_f32[0] - 100.0f, handPos.m128_f32[1] - 100.0f };
	rightHpBar_->SetPosition(hpBarPos);
	rightHpRedBar_->SetPosition(hpBarPos);
}
