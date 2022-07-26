#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"

class Enemy
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

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

private: //�����o�֐�

private: //�����o�ϐ�

	//�G�l�~�[�̈ʒu
	Vector3 enemyPos[3];

	//�G�l�~�[�̌���
	Vector3 enemyRot;

	//�G�l�~�[�̑傫��
	Vector3 enemyScale = { 5, 5, 5 };

	//�G�l�~�[�̃��f��
	Model* enemyModel;

	//�G�l�~�[�I�u�W�F�N�g
	Object3d* enemy[3];
};

