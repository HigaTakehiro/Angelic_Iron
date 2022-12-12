#include "ImageManager.h"

ImageManager* ImageManager::GetIns()
{
	static ImageManager instance;
	return &instance;
}

void ImageManager::Initialize() {
	Sprite::LoadTexture(aim, L"Engine/Resources/Images/Aim.png");
	Sprite::LoadTexture(background, L"Engine/Resources/Images/background.png");
	Sprite::LoadTexture(title, L"Engine/Resources/Images/TitleLogo.png");
	Sprite::LoadTexture(score, L"Engine/Resources/Images/Score.png");
	Sprite::LoadTexture(scoreNumbers, L"Engine/Resources/Images/ScoreNumbers.png");
	Sprite::LoadTexture(playerUI, L"Engine/Resources/Images/PlayerUI.png");
	Sprite::LoadTexture(playerHP, L"Engine/Resources/Images/PlayerHP.png");
	Sprite::LoadTexture(playerBullet, L"Engine/Resources/Images/PlayerBullet.png");
	Sprite::LoadTexture(reload, L"Engine/Resources/Images/Reload.png");
	Sprite::LoadTexture(enemyDead, L"Engine/Resources/Images/enemyDead.png");
	Sprite::LoadTexture(StartButton, L"Engine/Resources/Images/StartButton.png");
	Sprite::LoadTexture(Stage1, L"Engine/Resources/Images/Stage1.png");
	Sprite::LoadTexture(Stage2, L"Engine/Resources/Images/Stage2.png");
	Sprite::LoadTexture(ManualButton, L"Engine/Resources/Images/ManualButton.png");
	Sprite::LoadTexture(Manual, L"Engine/Resources/Images/Manual.png");
	Sprite::LoadTexture(Close, L"Engine/Resources/Images/Close.png");
	Sprite::LoadTexture(Pause, L"Engine/Resources/Images/Pause.png");
	Sprite::LoadTexture(TitleBack, L"Engine/Resources/Images/TitleBack.png");
	Sprite::LoadTexture(Back, L"Engine/Resources/Images/Back.png");
	Sprite::LoadTexture(Restart, L"Engine/Resources/Images/Restart.png");
	Sprite::LoadTexture(Boost, L"Engine/Resources/Images/Boost.png");
}