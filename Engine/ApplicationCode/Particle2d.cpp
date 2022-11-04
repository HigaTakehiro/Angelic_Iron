#include "Particle2d.h"

Particle2d::~Particle2d() {
	safe_delete(particle);
}

void Particle2d::Initialize(XMFLOAT2 pos, XMFLOAT2 scale, int32_t time, ImageManager::ImageName imagename, XMFLOAT2 anchorPoint, int imageNo, XMFLOAT2 texUpperLeft, XMFLOAT2 texLowerRight) {
	this->pos = pos;
	particle = Sprite::Create(imagename, pos);
	particle->SetSize(scale);
	particle->SetAnchorPoint(anchorPoint);
	deleteTime = time;
	this->texUpperLeft = { 0, 0 };
	this->texLowerRight = { 0, 0 };
	drawTime = 0;
	if (imageNo != 0) {
		this->imageNo = imageNo;
		this->texUpperLeft = texUpperLeft;
		this->texLowerRight = texLowerRight;
		particle->SetTextureRect(texUpperLeft, texLowerRight);
		drawTime = deleteTime / imageNo;
	}

	nowTime = 0;
	nowImage = 0;
	isDelete = false;
}

void Particle2d::Update() {
	nowTime++;
	if (nowTime > deleteTime) {
		isDelete = true;
	}
	if (nowTime >= drawTime * (nowImage + 1) && imageNo != 0) {
		nowImage++;
		texUpperLeft.x = texUpperLeft.x * (nowImage + 1);
		texLowerRight.x = texLowerRight.x * (nowImage + 1);
		particle->SetTextureRect(texUpperLeft, texLowerRight);
		pos.x = texUpperLeft.x;
		particle->SetPosition(pos);
	}
}

void Particle2d::Draw() {
	if (particle != nullptr) {
		particle->Draw();
	}
}