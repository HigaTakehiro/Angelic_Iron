#include "Enemy.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <wrl.h>

using namespace std;

void Enemy::Initialize() {
	enemyModel = Model::CreateModel("Enemy");
	shotModel = Model::CreateModel("Block");

	//ファイルストリーム
	ifstream file;

	const string filename = "EnemySet.txt";
	const string directory = "Resources/";
	file.open(directory + filename);
	if (file.fail()) {
		assert(0);
	}
	string line;
	while (getline(file, line)) {
		istringstream line_stream(line);
		string word;
		//半角区切りで文字列を取得
		getline(line_stream, word, ' ');
		if (word == "Pos") {
			Vector3 pos{};
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;

			enemyPos.push_back(pos);
		}
		if (word == "Rot") {
			Vector3 rot{};
			line_stream >> rot.x;
			line_stream >> rot.y;
			line_stream >> rot.z;

			enemyRot.push_back(rot);
		}
		if (word == "Scale") {
			Vector3 scale{};
			line_stream >> scale.x;
			line_stream >> scale.y;
			line_stream >> scale.z;

			enemyScale.push_back(scale);
		}
	}

	file.close();

	for (int i = 0; i < 3; i++) {
		shotPos[i] = enemyPos[i];
		shotScale[i] = { 2, 2, 2 };

		enemy[i] = Object3d::Create(enemyModel);
		enemy[i]->SetPosition(enemyPos[i]);
		enemy[i]->SetScale(enemyScale[i]);
		enemy[i]->SetRotation(enemyRot[i]);

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
	enemyPos.clear();
	enemyPos.shrink_to_fit();
	enemyRot.clear();
	enemyRot.shrink_to_fit();
	enemyScale.clear();
	enemyScale.shrink_to_fit();
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