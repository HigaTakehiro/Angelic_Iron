#pragma once
#include "BaseScene.h"

class ResultScene : public BaseScene
{
public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dxCommon"></param>
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
};

