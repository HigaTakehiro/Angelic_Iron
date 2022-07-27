#include "Enemy.h"

void Enemy::Initialize() {
	enemyModel = Model::CreateModel("Enemy");
	shotModel = Model::CreateModel("Block");

	enemyPos[0] = { 30, 0, 50 };
	enemyPos[1] = { 80, -10, 150 };
	enemyPos[2] = { 20, 20, 300 };
	enemyRot = { 0, 180, 0 };
	for (int i = 0; i < 3; i++) {
		shotPos[i] = enemyPos[i];
		shotScale[i] = { 2, 2, 2 };

		enemy[i] = Object3d::Create(enemyModel);
		enemy[i]->SetPosition(enemyPos[i]);
		enemy[i]->SetScale(enemyScale);
		enemy[i]->SetRotation(enemyRot);

		shot[i] = Object3d::Create(shotModel);
		shot[i]->SetPosition(shotPos[i]);
		shot[i]->SetScale(shotScale[i]);
	}

}

void Enemy::Update() {
	for (int i = 0; i < 3; i++) {
		enemy[i]->Update();
	}
}

void Enemy::Draw(bool isEnemyDead[]) {
	for (int i = 0; i < 3; i++) {
		if (!isEnemyDead[i]) {
			enemy[i]->Draw();
		}
	}
}

void Enemy::Finalize() {
	for (int i = 0; i < 3; i++) {
		safe_delete(enemy[i]);
	}
}

void Enemy::Shot() {

}

//bool Enemy::ShotRangeJudge(Object3d* player) {
//	for (int i = 0; i < 3; i++) {
//		if (enemyPos[i].z > player->GetPosition().z) return true;
//	}
//	
//	return false;
//}