#include "ScoreItem.h"
#include "SafeDelete.h"
#include "ModelManager.h"
#include "DirectXSetting.h"

const float ScoreItem::moveTime = 60.0f;

ScoreItem::~ScoreItem()
{
	safe_delete(scoreItem_);
	safe_delete(particle_);
}

void ScoreItem::Initialize(const Vector3& pos, Player* player, Camera* camera)
{
	const Vector3 initRot = { 0.0f, 0.0f, 0.0f };
	const Vector3 initScale = { 2.0f, 2.0f, 2.0f };
	pos_ = pos;
	rot_ = initRot;
	scale_ = initScale;
	player_ = player;
	particle_ = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);
	scoreItem_ = Object3d::Create(ModelManager::GetIns()->GetModel("scoreItem"));
	scoreItem_->SetPosition(pos_);
	scoreItem_->SetRotation(rot_);
	scoreItem_->SetScale(scale_);
	scoreItem_->SetObjType((int32_t)Object3d::OBJType::ScoreItem);
	scoreItem_->SetColType(Object3d::CollisionType::Sphere);
}

void ScoreItem::Update()
{
	DirectX::XMVECTOR vel = { 0, 0, 0 };
	XMVector3TransformNormal(vel, Camera::GetMatWorld());
	Vector3 velocity = vel;
	Vector3 acc = { 0, 0, 0 };
	float initScale = 10.0f;
	float endScale = 1.0f;
	Vector3 particleColor = { 0.6f, 0.3f, 0.0f };
	particle_->Add(10, pos_, velocity, acc, initScale, endScale, particleColor, particleColor);
	if (rot_.y < 360.0f) {
		rot_.y += 3.0f;
	}
	else {
		rot_.y = 0;
	}
	if (++standByTimer_ >= standByTime) {
		float t = ++moveTimer_ / moveTime;
		pos_ = easeIn(pos_, player_->GetPlayerObject()->GetMatWorld().r[3], t);
	}

	scoreItem_->SetPosition(pos_);
	scoreItem_->SetRotation(rot_);

	scoreItem_->Update();
	particle_->Update();
}

void ScoreItem::Draw()
{
	scoreItem_->Draw();
	particle_->Draw(DirectXSetting::GetIns()->GetCmdList());

}

void ScoreItem::OnCollision()
{
	isDead_ = true;
}
