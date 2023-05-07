#include "Particle2d.h"

Particle2d::~Particle2d() {
	safe_delete(particle_);
}

void Particle2d::Initialize(XMFLOAT2 pos, XMFLOAT2 scale, int32_t time, ImageManager::ImageName imagename, XMFLOAT2 anchorPoint, int32_t imageNo, XMFLOAT2 texUpperLeft, XMFLOAT2 texLowerRight) {
	pos_ = pos;
	particle_ = Sprite::Create(imagename, pos);
	particle_->SetSize(scale);
	particle_->SetAnchorPoint(anchorPoint);
	deleteTime_ = time;
	texUpperLeft_ = { 0, 0 };
	texLowerRight_ = { 0, 0 };
	drawTime_ = 0;
	if (imageNo != 0) {
		imageNo_ = imageNo;
		texUpperLeft_ = texUpperLeft;
		texLowerRight_ = texLowerRight;
		particle_->SetTextureRect(texUpperLeft, texLowerRight);
		drawTime_ = deleteTime_ / imageNo;
	}

	nowTimer_ = 0;
	nowImage_ = 0;
	isDelete_ = false;
}

void Particle2d::Update() {
	nowTimer_++;
	if (nowTimer_ > deleteTime_) {
		isDelete_ = true;
	}
	if (nowTimer_ >= drawTime_ * (nowImage_ + 1) && imageNo_ != 0) {
		nowImage_++;
		texUpperLeft_.x = texLowerRight_.x;
		texUpperLeft_.x = texUpperLeft_.x * (nowImage_);
		particle_->SetTextureRect(texUpperLeft_, texLowerRight_);
		particle_->SetPosition(pos_);
	}
}

void Particle2d::Draw() {
	if (particle_ != nullptr) {
		particle_->Draw();
	}
}