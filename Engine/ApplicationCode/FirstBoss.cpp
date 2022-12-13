#include "FirstBoss.h"

const int32_t FirstBoss::rotationTime = 15;
const int32_t FirstBoss::actionCoolTime = 60;
const int32_t FirstBoss::rollingShotTime = 90;

void FirstBoss::Initialize(ModelManager::ModelName model, const Vector3& pos) {
	boss = Object3d::Create(ModelManager::GetIns()->GetModel(model));
	this->pos = pos;
	scale = { 10, 10, 10 };
	rot = { 0, 90, 0 };
	hp = 100;
	attackPower = 1;
	actionCoolTimer = 0;
	actionPattern = 1;
	rotationTimer = 0;

	boss->SetPosition(this->pos);
	boss->SetRotation(rot);
	boss->SetScale(scale);

	leftHand = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::BossHand));
	rightHand = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::BossHand));

	leftHandPos = { 15.0f, 0.0f, 0.0f };
	leftHandScale = { 1.0f, 1.0f, 1.0f };
	leftHandRot = { -90.0f, 0.0f, 0.0f };
	leftHandHP = 50;
	leftHandDamageTimer = 0;
	leftHand->SetParent(boss);
	leftHand->SetPosition(leftHandPos);
	leftHand->SetScale(leftHandScale);
	leftHand->SetRotation(leftHandRot);

	rightHandPos = { -15.0f, 0.0f, 0.0f };
	rightHandScale = { 1.0f, 1.0f, 1.0f };
	rightHandRot = { -90.0f, 0.0f, 0.0f };
	rightHandHP = 50;
	rightHandDamageTimer = 0;
	rightHand->SetParent(boss);
	rightHand->SetPosition(rightHandPos);
	rightHand->SetRotation(rightHandRot);
	rightHand->SetScale(rightHandScale);

	rollingShotTimer = 0;
	leftHandAngle = 0.0f;
	rightHandAngle = 180.0f;
}

void FirstBoss::Update(const Vector3& playerPos, const int delayTime)
{
	this->playerPos = playerPos;
	if (leftHandHP <= 0) {
		isLeftHandDead = true;
	}
	if (rightHandHP <= 0) {
		isRightHandDead = true;
	}

	boss->Update();
	leftHand->SetPosition(leftHandPos);
	rightHand->SetPosition(rightHandPos);
	leftHand->SetRotation(leftHandRot);
	rightHand->SetRotation(rightHandRot);
	leftHand->Update();
	rightHand->Update();
	DamageReaction();
	LeftHandDamageReaction();
	RightHandDamageReaction();
	Action();

}

void FirstBoss::Draw()
{
	boss->Draw();
	if (!isLeftHandDead) {
		leftHand->Draw();
	}
	if (!isRightHandDead) {
		rightHand->Draw();
	}
}

void FirstBoss::Finalize()
{
	safe_delete(boss);
	safe_delete(leftHand);
	safe_delete(rightHand);
}

void FirstBoss::Action()
{
	actionCoolTimer++;
	leftHandPos.y = 0.0f;
	rightHandPos.y = 0.0f;
	leftHandRot.y = 0.0f;
	rightHandRot.y = 0.0f;
	if (actionCoolTimer >= actionCoolTime) {
		switch (actionPattern)
		{
		case 1:
			RollingShot();
			break;
		case 2:
			actionPattern = 1;
			break;
		default:
			break;
		}
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
		leftHand->SetColor({ 1.0f, 0.3f, 0.3f, 1.0f });
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
		rightHand->SetColor({ 1.0f, 0.3f, 0.3f, 1.0f });
	}

	if (rightHandDamageTimer >= damageTime) {
		isRightHandDamage = false;
		rightHandDamageTimer = 0;
		rightHand->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	}
}

void FirstBoss::Rotation()
{
	//float angle = player->GetAngle();
}

void FirstBoss::RollingShot() {
	rollingShotTimer++;
	if (rollingShotTimer >= rollingShotTime) {
		actionCoolTimer = 0;
		actionPattern = 2;
		rollingShotTimer = 0;
	}
	const float bulletSpeed = 0.001f;

	leftHandAngle++;
	if (leftHandAngle >= 360.0f) {
		leftHandAngle = 0;
	}
	rightHandAngle++;
	if (rightHandAngle >= 360.0f) {
		rightHandAngle = 0;
	}
	leftHandPos = MotionMath::GetIns()->CircularMotion({ 0.0f, 0.0f, 0.0f }, leftHandPos, leftHandAngle, 15, MotionMath::Y);
	leftHandPos.y = -3.5f;
	rightHandPos.y = -3.5f;
	rightHandPos = MotionMath::GetIns()->CircularMotion({ 0.0f, 0.0f, 0.0f }, rightHandPos, rightHandAngle, 15, MotionMath::Y);
	leftHandRot.y = -leftHandAngle;
	rightHandRot.y = -rightHandAngle;

	if (!isLeftHandDead) {
		XMVECTOR velocity = { 0, -1, 0 };
		velocity = MatCalc::GetIns()->VecDivided(velocity, leftHand->GetMatWorld());
		std::unique_ptr<EnemyBullet> newLeftBullet = std::make_unique<EnemyBullet>();
		newLeftBullet->Initialize(leftHand->GetMatWorld().r[3], velocity);
		bossScene->AddEnemyBullet(std::move(newLeftBullet));
	}

	if (!isRightHandDead) {
		XMVECTOR velocity = { 0, -1, 0 };
		velocity = MatCalc::GetIns()->VecDivided(velocity, rightHand->GetMatWorld());
		std::unique_ptr<EnemyBullet> newRightBullet = std::make_unique<EnemyBullet>();
		newRightBullet->Initialize(rightHand->GetMatWorld().r[3], velocity);
		bossScene->AddEnemyBullet(std::move(newRightBullet));
	}
	
}