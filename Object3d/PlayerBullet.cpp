#include "PlayerBullet.h"

void PlayerBullet::Initialize(Vector3 pos) {
	const Vector3 bulletSize = { 2, 2, 2 };

	bulletModel = Model::CreateModel("Block");
	bullet = Object3d::Create(bulletModel);
	bullet->SetScale(bulletSize);
	bullet->SetRotation(Vector3(0, 0, 0));
	initPos = pos;
	this->pos = pos;
	bullet->SetPosition(this->pos);
}

void PlayerBullet::Update() {
	if (pos.z <= initPos.z + 100.0f) {
		pos.z += 1.0f;
	}
	else {
		isDead = true;
	}

	if (bullet != nullptr) {
		bullet->SetPosition(pos);
		bullet->Update();
	}
}

void PlayerBullet::Draw() {
	bullet->Draw();
}
