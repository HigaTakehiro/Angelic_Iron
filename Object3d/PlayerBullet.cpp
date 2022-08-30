#include "PlayerBullet.h"

void PlayerBullet::Initialize(Vector3 pos) {
	const Vector3 bulletSize = { 2, 2, 2 };

	bulletModel = Model::CreateModel("Block");
	bullet = Object3d::Create(bulletModel);
	bullet->SetScale(bulletSize);
	bullet->SetRotation(Vector3(0, 0, 0));
	bullet->SetPosition(pos);
}

void PlayerBullet::Update() {
	bullet->Update();
}

void PlayerBullet::Draw() {
	bullet->Draw();
}
