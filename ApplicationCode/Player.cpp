#include "Player.h"
#include "SafeDelete.h"

void Player::Initialize(Camera* camera) {
	this->camera = camera;

	Sprite::LoadTexture(1, L"Resources/Aim.png");
	aim = Sprite::Create(1, { 0, 0 });
	aim->SetSize(XMFLOAT2(100.0f, 100.0f));

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
	aim3d->SetPosition(Vector3(0, 0, 50));
	aim3d->SetRotation(Vector3(0, 0, 0));
	aim3d->SetParent(player);
}

void Player::Finalize() {
	safe_delete(player);
	safe_delete(playerModel);
	safe_delete(aim);
	safe_delete(aim3d);
}

void Player::Update() {
	bullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });

	Move();

	playerWPos = player->GetMatWorld().r[3];

	AimUpdate();

	if (KeyInput::GetIns()->PushKey(DIK_SPACE) && !isShot) {
		//targetAimPos = Vector3(aimPos.x, aimPos.y, 500.0f);
		//targetAimPos.normalize();
		//shotPos = playerWPos;
		//oldShotPos = shotPos;
		//shot->SetPosition(shotPos);
		isShot = true;
	}

	if (isShot) {
		Shot();
	}

	//playerLPos.z = -50.0f;
	//aim3d->SetPosition(Vector3(aimPos.x, aimPos.y, 50));

	aim->SetPosition(XMFLOAT2(aimPos.x - 50.0f, aimPos.y - 50.0f));
	aim3d->Update();
	player->Update();
	for (std::unique_ptr<PlayerBullet>& bullet : bullets) {
		bullet->Update();
	}
}

void Player::SpriteDraw() {
	aim->Draw();
}

void Player::ObjectDraw() {
	player->Draw();
	aim3d->Draw();

	//if (isShot) {
	//	shot->Draw();
	//}
	for (std::unique_ptr<PlayerBullet>& bullet : bullets) {
		bullet->Draw();
	}
}

void Player::Move() {
	const float moveSpeed = 2.0f;
	const float autoSpeed = 0.2;
	const float playerAngle = 180.0f;
	const float stopAngleY = 45.0f;
	const float stopAngleX = 30.0f;
	const float stopPosX = 40.0f;
	const float stopPosY = 20.0f;

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

	if (KeyInput::GetIns()->PushKey(DIK_LEFT) && playerRot.y >= playerAngle - stopAngleY) {
		playerRot.y -= moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_RIGHT) && playerRot.y <= playerAngle + stopAngleY) {
		playerRot.y += moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_UP) && playerRot.x >= -stopAngleX) {
		playerRot.x -= moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_DOWN) && playerRot.x <= stopAngleX) {
		playerRot.x += moveSpeed;
	}

	player->SetPosition(playerLPos);
	player->SetRotation(playerRot);
}

void Player::Shot() {
	const float bulletSpeed = 5.0f;
	XMVECTOR velocity;
	velocity = { aim3d->GetMatWorld().r[3] - player->GetMatWorld().r[3] };
	velocity = XMVector3Normalize(velocity) * bulletSpeed;

	//velocity = MatCalc::GetIns()->VecDivided(velocity, player->GetMatWorld());

	std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
	newBullet->Initialize(playerWPos, velocity);

	bullets.push_back(std::move(newBullet));

	isShot = false;
}

void Player::Reset() {
	playerScale = { 2, 2, 2 };
	playerLPos = { 0, 0, -50 };
	playerRot = { 0, 180, 0 };

	player->SetPosition(playerLPos);
	for (const std::unique_ptr<PlayerBullet>& bullet : bullets) {
		bullet->OnCollision();
	}
}

void Player::AimUpdate() {

	//2D¨3D
	const float kDistancePlayerTo3DRaticle = 50.0f;
	XMVECTOR offset = { 0, 0, 1.0f };
	offset = MatCalc::GetIns()->VecDivided(offset, player->GetMatWorld());
	offset = XMVector3Normalize(offset) * kDistancePlayerTo3DRaticle;

	XMVECTOR raticle2D = { aim3d->GetMatWorld().r[3] };
	XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
	raticle2D = MatCalc::GetIns()->Wdivided(raticle2D, matViewProjectionViewport);

	aimPos = { raticle2D.m128_f32[0], raticle2D.m128_f32[1] };

	//3D¨2D
	//aimPos = XMFLOAT2(MouseInput::GetIns()->GetMousePoint().x, MouseInput::GetIns()->GetMousePoint().y);

	//XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
	//XMMATRIX matInverseVPV = XMMatrixInverse(nullptr, matVPV);
	//XMVECTOR posNear = { (float)aimPos.x, (float)aimPos.y, 0 };
	//XMVECTOR posFar = { (float)aimPos.x, (float)aimPos.y, 1 };

	//posNear = MatCalc::GetIns()->Wdivided(posNear, matInverseVPV);
	//posFar = MatCalc::GetIns()->Wdivided(posFar, matInverseVPV);

	//XMVECTOR mouseDirection = posFar - posNear;
	//mouseDirection = XMVector3Normalize(mouseDirection);

	//const float kDistanceTestObject = 20.0f;
	//mouseDirection = mouseDirection * kDistanceTestObject;
	//mouseDirection = MatCalc::GetIns()->VecDivided(mouseDirection, camera->GetMatWorld());
	//aimPos3d = posNear + mouseDirection;

	//aim3d->SetPosition(aimPos3d);

}