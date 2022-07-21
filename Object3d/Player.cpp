#include "Player.h"
#include "SafeDelete.h"

void Player::Initialize(Camera* camera) {
	this->camera = camera;

	Sprite::LoadTexture(1, L"Resources/Aim.png");
	aim = Sprite::Create(1, { 0, 0 });
	aim->SetSize(XMFLOAT2(100.0f, 100.0f));

	playerModel = Model::CreateModel("Player");
	player = Object3d::Create(playerModel);
	playerScale = { 5, 5, 5 };
	playerPos = { 50, 0, 0 };
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
		targetAimPos = Vector3(MouseInput::GetIns()->GetMousePoint().x, MouseInput::GetIns()->GetMousePoint().y, 500.0f);
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

	player->SetPosition(playerPos);
}

void Player::Shot() {
	const float shotSpeed = 3.0f;
	const float windowOverX = -100.0f;

	Vector3 direction = oldShotPos - targetAimPos;
	direction.normalize();

	shotPos -= direction * shotSpeed;
	shot->SetPosition(shotPos);

	if (shotPos.z >= 100.0f || shotPos.x <= windowOverX || shotPos.x >= WinApp::window_width) {
		isShot = false;
	}
}