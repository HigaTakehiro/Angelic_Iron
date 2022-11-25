#include "ResultScene.h"

void ResultScene::Initialize(DirectXCommon* dxCommon, Sound* sound)
{
	this->dxCommon = dxCommon;
	this->sound = sound;
}

void ResultScene::Update()
{

}

void ResultScene::Draw()
{

}

void ResultScene::Finalize()
{
	delete dxCommon;
	dxCommon = nullptr;
	delete sound;
	sound = nullptr;
}
