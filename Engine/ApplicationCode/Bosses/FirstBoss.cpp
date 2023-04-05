#include "FirstBoss.h"

void FirstBoss::Initialize(const std::string modelKey, const Vector3& pos) {
	boss = Object3d::Create(ModelManager::GetIns()->GetModel(modelKey));
	this->pos = pos;
	scale = { 10, 10, 10 };
	rot = { 0, 90, 0 };
	hp = 100;
	attackPower = 1;
	actionCoolTimer = 0;
	actionPattern = 1;
	rotationTimer = 0;
	actionPreTimer = 0;
	deadTimer = 0;
	isMovie = true;

	boss->SetPosition(this->pos);
	boss->SetRotation(rot);
	boss->SetScale(scale);

	leftHand = Object3d::Create(ModelManager::GetIns()->GetModel("boss1_Hand"));
	rightHand = Object3d::Create(ModelManager::GetIns()->GetModel("boss1_Hand"));
	leftHandShadow = Object3d::Create(ModelManager::GetIns()->GetModel("shadow"));
	rightHandShadow = Object3d::Create(ModelManager::GetIns()->GetModel("shadow"));
	leftHandShadow->SetScale({ 30.0f, 30.0f, 30.0f });
	rightHandShadow->SetScale({ 30.0f, 30.0f, 30.0f });

	leftHandPos = { 15.0f, 0.0f, 0.0f };
	leftHandScale = { 1.0f, 1.0f, 1.0f };
	leftHandRot = { -90.0f, 0.0f, 0.0f };
	leftHandHP = 50;
	leftHandDamageTimer = 0;
	leftHandDeadTimer = 0;
	leftHand->SetParent(boss);
	leftHand->SetPosition(leftHandPos);
	leftHand->SetScale(leftHandScale);
	leftHand->SetRotation(leftHandRot);

	rightHandPos = { -15.0f, 0.0f, 0.0f };
	rightHandScale = { 1.0f, 1.0f, 1.0f };
	rightHandRot = { -90.0f, 0.0f, 0.0f };
	rightHandHP = 50;
	rightHandDamageTimer = 0;
	rightHandDeadTimer = 0;
	rightHand->SetParent(boss);
	rightHand->SetPosition(rightHandPos);
	rightHand->SetRotation(rightHandRot);
	rightHand->SetScale(rightHandScale);

	rollingShotTimer = 0;
	leftHandAngle = 0.0f;
	rightHandAngle = 180.0f;

	hpBar = Sprite::Create(ImageManager::HPBar, { 0.0f, 0.0f }, { 0.0f, 0.7f, 0.0f, 1.0f });
	hpBar->SetAnchorPoint({ 0.5f, 0.5f });
	hpBar->SetLeftSizeCorrection(false);
	hpBar->SetColor({ 0.0f, 0.7f, 0.0f });
	hpRedBar = Sprite::Create(ImageManager::HPBar, { 0.0f, 0.0f }, { 0.7f, 0.0f, 0.0f, 1.0f });
	hpRedBar->SetAnchorPoint({ 0.5f, 0.5f });
	hpRedBar->SetLeftSizeCorrection(false);
	hpRedBar->SetColor({ 0.7f, 0.0f, 0.0f });

	leftHpBar = Sprite::Create(ImageManager::HPBar, { 0.0f, 0.0f }, { 0.0f, 0.7f, 0.0f, 1.0f });
	leftHpBar->SetAnchorPoint({ 0.5f, 0.5f });
	leftHpBar->SetLeftSizeCorrection(false);
	leftHpBar->SetColor({ 0.0f, 0.7f, 0.0f });
	leftHpRedBar = Sprite::Create(ImageManager::HPBar, { 0.0f, 0.0f }, { 0.7f, 0.0f, 0.0f, 1.0f });
	leftHpRedBar->SetAnchorPoint({ 0.5f, 0.5f });
	leftHpRedBar->SetLeftSizeCorrection(false);
	leftHpRedBar->SetColor({ 0.7f, 0.0f, 0.0f });

	rightHpBar = Sprite::Create(ImageManager::HPBar, { 0.0f, 0.0f }, { 0.0f, 0.7f, 0.0f, 1.0f });
	rightHpBar->SetAnchorPoint({ 0.5f, 0.5f });
	rightHpBar->SetLeftSizeCorrection(false);
	rightHpBar->SetColor({ 0.0f, 0.7f, 0.0f });
	rightHpRedBar = Sprite::Create(ImageManager::HPBar, { 0.0f, 0.0f }, { 0.7f, 0.0f, 0.0f, 1.0f });
	rightHpRedBar->SetAnchorPoint({ 0.5f, 0.5f });
	rightHpRedBar->SetLeftSizeCorrection(false);
	rightHpRedBar->SetColor({ 0.7f, 0.0f, 0.0f });
}

void FirstBoss::Update(const Vector3& playerPos, const int delayTime)
{
	leftHandShadowPos = leftHand->GetMatWorld().r[3];
	rightHandShadowPos = rightHand->GetMatWorld().r[3];
	leftHandShadowPos.y = -50.0f;
	rightHandShadowPos.y = -50.0f;

	if (isMovie) {
		MovieAction();
	}
	else {
		this->playerPos = playerPos;
		if (leftHandHP <= deadHP) {
			LeftHandDeadReaction();
		}
		if (rightHandHP <= deadHP) {
			RightHandDeadReaction();
		}

		if (hp > deadHP) {
			Action();
			DamageReaction();
			LeftHandDamageReaction();
			RightHandDamageReaction();
		}
		else {
			leftHandHP = deadHP;
			rightHandHP = deadHP;
			DeadReaction();
		}
	}

	HPBarUpdate();
	boss->Update();
	boss->SetPosition(pos);
	boss->SetRotation(rot);
	leftHand->SetPosition(leftHandPos);
	rightHand->SetPosition(rightHandPos);
	leftHandShadow->SetPosition(leftHandShadowPos);
	rightHandShadow->SetPosition(rightHandShadowPos);
	leftHand->SetRotation(leftHandRot);
	rightHand->SetRotation(rightHandRot);
	leftHand->Update();
	rightHand->Update();
	leftHandShadow->Update();
	rightHandShadow->Update();
}

void FirstBoss::Draw()
{
	boss->Draw();
	if (leftHandHP > deadHP) {
		leftHandShadow->Draw();
	}
	if (rightHandHP > deadHP) {
		rightHandShadow->Draw();
	}
	if (!isLeftHandDead) {
		leftHand->Draw();
	}
	if (!isRightHandDead) {
		rightHand->Draw();
	}
}

void FirstBoss::SpriteDraw()
{
	if (!isDead) {
		hpRedBar->Draw();
		hpBar->Draw();
	}
	if (!isLeftHandDead) {
		leftHpRedBar->Draw();
		leftHpBar->Draw();
	}
	if (!isRightHandDead) {
		rightHpRedBar->Draw();
		rightHpBar->Draw();
	}
}

void FirstBoss::Finalize()
{
	safe_delete(boss);
	safe_delete(leftHand);
	safe_delete(rightHand);
	safe_delete(leftHandShadow);
	safe_delete(rightHandShadow);
	safe_delete(hpBar);
	safe_delete(hpRedBar);
	safe_delete(leftHpBar);
	safe_delete(leftHpRedBar);
	safe_delete(rightHpBar);
	safe_delete(rightHpRedBar);
}

void FirstBoss::Action()
{
	actionCoolTimer++;
	if (leftHandHP > deadHP) {
		leftHandPos = { 15.0f, 0.0f, 0.0f };
		leftHandScale = { 1.0f, 1.0f, 1.0f };
		leftHandRot = { -90.0f, 0.0f, 0.0f };
	}
	if (rightHandHP > deadHP) {
		rightHandPos = { -15.0f, 0.0f, 0.0f };
		rightHandScale = { 1.0f, 1.0f, 1.0f };
		rightHandRot = { -90.0f, 0.0f, 0.0f };
	}
	if (actionCoolTimer >= actionCoolTime) {
		switch (actionPattern)
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

	movieTimer++;
	if (!isMoviePoint_1) {
		movieTime = 120;
	}
	else if (!isMoviePoint_2) {
		movieTime = 40;
	}
	else if (!isMoviePoint_3) {
		movieTime = 120;
	}

	if (movieTimer >= movieTime / 2 && isMoviePoint_2) {
		isCameraMoveTiming = true;
	}
	if (movieTimer >= movieTime) {
		if (!isMoviePoint_1) {
			movieTimer = 0;
			isMoviePoint_1 = true;
		}
		else if (!isMoviePoint_2) {
			movieTimer = 0;
			isMoviePoint_2 = true;
		}
		else if (!isMoviePoint_3) {
			movieTimer = 0;
			isMoviePoint_3 = true;
			isMovie = false;
		}
	}

	float timeRate = min((float)movieTimer / (float)movieTime, 1.0f);
	if (!isMoviePoint_1) {
		leftHandPos = easeIn(initLeftHandPos, movieLeftHandPointPos_1, timeRate);
		rightHandPos = easeIn(initRightHandPos, movieRightHandPointPos_1, timeRate);
		leftHandRot = easeIn(initHandRot, movieLeftHandPointRot_1, timeRate);
		rightHandRot = easeIn(initHandRot, movieRightHandPointRot_1, timeRate);
	}
	else if (!isMoviePoint_2) {
		leftHandPos = easeIn(movieLeftHandPointPos_1, movieLeftHandPointPos_2, timeRate);
		rightHandPos = easeIn(movieRightHandPointPos_1, movieRightHandPointPos_2, timeRate);
		leftHandRot = easeIn(movieLeftHandPointRot_1, movieLeftHandPointRot_2, timeRate);
		rightHandRot = easeIn(movieRightHandPointRot_1, movieRightHandPointRot_2, timeRate);
	}
	else if (!isMoviePoint_3) {
		leftHandPos = easeIn(movieLeftHandPointPos_2, initLeftHandPos, timeRate);
		rightHandPos = easeIn(movieRightHandPointPos_2, initRightHandPos, timeRate);
		leftHandRot = easeIn(movieLeftHandPointRot_2, initHandRot, timeRate);
		rightHandRot = easeIn(movieRightHandPointRot_2, initHandRot, timeRate);
	}
}

void FirstBoss::LeftHandOnCollision()
{
	leftHandHP--;
	isLeftHandDamage = true;
}

void FirstBoss::RightHandOnCollision()
{
	rightHandHP--;
	isRightHandDamage = true;
}

void FirstBoss::LeftHandDamageReaction()
{
	if (isLeftHandDamage) {
		leftHandDamageTimer++;
		leftHand->SetColor(damageColor);
	}

	if (leftHandDamageTimer >= damageTime) {
		isLeftHandDamage = false;
		leftHandDamageTimer = 0;
		leftHand->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	}
}

void FirstBoss::RightHandDamageReaction()
{
	if (isRightHandDamage) {
		rightHandDamageTimer++;
		rightHand->SetColor(damageColor);
	}

	if (rightHandDamageTimer >= damageTime) {
		isRightHandDamage = false;
		rightHandDamageTimer = 0;
		rightHand->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	}
}

void FirstBoss::Guard(const int32_t actionPreTime)
{
	actionPreTimer++;
	if (actionPreTimer >= actionPreTime) {
		isActionPos = true;
	}

	if (isActionPos) {
		guardTimer++;
		if (guardTimer >= guardTime) {
			isActionPos = false;
			isActionPost = true;
		}

		const float direction = 180.0f;

		Vector3 distance = pos - playerPos;

		float angle = (atan2(distance.x, distance.z)) * 180.0f / 3.14f + direction;

		rot.y = angle;

		if (leftHandHP > deadHP) {
			leftHandPos.x = 2.0f;
			leftHandPos.z = 15.0f;
			leftHandRot.x = -180.0f;
		}

		if (rightHandHP > deadHP) {
			rightHandPos.x = -2.0f;
			rightHandPos.z = 15.0f;
			rightHandRot.x = -180.0f;
		}
	}
	else {
		const float direction = 180.0f;

		Vector3 distance = pos - playerPos;

		float angle = (atan2(distance.x, distance.z)) * 180.0f / 3.14f + direction;

		rot.y = Easing::easeIn((float)actionPreTimer, (float)actionPreTime, angle, rot.y);

		if (leftHandHP > deadHP) {
			leftHandPos.x = Easing::easeIn((float)actionPreTimer, (float)actionPreTime, 2.0f, leftHandPos.x);
			leftHandPos.z = Easing::easeIn((float)actionPreTimer, (float)actionPreTime, 15.0f, leftHandPos.z);
			leftHandRot.x = Easing::easeIn((float)actionPreTimer, (float)actionPreTime, -180.0f, leftHandRot.x);
		}
		
		if (rightHandHP > deadHP) {
			rightHandPos.x = Easing::easeIn((float)actionPreTimer, (float)actionPreTime, 2.0f, rightHandPos.x);
			rightHandPos.z = Easing::easeIn((float)actionPreTimer, (float)actionPreTime, 15.0f, rightHandPos.z);
			rightHandRot.x = Easing::easeIn((float)actionPreTimer, (float)actionPreTime, -180.0f, rightHandRot.x);
		}
	}

	if (isActionPost) {
		const Vector3 initLeftHandPos = { 15.0f, 0.0f, 0.0f };
		const Vector3 initRightHandPos = { -15.0f, 0.0f, 0.0f };
		const Vector3 initHandRot = { -90.0f, 0.0f, 0.0f };

		if (leftHandHP > deadHP) {
			leftHandPos.x = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initLeftHandPos.x, leftHandPos.x);
			leftHandPos.y = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initLeftHandPos.y, leftHandPos.y);
			leftHandPos.z = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initLeftHandPos.z, leftHandPos.z);

			leftHandRot.x = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initHandRot.x, leftHandRot.x);
			leftHandRot.y = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initHandRot.y, leftHandRot.y);
			leftHandRot.z = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initHandRot.z, leftHandRot.z);
		}

		if (rightHandHP > deadHP) {
			rightHandPos.x = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initRightHandPos.x, rightHandPos.x);
			rightHandPos.y = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initRightHandPos.y, rightHandPos.y);
			rightHandPos.z = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initRightHandPos.z, rightHandPos.z);

			rightHandRot.x = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initHandRot.x, rightHandRot.x);
			rightHandRot.y = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initHandRot.y, rightHandRot.y);
			rightHandRot.z = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initHandRot.z, rightHandRot.z);
		}

		actionPostTimer++;
		if (actionPostTimer >= actionPreTime) {
			actionCoolTimer = 0;
			actionPattern = 1;
			guardTimer = 0;
			actionPreTimer = 0;
			actionPostTimer = 0;
			isActionPost = false;
		}
	}
}

void FirstBoss::RollingShot(const int32_t actionPreTime) {
	const float bulletSpeed = 0.001f;

	actionPreTimer++;
	if (actionPreTimer >= actionPreTime) {
		isActionPos = true;
	}

	if (isActionPos) {
		rollingShotTimer++;
		if (rollingShotTimer >= rollingShotTime) {
			isActionPos = false;
			isActionPost = true;
		}

		if (leftHandHP > deadHP) {
			leftHandAngle++;
			if (leftHandAngle >= 360.0f) {
				leftHandAngle = 0;
			}

			leftHandPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, leftHandPos, leftHandAngle, 15, MotionMath::Y);
			leftHandPos.y = -3.5f;

			leftHandRot.y = -leftHandAngle;

			XMVECTOR velocity = { 0, -1, 0 };
			velocity = XMVector3TransformNormal(velocity, leftHand->GetMatWorld());
			std::unique_ptr<EnemyBullet> newLeftBullet = std::make_unique<EnemyBullet>();
			newLeftBullet->Initialize(leftHand->GetMatWorld().r[3], velocity);
			bossScene->AddEnemyBullet(std::move(newLeftBullet));
		}

		if (rightHandHP > deadHP) {
			rightHandAngle++;
			if (rightHandAngle >= 360.0f) {
				rightHandAngle = 0;
			}

			rightHandPos.y = -3.5f;
			rightHandPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, rightHandPos, rightHandAngle, 15, MotionMath::Y);

			rightHandRot.y = -rightHandAngle;

			XMVECTOR velocity = { 0, -1, 0 };
			velocity = XMVector3TransformNormal(velocity, rightHand->GetMatWorld());
			std::unique_ptr<EnemyBullet> newRightBullet = std::make_unique<EnemyBullet>();
			newRightBullet->Initialize(rightHand->GetMatWorld().r[3], velocity);
			bossScene->AddEnemyBullet(std::move(newRightBullet));
		}
	}
	else {
		Vector3 leftHandActionPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, leftHandActionPos, leftHandAngle, 15, MotionMath::Y);
		leftHandActionPos.y = -3.5f;
		Vector3 rightHandActionPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, rightHandActionPos, rightHandAngle, 15, MotionMath::Y);
		rightHandActionPos.y = -3.5f;

		if (leftHandHP > deadHP) {
			leftHandPos.x = Easing::easeIn((float)actionPreTimer, (float)actionPreTime, leftHandActionPos.x, leftHandPos.x);
			leftHandPos.y = Easing::easeIn((float)actionPreTimer, (float)actionPreTime, leftHandActionPos.y, leftHandPos.y);
			leftHandPos.z = Easing::easeIn((float)actionPreTimer, (float)actionPreTime, leftHandActionPos.z, leftHandPos.z);
		}
		
		if (rightHandHP > deadHP) {
			rightHandPos.x = Easing::easeIn((float)actionPreTimer, (float)actionPreTime, rightHandActionPos.x, rightHandPos.x);
			rightHandPos.y = Easing::easeIn((float)actionPreTimer, (float)actionPreTime, rightHandActionPos.y, rightHandPos.y);
			rightHandPos.z = Easing::easeIn((float)actionPreTimer, (float)actionPreTime, rightHandActionPos.z, rightHandPos.z);
		}
	}

	if (isActionPost) {
		const Vector3 initLeftHandPos = { 15.0f, 0.0f, 0.0f };
		const Vector3 initRightHandPos = { -15.0f, 0.0f, 0.0f };
		const Vector3 initHandRot = { -90.0f, 0.0f, 0.0f };
		
		if (leftHandHP > deadHP) {
			leftHandPos.x = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initLeftHandPos.x, leftHandPos.x);
			leftHandPos.y = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initLeftHandPos.y, leftHandPos.y);
			leftHandPos.z = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initLeftHandPos.z, leftHandPos.z);

			leftHandRot.x = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initHandRot.x, leftHandRot.x);
			leftHandRot.y = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initHandRot.y, leftHandRot.y);
			leftHandRot.z = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initHandRot.z, leftHandRot.z);
		}
		
		if (rightHandHP > deadHP) {
			rightHandPos.x = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initRightHandPos.x, rightHandPos.x);
			rightHandPos.y = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initRightHandPos.y, rightHandPos.y);
			rightHandPos.z = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initRightHandPos.z, rightHandPos.z);

			rightHandRot.x = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initHandRot.x, rightHandRot.x);
			rightHandRot.y = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initHandRot.y, rightHandRot.y);
			rightHandRot.z = Easing::easeIn((float)actionPostTimer, (float)actionPreTime, initHandRot.z, rightHandRot.z);
		}

		actionPostTimer++;
		if (actionPostTimer >= actionPreTime) {
			actionCoolTimer = 0;
			actionPattern = 2;
			rollingShotTimer = 0;
			actionPreTimer = 0;
			actionPostTimer = 0;
			isActionPost = false;
		}
		
	}
}

void FirstBoss::Stomp()
{
	stompTimer++;
	if (stompTimer <= 50) {
		leftHandAngle = player->GetAngle();
		leftHandPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, leftHandPos, leftHandAngle, 15, MotionMath::Y);
		leftHandPos.y = 10.0f;
		leftHandRot.x = 0.0f;
	}
	else {
		leftHandPos.y -= 3.0f;
	}

	if (stompTimer >= stompTime) {
		actionCoolTimer = 0;
		stompTimer = 0;
		actionPattern = 1;
	}

	if (rightHandHP > deadHP) {
		rightHandAngle++;
		if (rightHandAngle >= 360.0f) {
			rightHandAngle = 0;
		}

		rightHandPos.y = -3.5f;
		rightHandPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, rightHandPos, rightHandAngle, 15, MotionMath::Y);

		rightHandRot.y = -rightHandAngle;

		XMVECTOR velocity = { 0, -1, 0 };
		velocity = XMVector3TransformNormal(velocity, rightHand->GetMatWorld());
		std::unique_ptr<EnemyBullet> newRightBullet = std::make_unique<EnemyBullet>();
		newRightBullet->Initialize(rightHand->GetMatWorld().r[3], velocity);
		bossScene->AddEnemyBullet(std::move(newRightBullet));
	}
}

void FirstBoss::Lariat()
{
	punchTimer++;
	if (punchTimer >= punchTime) {
		actionCoolTimer = 0;
		actionPattern = 1;
		punchTimer = 0;
	}

	if (leftHandHP > deadHP) {
		leftHandAngle += 2.0f;
		if (leftHandAngle >= 360.0f) {
			leftHandAngle = 0;
		}

		leftHandPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, leftHandPos, leftHandAngle, 18, MotionMath::Y);
		leftHandPos.y = -3.5f;

		leftHandRot.y = -leftHandAngle + 60;

		leftHandScale = { 0.8f, 0.8f, 0.8f };
	}

	if (rightHandHP > deadHP) {
		rightHandAngle += 2.0f;
		if (rightHandAngle >= 360.0f) {
			rightHandAngle = 0;
		}

		rightHandPos.y = -3.5f;
		rightHandPos = MotionMath::CircularMotion({ 0.0f, 0.0f, 0.0f }, rightHandPos, rightHandAngle, 18, MotionMath::Y);

		rightHandRot.y = -rightHandAngle + 60;

		rightHandScale = { 0.8f, 0.8f, 0.8f };
	}
}

void FirstBoss::DeadReaction()
{

	deadTimer++;
	pos.y -= 1.0f;
	rightHandPos.y -= 0.1f;
	boss->SetColor(damageColor);
	if (deadTimer >= deadTime) {
		isDead = true;
	}
}

void FirstBoss::LeftHandDeadReaction()
{
	if (leftHandDeadTimer >= leftHandDeadTime) {
		isLeftHandDead = true;
	}
	else {
		leftHandPos.y -= 0.1f;
		leftHandDeadTimer++;
		leftHand->SetColor(damageColor);
	}
}

void FirstBoss::RightHandDeadReaction()
{
	if (rightHandDeadTimer >= rightHandDeadTime) {
		isRightHandDead = true;
	}
	else {
		rightHandPos.y -= 0.1f;
		rightHandDeadTimer++;
		rightHand->SetColor(damageColor);
	}
}

void FirstBoss::HPBarUpdate()
{
	//最大HP(後々外部ファイルで管理するので仮)
	const int handMaxHp = 50;
	const int bossMaxHp = 100;
	//HPバーサイズセット用変数
	XMFLOAT2 bossHpBarSize = { 100.0f, 20.0f };
	XMFLOAT2 leftHandHpBarSize = { 50.0f, 20.0f };
	XMFLOAT2 rightHandHpBarSize = { 50.0f, 20.0f };
	XMFLOAT2 hpBarPos = { 0.0f, 0.0f };

	//HPバーサイズセット
	hpRedBar->SetSize(bossHpBarSize);
	leftHpRedBar->SetSize(leftHandHpBarSize);
	rightHpRedBar->SetSize(rightHandHpBarSize);

	bossHpBarSize.x = (float)bossMaxHp * (float)(hp / bossMaxHp);
	hpBar->SetSize(bossHpBarSize);
	leftHandHpBarSize.x = (float)handMaxHp * ((float)leftHandHP / (float)handMaxHp);
	leftHpBar->SetSize(leftHandHpBarSize);
	rightHandHpBarSize.x = (float)handMaxHp * ((float)rightHandHP / (float)handMaxHp);
	rightHpBar->SetSize(rightHandHpBarSize);

	//HPバー座標計算&セット
	XMVECTOR bossPos = { boss->GetMatWorld().r[3].m128_f32[0], boss->GetMatWorld().r[3].m128_f32[1], boss->GetMatWorld().r[3].m128_f32[2]};
	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
	bossPos = XMVector3TransformCoord(bossPos, matVPV);
	hpBarPos = { bossPos.m128_f32[0], bossPos.m128_f32[1] - 100.0f };
	hpBar->SetPosition(hpBarPos);
	hpRedBar->SetPosition(hpBarPos);

	XMVECTOR handPos = { leftHand->GetMatWorld().r[3].m128_f32[0], leftHand->GetMatWorld().r[3].m128_f32[1], leftHand->GetMatWorld().r[3].m128_f32[2] };
	handPos = XMVector3TransformCoord(handPos, matVPV);
	hpBarPos = { handPos.m128_f32[0], handPos.m128_f32[1] - 100.0f };
	leftHpBar->SetPosition(hpBarPos);
	leftHpRedBar->SetPosition(hpBarPos);

	handPos = { rightHand->GetMatWorld().r[3].m128_f32[0], rightHand->GetMatWorld().r[3].m128_f32[1], rightHand->GetMatWorld().r[3].m128_f32[2] };
	handPos = XMVector3TransformCoord(handPos, matVPV);
	hpBarPos = { handPos.m128_f32[0], handPos.m128_f32[1] - 100.0f };
	rightHpBar->SetPosition(hpBarPos);
	rightHpRedBar->SetPosition(hpBarPos);
}
