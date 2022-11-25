#include "TitleScene.h"

void TitleScene::Initialize(DirectXCommon* dxCommon, Sound* sound)
{
	this->dxCommon = dxCommon;
	this->sound = sound;
	//test->Create(ImageManager::aim, { 640, 360 });
}

void TitleScene::Update()
{

}

void TitleScene::Draw()
{
	//Sprite::PreDraw(dxCommon->GetCmdList());
	//test->Draw();
	//Sprite::PostDraw();

}

void TitleScene::Finalize()
{
	delete dxCommon;
	dxCommon = nullptr;
	delete sound;
	sound = nullptr;
}
