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
	playerLPos = { 0, 0, -50 };
	playerRot = { 0, 180, 0 };
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
	aim3d->SetPosition(Vector3(0, 0, 50));
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

	playerWPos = player->GetMatWorld().r[3];

	AimUpdate();

	if (KeyInput::GetIns()->TriggerKey(DIK_SPACE) && !isShot) {
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

	playerLPos.z = -50.0f;
	//aim3d->SetPosition(Vector3(aimPos.x, aimPos.y, 50));

	aim->SetPosition(XMFLOAT2(aimPos.x - 50.0f, aimPos.y - 50.0f));
	aim3d->Update();
	shot->Update();
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

	if (KeyInput::GetIns()->PushKey(DIK_W)) {
		playerLPos.y += moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_S)) {
		playerLPos.y -= moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_A)) {
		playerLPos.x += moveSpeed;
	}
	if (KeyInput::GetIns()->PushKey(DIK_D)) {
		playerLPos.x -= moveSpeed;
	}

	//playerPos.z += autoSpeed;
	//playerWPos = playerLPos * player->GetMatWorld().r->m128_f32[3];

	player->SetPosition(playerLPos);
}

void Player::Shot() {
	const float shotSpeed = 3.0f;
	const float windowOverX_Left = -100.0f;
	const float windowOverX_Right = 200.0f;

	std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
	newBullet->Initialize(playerWPos);

	bullets.push_back(std::move(newBullet));

	isShot = false;

	//shotPos.z += shotSpeed;
	//shot->SetPosition(shotPos);

	//if (shotPos.z >= playerWPos.z + 100.0f || shotPos.x <= windowOverX_Left || shotPos.x >= windowOverX_Right) {
	//	isShot = false;
	//}
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

	//const float kDistancePlayerTo3DRaticle = 50.0f;
	//XMVECTOR offset = { 0, 0, 1.0f };
	//offset = VecDivided(offset, player->GetMatWorld());
	//offset = XMVector3Normalize(offset) * kDistancePlayerTo3DRaticle;

	//aimPos3d.x = playerWPos.x + offset.m128_f32[0];
	//aimPos3d.y = playerWPos.y + offset.m128_f32[1];
	//aimPos3d.z = playerWPos.z + offset.m128_f32[2];

	/*XMVECTOR raticle2D = { aim3d->GetMatWorld().r[3] };
	XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
	raticle2D = Wdivided(raticle2D, matViewProjectionViewport);

	aimPos = { raticle2D.m128_f32[0] - 50.0f, raticle2D.m128_f32[1] - 50.0f };*/
	aimPos = XMFLOAT2(MouseInput::GetIns()->GetMousePoint().x, MouseInput::GetIns()->GetMousePoint().y);

	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
	XMMATRIX matInverseVPV = XMMatrixInverse(nullptr, matVPV);
	XMVECTOR posNear = { (float)aimPos.x, (float)aimPos.y, 0 };
	XMVECTOR posFar = { (float)aimPos.x, (float)aimPos.y, 1 };

	posNear = Wdivided(posNear, matInverseVPV);
	posFar = Wdivided(posFar, matInverseVPV);

	XMVECTOR mouseDirection = posFar - posNear;
	mouseDirection = XMVector3Normalize(mouseDirection);

	const float kDistanceTestObject = 50.0f;
	aimPos3d = (mouseDirection + posNear) * kDistanceTestObject;

	aim3d->SetPosition(aimPos3d);

}

XMVECTOR Player::Wdivided(XMVECTOR vec, XMMATRIX mat) {
	float x, y, z, w;

	x = (vec.m128_f32[0] * mat.r[0].m128_f32[0]) + (vec.m128_f32[1] * mat.r[1].m128_f32[0]) + (vec.m128_f32[2] * mat.r[2].m128_f32[0]) + (1.0f * mat.r[3].m128_f32[0]);
	y = (vec.m128_f32[0] * mat.r[0].m128_f32[1]) + (vec.m128_f32[1] * mat.r[1].m128_f32[1]) + (vec.m128_f32[2] * mat.r[2].m128_f32[1]) + (1.0f * mat.r[3].m128_f32[1]);
	z = (vec.m128_f32[0] * mat.r[0].m128_f32[2]) + (vec.m128_f32[1] * mat.r[1].m128_f32[2]) + (vec.m128_f32[2] * mat.r[2].m128_f32[2]) + (1.0f * mat.r[3].m128_f32[2]);
	w = 1.0f;
	
	w = z;
	x = x / w;
	y = y / w;
	z = z / w;

	return XMVECTOR{ x, y, z, w };
}

XMVECTOR Player::VecDivided(XMVECTOR vec, XMMATRIX mat) {
	float x, y, z, w;

	x = (vec.m128_f32[0] * mat.r[0].m128_f32[0]) + (vec.m128_f32[1] * mat.r[1].m128_f32[0]) + (vec.m128_f32[2] * mat.r[2].m128_f32[0]) + (0.0f * mat.r[3].m128_f32[0]);
	y = (vec.m128_f32[0] * mat.r[0].m128_f32[1]) + (vec.m128_f32[1] * mat.r[1].m128_f32[1]) + (vec.m128_f32[2] * mat.r[2].m128_f32[1]) + (0.0f * mat.r[3].m128_f32[1]);
	z = (vec.m128_f32[0] * mat.r[0].m128_f32[2]) + (vec.m128_f32[1] * mat.r[1].m128_f32[2]) + (vec.m128_f32[2] * mat.r[2].m128_f32[2]) + (0.0f * mat.r[3].m128_f32[2]);
	w = 0.0f;

	return XMVECTOR{ x, y, z, w };
}