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
	playerPos = { 50, 0, -50 };
	playerRot = { 0, 0, 0 };
	player->SetScale(playerScale);
	player->SetPosition(playerPos);
	player->SetRotation(playerRot);

	shotModel = Model::CreateModel("Block");
	shot = Object3d::Create(shotModel);
	shotScale = { 2, 2, 2 };
	shotPos = { 50, 0, 0 };
	shotRot = { 0, 0, 0 };
	shot->SetScale(shotScale);
	shot->SetPosition(shotPos);
	shot->SetRotation(shotRot);
}

void Player::Finalize() {
	safe_delete(player);
	safe_delete(playerModel);
	safe_delete(shot);
	safe_delete(shotModel);
	safe_delete(aim);
}

void Player::Update() {
	Move();
	aimPos = XMFLOAT2(MouseInput::GetIns()->GetMousePoint().x - 50.0f, MouseInput::GetIns()->GetMousePoint().y - 50.0f);

	if (MouseInput::GetIns()->TriggerClick(MouseInput::GetIns()->LEFT_CLICK) && !isShot) {
		targetAimPos = Vector3(aimPos.x, aimPos.y, 500.0f);
		targetAimPos.normalize();
		shotPos = playerPos;
		oldShotPos = shotPos;
		shot->SetPosition(shotPos);
		isShot = true;
	}

	if (isShot) {
		Shot();
	}

	aim->SetPosition(aimPos);
	player->Update();
	shot->Update();
}

void Player::SpriteDraw() {
	aim->Draw();
}

void Player::ObjectDraw() {
	player->Draw();

	if (isShot) {
		shot->Draw();
	}

}

void Player::Move() {
	const float moveSpeed = 2.0f;
	const float autoSpeed = 0.2;

	if (KeyInput::GetIns()->PushKey(DIK_W)) {
		playerPos.y += moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_S)) {
		playerPos.y -= moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_A)) {
		playerPos.x -= moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_D)) {
		playerPos.x += moveSpeed;
	}

	playerPos.z += autoSpeed;

	player->SetPosition(playerPos);
}

void Player::Shot() {
	const float shotSpeed = 3.0f;
	const float windowOverX_Left = -100.0f;
	const float windowOverX_Right = 200.0f;
	const XMMATRIX matViewport = player->GetMatWorld() * Camera::GetMatView() * Camera::GetMatView();
	matVPV = Camera::GetMatView() * Camera::GetMatProjection() * matViewport;
	matInverseVPV = XMMatrixInverse(nullptr, matVPV);
	posNear = { WinApp::window_width, WinApp::window_height, 0 };
	posFar = { WinApp::window_width, WinApp::window_height, 1 };

	posNear = XMVector3TransformCoord(posNear, matInverseVPV);
	posFar = XMVector3TransformCoord(posFar, matInverseVPV);

	posNearMath = posNear;
	posFarMath = posFar;

	mouseDirection = posNear - posFar;
	mouseDirection.normalize();

	const float kDistanceTestObject = 50.0f;
	shotPos += (posNearMath - mouseDirection) / kDistanceTestObject;
	shot->SetPosition(shotPos);

	if (shotPos.z >=  playerPos.z + 100.0f || shotPos.x <= windowOverX_Left || shotPos.x >= windowOverX_Right) {
		isShot = false;
	}
}