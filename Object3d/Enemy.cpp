#include "Enemy.h"

void Enemy::Initialize() {
	enemyModel = Model::CreateModel("Enemy");
	enemyPos[0] = { 30, 0, 50 };
	enemyPos[1] = { 80, -10, 150 };
	enemyPos[2] = { 20, 20, 300 };
	enemyRot = { 0, 180, 0 };
	for (int i = 0; i < 3; i++) {
		enemy[i] = Object3d::Create(enemyModel);
		enemy[i]->SetPosition(enemyPos[i]);
		enemy[i]->SetScale(enemyScale);
		enemy[i]->SetRotation(enemyRot);
	}

}

void Enemy::Update() {
	for (int i = 0; i < 3; i++) {
		enemy[i]->Update();
	}
}

void Enemy::Draw() {
	for (int i = 0; i < 3; i++) {
		enemy[i]->Draw();
	}
}

void Enemy::Finalize() {
	for (int i = 0; i < 3; i++) {
		safe_delete(enemy[i]);
	}
}
