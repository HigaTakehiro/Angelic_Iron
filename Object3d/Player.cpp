#include "Player.h"
#include "SafeDelete.h"

void Player::Initialize(Camera* camera) {
	this->camera = camera;

	Sprite::LoadTexture(1, L"Resources/Aim.png");
	aim = Sprite::Create(1, { 0, 0 });
	aim->SetSize(XMFLOAT2(100.0f, 100.0f));

	playerModel = Model::CreateModel("Player");
	player = Object3d::Create(playerModel);
	playerScale = { 2, 2, 2 };
	playerLPos = { 0, 0, 50 };
	playerRot = { 0, 0, 0 };
	player->SetScale(playerScale);
	player->SetPosition(playerLPos);
	player->SetRotation(playerRot);
	player->SetCameraParent(camera);

	shotModel = Model::CreateModel("Block");
	shot = Object3d::Create(shotModel);
	shotScale = { 2, 2, 2 };
	shotPos = { 50, 0, 0 };
	shotRot = { 0, 0, 0 };
	shot->SetScale(shotScale);
	shot->SetPosition(shotPos);
	shot->SetRotation(shotRot);

	aim3d = Object3d::Create(shotModel);
	aim3d->SetScale(shotScale);
	aim3d->SetPosition(Vector3(0, 0, 200));
	aim3d->SetRotation(shotRot);
	//aim3d->SetParent(player);
}

void Player::Finalize() {
	safe_delete(player);
	safe_delete(playerModel);
	safe_delete(shot);
	safe_delete(shotModel);
	safe_delete(aim);
	safe_delete(aim3d);
}

void Player::Update() {
	Move();
	//positionRaticle = XMLoadFloat3(&aimPos3d);
	//matViewPort = player->GetMatWorld() * Camera::GetMatView() * Camera::GetMatProjection();
	//matViewProjection = Camera::GetMatView() * Camera::GetMatProjection() * matViewPort;
	//positionRaticle = XMVector3TransformCoord(positionRaticle, matViewProjection);
	//aimPos = XMFLOAT2(positionRaticle.m128_f32[0], positionRaticle.m128_f32[1]);
	aimPos = XMFLOAT2(MouseInput::GetIns()->GetMousePoint().x - 50, MouseInput::GetIns()->GetMousePoint().y - 50);

	playerWPos = player->GetMatWorld().r[3];

	AimUpdate();

	if (KeyInput::GetIns()->TriggerKey(DIK_SPACE) && !isShot) {
		targetAimPos = Vector3(aimPos.x, aimPos.y, 500.0f);
		targetAimPos.normalize();
		shotPos = playerWPos;
		oldShotPos = shotPos;
		shot->SetPosition(shotPos);
		isShot = true;
	}

	if (isShot) {
		Shot();
	}

	//aim3d->SetPosition(Vector3(aimPos.x, aimPos.y, 50));

	aim->SetPosition(aimPos);
	aim3d->Update();
	shot->Update();
	player->Update();
}

void Player::SpriteDraw() {
	aim->Draw();
}

void Player::ObjectDraw() {
	player->Draw();
	aim3d->Draw();

	if (isShot) {
		shot->Draw();
	}

}

void Player::Move() {
	const float moveSpeed = 2.0f;
	const float autoSpeed = 0.2;

	if (KeyInput::GetIns()->PushKey(DIK_W)) {
		playerLPos.y += moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_S)) {
		playerLPos.y -= moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_A)) {
		playerLPos.x -= moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_D)) {
		playerLPos.x += moveSpeed;
	}

	//playerPos.z += autoSpeed;
	//playerWPos = playerLPos * player->GetMatWorld().r->m128_f32[3];

	player->SetPosition(playerLPos);
}

void Player::Shot() {
	const float shotSpeed = 3.0f;
	const float windowOverX_Left = -100.0f;
	const float windowOverX_Right = 200.0f;
	//const XMMATRIX matViewport = player->GetMatWorld() * Camera::GetMatView() * Camera::GetMatProjection();
	//matVPV = Camera::GetMatView() * Camera::GetMatProjection() * matViewport;
	//matInverseVPV = XMMatrixInverse(nullptr, matVPV);
	//posNear = { aimPos.x, aimPos.y, 0 };
	//posFar = { aimPos.x, aimPos.y, 1 };

	//posNear = XMVector3TransformCoord(posNear, matInverseVPV);
	//posFar = XMVector3TransformCoord(posFar, matInverseVPV);

	//posNearMath = posNear;
	//posFarMath = posFar;

	//mouseDirection = posNear - posFar;
	//mouseDirection = XMVector3Normalize(mouseDirection);

	//const float kDistanceTestObject = 50.0f;
	//aimPos3d.x = ((mouseDirection.m128_f32[0] * mouseDirection.m128_f32[0]) * (posNear.m128_f32[0] * posNear.m128_f32[0])) - kDistanceTestObject;
	//aimPos3d.y = ((mouseDirection.m128_f32[1] * mouseDirection.m128_f32[1]) * (posNear.m128_f32[1] * posNear.m128_f32[1])) - kDistanceTestObject;
	//aimPos3d.z = ((mouseDirection.m128_f32[2] * mouseDirection.m128_f32[2]) * (posNear.m128_f32[2] * posNear.m128_f32[2])) + kDistanceTestObject;

	//aim3d->SetPosition(aimPos3d);
	//shot->SetPosition(shotPos);

	shotPos.z += shotSpeed;
	shot->SetPosition(shotPos);

	if (shotPos.z >= playerWPos.z + 100.0f || shotPos.x <= windowOverX_Left || shotPos.x >= windowOverX_Right) {
		isShot = false;
	}
}

void Player::Reset() {
	playerScale = { 2, 2, 2 };
	playerLPos = { 0, 0, 50 };
	playerRot = { 0, 0, 0 };
	shotScale = { 2, 2, 2 };
	shotPos = { 50, 0, 0 };
	shotRot = { 0, 0, 0 };

	player->SetPosition(playerLPos);
	shot->SetPosition(playerWPos);
}

void Player::AimUpdate() {
 	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
	XMMATRIX matInverseVPV = XMMatrixInverse(nullptr, matVPV);
	posNear = { aimPos.x, aimPos.y, 0 };
	posFar = { aimPos.x, aimPos.y, 1 };

	posNear = XMVector3TransformCoord(posNear, matInverseVPV);
	posFar = XMVector3TransformCoord(posFar, matInverseVPV);

	mouseDirection = posFar - posNear;
	mouseDirection = XMVector3Normalize(mouseDirection);

	const float kDistanceTestObject = 50.0f;
	aimPos3d = mouseDirection * posNear;
	//aimPos3d.z = kDistanceTestObject;

	aim3d->SetPosition(aimPos3d);
}