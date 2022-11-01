#include "ImageManager.h"

ImageManager* ImageManager::GetIns()
{
	static ImageManager instance;
	return &instance;
}

void ImageManager::Initialize() {
	Sprite::LoadTexture(aim, L"Engine/Resources/Images/Aim.png");
	Sprite::LoadTexture(background, L"Engine/Resources/Images/background.png");
	Sprite::LoadTexture(title, L"Engine/Resources/Images/AlphaTitle.png");
	Sprite::LoadTexture(gameover, L"Engine/Resources/Images/Gameover.png");
	Sprite::LoadTexture(clear, L"Engine/Resources/Images/Clear.png");
	Sprite::LoadTexture(playerUI, L"Engine/Resources/Images/PlayerUI.png");
	Sprite::LoadTexture(playerHP, L"Engine/Resources/Images/PlayerHP.png");
	Sprite::LoadTexture(playerBullet, L"Engine/Resources/Images/PlayerBullet.png");
	Sprite::LoadTexture(reload, L"Engine/Resources/Images/Reload.png");
}