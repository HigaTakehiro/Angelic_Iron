#include "ImageManager.h"

ImageManager* ImageManager::GetIns()
{
	static ImageManager instance;
	return &instance;
}

void ImageManager::Initialize() {
	Sprite::LoadTexture((UINT)ImageName::aim, L"Engine/Resources/Images/Aim.png");
	Sprite::LoadTexture((UINT)ImageName::title, L"Engine/Resources/Images/TitleLogo.png");
	Sprite::LoadTexture((UINT)ImageName::score, L"Engine/Resources/Images/Score.png");
	Sprite::LoadTexture((UINT)ImageName::scoreNumbers, L"Engine/Resources/Images/ScoreNumbers.png");
	Sprite::LoadTexture((UINT)ImageName::playerUI, L"Engine/Resources/Images/PlayerUI.png");
	Sprite::LoadTexture((UINT)ImageName::playerHP, L"Engine/Resources/Images/PlayerHP.png");
	Sprite::LoadTexture((UINT)ImageName::playerBullet, L"Engine/Resources/Images/PlayerBullet.png");
	Sprite::LoadTexture((UINT)ImageName::reload, L"Engine/Resources/Images/Reload.png");
	Sprite::LoadTexture((UINT)ImageName::enemyDead, L"Engine/Resources/Images/enemyDead.png");
	Sprite::LoadTexture((UINT)ImageName::StartButton, L"Engine/Resources/Images/StartButton.png");
	Sprite::LoadTexture((UINT)ImageName::Stage1, L"Engine/Resources/Images/Stage1.png");
	Sprite::LoadTexture((UINT)ImageName::Stage2, L"Engine/Resources/Images/Stage2.png");
	Sprite::LoadTexture((UINT)ImageName::ManualButton, L"Engine/Resources/Images/ManualButton.png");
	Sprite::LoadTexture((UINT)ImageName::Manual, L"Engine/Resources/Images/Manual.png");
	Sprite::LoadTexture((UINT)ImageName::Manual_2, L"Engine/Resources/Images/Manual_2.png");
	Sprite::LoadTexture((UINT)ImageName::Close, L"Engine/Resources/Images/Close.png");
	Sprite::LoadTexture((UINT)ImageName::Pause, L"Engine/Resources/Images/Pause.png");
	Sprite::LoadTexture((UINT)ImageName::TitleBack, L"Engine/Resources/Images/TitleBack.png");
	Sprite::LoadTexture((UINT)ImageName::Back, L"Engine/Resources/Images/Back.png");
	Sprite::LoadTexture((UINT)ImageName::Restart, L"Engine/Resources/Images/Restart.png");
	Sprite::LoadTexture((UINT)ImageName::Boost, L"Engine/Resources/Images/Boost.png");
	Sprite::LoadTexture((UINT)ImageName::Allow, L"Engine/Resources/Images/Allow.png");
	Sprite::LoadTexture((UINT)ImageName::TextWindow, L"Engine/Resources/Images/Text_Window.png");
	Sprite::LoadTexture((UINT)ImageName::FaceWindow, L"Engine/Resources/Images/Face_Window.png");
	Sprite::LoadTexture((UINT)ImageName::OPE_NORMAL, L"Engine/Resources/Images/Operator_Normal.png");
	Sprite::LoadTexture((UINT)ImageName::OPE_SURPRISE, L"Engine/Resources/Images/Operator_Surprise.png");
	Sprite::LoadTexture((UINT)ImageName::OPE_SMILE, L"Engine/Resources/Images/Operator_Smile.png");
	Sprite::LoadTexture((UINT)ImageName::SceneChangeBar, L"Engine/Resources/Images/SceneChangeBar.png");
	Sprite::LoadTexture((UINT)ImageName::Bomb, L"Engine/Resources/Images/Bomb.png");
	Sprite::LoadTexture((UINT)ImageName::HPBar, L"Engine/Resources/Images/HPBar.png");
	Sprite::LoadTexture((UINT)ImageName::SecondTimer, L"Engine/Resources/Images/Bomb_timer.png");
	Sprite::LoadTexture((UINT)ImageName::How_to_Bomb, L"Engine/Resources/Images/How_to_bomb.png");
	Sprite::LoadTexture((UINT)ImageName::How_to_Shot, L"Engine/Resources/Images/How_to_shot.png");
	Sprite::LoadTexture((UINT)ImageName::How_to_Up, L"Engine/Resources/Images/How_to_up.png");
	Sprite::LoadTexture((UINT)ImageName::How_to_Down, L"Engine/Resources/Images/How_to_down.png");
	Sprite::LoadTexture((UINT)ImageName::How_to_Left, L"Engine/Resources/Images/How_to_left.png");
	Sprite::LoadTexture((UINT)ImageName::How_to_Right, L"Engine/Resources/Images/How_to_right.png");
}