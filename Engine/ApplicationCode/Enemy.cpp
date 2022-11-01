#include "Enemy.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <wrl.h>

using namespace std;

Enemy::Enemy() {

}

Enemy::~Enemy() {
	delete enemy;
	delete test;
}

void Enemy::Initialize(const string& modelName, const Vector3& pos, const Vector3& scale, const string& style) {
	enemy = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Enemy));
	enemy->SetPosition(pos);
	test = Sprite::Create(ImageManager::ImageName::aim, { 0, 0 });
	test->SetSize(XMFLOAT2(100.0f, 100.0f));
	test->SetAnchorPoint({ 0.5f, 0.5f });
	oldPos = pos;
	enemy->SetScale(scale);
	type = stringToEnemyStyle(style);
	moveSpeedY = 0.2f;
	moveSpeedX = 0.2f;
	lifeTimer = lifeTime;
}

void Enemy::Update(const XMFLOAT3& playerPos) {
	const int32_t lifeTimeOver = 0;

	//XMVECTOR raticle2D = { enemy->GetMatWorld().r[3] }; //ワールド座標
	//XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
	//raticle2D = MatCalc::GetIns()->WDivided(raticle2D, matViewProjectionViewport); //スクリーン座標

	//DirectX::XMFLOAT2 spritePos = { raticle2D.m128_f32[0], raticle2D.m128_f32[1] };

	//test->SetPosition(spritePos);

	if (--lifeTimer <= lifeTimeOver) {
		//isDead = true;
		lifeTimer = 0;
	}

	if (enemy != nullptr) {
		if (pos.x == 0 && pos.y == 0 && pos.z == 0) {
			pos = oldPos;
		}
		EnemyAction(playerPos);
		enemy->Update();
	}
}

void Enemy::Draw() {
	enemy->Draw();
}

void Enemy::SpriteDraw() {
	//test->Draw();
}

void Enemy::OnCollision() {
	isDead = true;
}

Enemy::EnemyStyle Enemy::stringToEnemyStyle(const string& type) {
	Enemy::EnemyStyle style = EnemyStyle::STOP_PTAG;
	if (type == "STOP_PTAG") {
		style = EnemyStyle::STOP_PTAG;
	}
	else if (type == "STOP_STR") {
		style = EnemyStyle::STOP_STR;
	}
	else if (type == "UDMOVE_PTAG") {
		style = EnemyStyle::UDMOVE_PTAG;
	}
	else if (type == "UDMOVE_STR") {
		style = EnemyStyle::UDMOVE_STR;
	}
	else if (type == "LRMOVE_PTAG") {
		style = EnemyStyle::LRMOVE_PTAG;
	}
	else if (type == "LRMOVE_STR") {
		style = EnemyStyle::LRMOVE_STR;
	}

	return style;
}

void Enemy::EnemyAction(const XMFLOAT3& playerPos) {
	const float overPosY = 40.0f;
	const float overPosX = 60.0f;
	const int32_t shotIntervalTimeover = 0;
	Vector3 distance;
	float xRot, yRot;

	distance = Vector3(playerPos.x - pos.x, playerPos.y - pos.y, playerPos.z - pos.z);
	xRot = -(atan2(distance.y, sqrtf(pow(distance.z, 2)) + pow(distance.x, 2)) * 180.0f / 3.14f);
	yRot = (atan2(distance.x, distance.z) * 180.0f / 3.14f);

	if (type == EnemyStyle::UDMOVE_PTAG || type == EnemyStyle::UDMOVE_STR) {
		if (pos.y >= oldPos.y + overPosY || pos.y <= oldPos.y - overPosY) {
			moveSpeedY *= -1.0f;
		}
		pos.y += moveSpeedY;
	}
	if (type == EnemyStyle::LRMOVE_PTAG || type == EnemyStyle::LRMOVE_STR) {
		if (pos.x >= oldPos.x + overPosX || pos.x <= oldPos.x - overPosX) {
			moveSpeedX *= -1.0f;
		}
		pos.x += moveSpeedX;
	}

	if (--shotIntervalTimer <= shotIntervalTimeover /*&& IsShotRangeJudge(Vector3{playerPos.x, playerPos.y, playerPos.z}, pos, 150.0f, 2.0f)*/) {
		Shot();
		shotIntervalTimer = shotIntervalTime;
	}

	enemy->SetPosition(pos);
	enemy->SetRotation(Vector3(xRot, yRot, 0));
}

void Enemy::Shot() {
	const float bulletSpeed = 0.001f;
	XMVECTOR velocity = { 0, 0, 1 };

	velocity = MatCalc::GetIns()->VecDivided(velocity, enemy->GetMatWorld());

	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(enemy->GetMatWorld().r[3], velocity);

	gameScene->AddEnemyBullet(std::move(newBullet));
}

bool Enemy::IsShotRangeJudge(const Vector3& playerPos, const Vector3& enemyPos, float range, float playerScale) {
	Vector3 object1Pos = enemyPos;
	Vector3 object2Pos = playerPos;
	float objectPosTotal;
	float objectScaleTotal;

	objectPosTotal = (object2Pos.x - object1Pos.x) * (object2Pos.x - object1Pos.x) + (object2Pos.y - object1Pos.y) * (object2Pos.y - object1Pos.y) + (object2Pos.z - object1Pos.z) * (object2Pos.z - object1Pos.z);
	objectScaleTotal = (range + playerScale) * (range + playerScale);

	if (!(objectPosTotal <= objectScaleTotal)) return false;

	return true;
}