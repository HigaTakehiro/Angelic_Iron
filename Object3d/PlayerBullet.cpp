#include "PlayerBullet.h"

void PlayerBullet::Initialize() {
	const Vector3 bulletSize = { 2, 2, 2 };

	bulletModel = Model::CreateModel("Block");
	bullet = Object3d::Create(bulletModel);
	bullet->SetScale(bulletSize);
}

void PlayerBullet::Update() {
	bullet->Update();
}

void PlayerBullet::Draw() {
	bullet->Draw();
}
