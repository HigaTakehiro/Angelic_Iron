#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "ImageManager.h"

class TitleScene : public BaseScene
{
public: //�����o�֐�
	/// <summary>
	/// �������֐�
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Sound* sound);
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

private: //�����o�ϐ�
	DirectXCommon* dxCommon;
	Sound* sound;

	Sprite* test;
};

