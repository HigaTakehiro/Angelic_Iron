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
		background,
		title,
		gameover,
		clear,
		playerUI,
		playerHP,
		playerBullet,
		reload
	};

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
};
