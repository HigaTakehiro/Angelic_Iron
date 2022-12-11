#include "BossScenePlayer.h"

const int32_t BossScenePlayer::rotationTime = 30;
const int32_t BossScenePlayer::dashTime = 30;
const float BossScenePlayer::gravity = 8.0f;

void BossScenePlayer::Initialize(Camera* camera)
{
	//カメラをセット
	this->camera = camera;

	player = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Player_Normal));
	player->SetCameraParent(this->camera);
	pos = { 0.0f, -10.0f, -25.0f };
	rot = { 0.0f, 90.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };

	cameraAngle = 0.0f;
	cameraPos = { 0, -20.0f, 0 };
	cameraPos = MotionMath::GetIns()->CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos, cameraAngle, 250.0f, MotionMath::Y);

	camera->SetTarget({ 0.0f, 0.0f, 0.0f });
	camera->SetEye(cameraPos);
	player->SetPosition(pos);
	player->SetRotation(rot);
	player->SetScale(scale);

	rotationTimer = 0;
	jumpPower = 0.0f;
	isDash = false;
	isLeftDash = false;
	isRightDash = false;
	isJump = false;
}

void BossScenePlayer::Update()
{
	const float lowerLimit = -10.0f;
	camera->SetTarget({ 0.0f, 0.0f, 0.0f });
	camera->SetEye(cameraPos);
	player->SetPosition(pos);
	player->SetRotation(rot);
	player->Update();

	if (!isDash) {
		Move();
		Jump();
	}
	Dash();

	if (pos.y < lowerLimit) {
		//pos.y = -10.0f;
		pos.y += gravity;
	}
}

void BossScenePlayer::Draw()
{
	player->Draw();
}

void BossScenePlayer::SpriteDraw()
{
}

void BossScenePlayer::Finalize() {
	safe_delete(player);
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
		cameraPos = MotionMath::GetIns()->CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos, cameraAngle, 250.0f, MotionMath::Y);

		if (rot.y <= leftRot) {
			rot.y = Easing::GetIns()->easeIn(rotationTimer, rotationTime, leftRot, rot.y);
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
		cameraPos = MotionMath::GetIns()->CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos, cameraAngle, 250.0f, MotionMath::Y);

		if (rot.y >= rightRot) {
			rot.y = Easing::GetIns()->easeIn(rotationTimer, rotationTime, rightRot, rot.y);
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

	if (KeyInput::GetIns()->PushKey(DIK_A) && KeyInput::GetIns()->TriggerKey(DIK_LSHIFT) && !isDash) {
		isDash = true;
		isLeftDash = true;
		initAngle = cameraAngle;
	}
	else if (KeyInput::GetIns()->PushKey(DIK_D) && KeyInput::GetIns()->TriggerKey(DIK_LSHIFT) && !isDash) {
		isDash = true;
		isRightDash = true;
		initAngle = cameraAngle;
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
		cameraAngle = Easing::GetIns()->easeIn(dashTimer, dashTime, initAngle - moveAngle, cameraAngle);
		cameraPos = MotionMath::GetIns()->CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos, cameraAngle, 250.0f, MotionMath::Y);
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
		cameraAngle = Easing::GetIns()->easeIn(dashTimer, dashTime, initAngle + moveAngle, cameraAngle);
		cameraPos = MotionMath::GetIns()->CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos, cameraAngle, 250.0f, MotionMath::Y);
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
