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
	void Draw(bool isEnemyDead[]);

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	/// <summary>
	/// �U������
	/// </summary>
	void Shot();

	/// <summary>
	/// �G�l�~�[���擾
	/// </summary>
	/// <param name="i">�G�l�~�[�z��̔ԍ�</param>
	/// <returns>�G�l�~�[�I�u�W�F�N�g</returns>
	Object3d* GetEnemy(int enemyNo) { return enemy[enemyNo]; }

	/// <summary>
	/// �G�l�~�[�̒e���擾
	/// </summary>
	/// <param name="enemyNo">�G�l�~�[�z��̔ԍ�</param>
	/// <returns>�w�肵���G�l�~�[�̒e</returns>
	Object3d* GetEnemyShot(int enemyNo) { return shot[enemyNo]; }

	/// <summary>
	/// ���ˉ\�͈͂ɂ��邩����
	/// </summary>
	/// <param name="player">�v���C���[�I�u�W�F�N�g</param>
	/// <returns>���ˉ\���ǂ���</returns>
	bool ShotRangeJudge(Object3d* player);

private: //�����o�֐�

private: //�����o�ϐ�

	//�G�l�~�[�̈ʒu
	std::vector<Vector3> enemyPos;

	//�G�l�~�[�̌���
	Vector3 enemyRot;

	//�G�l�~�[�̑傫��
	Vector3 enemyScale = { 5, 5, 5 };

	//�e�̈ʒu
	Vector3 shotPos[3];

	//�e�̑傫��
	Vector3 shotScale[3];

	//���f��
	Model* enemyModel;
	Model* shotModel;

	//3d�I�u�W�F�N�g
	Object3d* enemy[3];
	Object3d* shot[3];

	//�Q�[���Ɏg�p����ϐ�
	bool isShotRange[3];
};

