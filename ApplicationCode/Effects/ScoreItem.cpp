#include "ScoreItem.h"
#include "SafeDelete.h"
#include "ModelManager.h"
#include "DirectXSetting.h"

ScoreItem::~ScoreItem()
{
	safe_delete(scoreItem_);
	safe_delete(particle_);
}

void ScoreItem::Initialize(const Vector3& pos, Player* player, Camera* camera)
{
	const Vector3 initRot = { 0.0f, 0.0f, 0.0f };
	const Vector3 initScale = { 1.0f, 1.0f, 1.0f };
	pos_ = pos;
	rot_ = initRot;
	scale_ = initScale;
	player_ = player;
	particle_ = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);
	//scoreItem_ = Object3d::Create(ModelManager::GetIns()->GetModel("scoreItem"));
}

void ScoreItem::Update()
{
	Vector3 vel = { 0, 0, 0 };
	Vector3 acc = { 0, 0, 0 };
	float initScale = 3.0f;
	float endScale = 1.0f;
	Vector3 particleColor = { 0.6f, 0.3f, 0.0f };
	particle_->Add(2, pos_, vel, acc, initScale, endScale, particleColor, particleColor);
	if (++standByTimer_ < standByTime) {
		if (rot_.y < 360.0f) {
			rot_.y++;
		}
		else {
			rot_.y = 0;
		}
	}
	else {
		float t = (float)++moveTimer_ / (float)moveTime;
		pos_ = easeIn(pos_, player_->GetPlayerObject()->GetMatWorld().r[3], t);
	}
}

void ScoreItem::Draw()
{
	particle_->Draw(DirectXSetting::GetIns()->GetCmdList());
	scoreItem_->Draw();
}

void ScoreItem::OnCollision()
{
	isDead_ = true;
}
