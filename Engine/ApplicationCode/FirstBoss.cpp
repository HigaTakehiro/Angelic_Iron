#include "FirstBoss.h"

const int32_t FirstBoss::actionCoolTime = 60;

void FirstBoss::Initialize(ModelManager::ModelName model, const Vector3& pos) {
	boss = Object3d::Create(ModelManager::GetIns()->GetModel(model));
	this->pos = pos;
	scale = { 10, 10, 10 };
	rot = { 0, 0, 0 };
	hp = 100;
	attackPower = 1;

	boss->SetPosition(this->pos);
	boss->SetRotation(rot);
	boss->SetScale(scale);
}

void FirstBoss::Update(const Vector3& playerPos, const int delayTime)
{
	this->playerPos = playerPos;

	boss->Update();
}

void FirstBoss::Draw()
{
	boss->Draw();
}

void FirstBoss::Finalize()
{
	safe_delete(boss);
}

void FirstBoss::Action()
{
}
