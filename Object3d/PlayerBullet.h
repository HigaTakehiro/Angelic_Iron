#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"

class PlayerBullet
{
public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

private: //�����o�ϐ�
	Model* bulletModel;
	Object3d* bullet;
};

