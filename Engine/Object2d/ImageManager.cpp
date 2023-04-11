#include "ImageManager.h"

ImageManager* ImageManager::GetIns()
{
	static ImageManager instance;
	return &instance;
}

void ImageManager::Initialize() {
	Sprite::LoadTexture(aim, L"Engine/Resources/Images/Aim.png");
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
	Sprite::LoadTexture(Manual_2, L"Engine/Resources/Images/Manual_2.png");
	Sprite::LoadTexture(Close, L"Engine/Resources/Images/Close.png");
	Sprite::LoadTexture(Pause, L"Engine/Resources/Images/Pause.png");
	Sprite::LoadTexture(TitleBack, L"Engine/Resources/Images/TitleBack.png");
	Sprite::LoadTexture(Back, L"Engine/Resources/Images/Back.png");
	Sprite::LoadTexture(Restart, L"Engine/Resources/Images/Restart.png");
	Sprite::LoadTexture(Boost, L"Engine/Resources/Images/Boost.png");
	Sprite::LoadTexture(Allow, L"Engine/Resources/Images/Allow.png");
	Sprite::LoadTexture(TextWindow, L"Engine/Resources/Images/Text_Window.png");
	Sprite::LoadTexture(FaceWindow, L"Engine/Resources/Images/Face_Window.png");
	Sprite::LoadTexture(OPE_NORMAL, L"Engine/Resources/Images/Operator_Normal.png");
	Sprite::LoadTexture(OPE_SURPRISE, L"Engine/Resources/Images/Operator_Surprise.png");
	Sprite::LoadTexture(OPE_SMILE, L"Engine/Resources/Images/Operator_Smile.png");
	Sprite::LoadTexture(SceneChangeBar, L"Engine/Resources/Images/SceneChangeBar.png");
	Sprite::LoadTexture(Bomb, L"Engine/Resources/Images/Bomb.png");
	Sprite::LoadTexture(HPBar, L"Engine/Resources/Images/HPBar.png");
	Sprite::LoadTexture(SecondTimer, L"Engine/Resources/Images/Bomb_timer.png");
	Sprite::LoadTexture(How_to_Bomb, L"Engine/Resources/Images/How_to_bomb.png");
	Sprite::LoadTexture(How_to_Shot, L"Engine/Resources/Images/How_to_shot.png");
	Sprite::LoadTexture(How_to_Up, L"Engine/Resources/Images/How_to_up.png");
	Sprite::LoadTexture(How_to_Down, L"Engine/Resources/Images/How_to_down.png");
	Sprite::LoadTexture(How_to_Left, L"Engine/Resources/Images/How_to_left.png");
	Sprite::LoadTexture(How_to_Right, L"Engine/Resources/Images/How_to_right.png");
}