#pragma once
#include "Sprite.h"

class ImageManager final
{
private:
	ImageManager() = default;
	~ImageManager() = default;
	ImageManager(const ImageManager & obj) = delete;
	ImageManager& operator=(const ImageManager & obj) = delete;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static ImageManager* GetIns();

public: //�摜��
	enum ImageName {
		aim = 1,
		title,
		score,
		scoreNumbers,
		playerUI,
		playerHP,
		playerBullet,
		reload,
		enemyDead,
		StartButton,
		Stage1,
		Stage2,
		ManualButton,
		Manual,
		Manual_2,
		Close,
		Pause,
		TitleBack,
		Back,
		Restart,
		Boost,
		Allow,
		FaceWindow,
		TextWindow,
		OPE_NORMAL,
		OPE_SURPRISE,
		OPE_SMILE,
		SceneChangeBar,
		Bomb,
		HPBar,
		SecondTimer,
		How_to_Bomb,
		How_to_Shot,
		How_to_Up,
		How_to_Down,
		How_to_Left,
		How_to_Right
	};

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
};

