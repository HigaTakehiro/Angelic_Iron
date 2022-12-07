#pragma once
#include "BaseEnemy.h"

class RailScene;

class NormalEnemy : public BaseEnemy
{
public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="modelName">���f����</param>
	/// <param name="pos">���W</param>
	/// <param name="scale">�傫��</param>
	void Initialize(const ModelManager::ModelName modelName, const Vector3& pos, const Vector3& scale);
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="playerPos">�v���C���[�̍��W</param>
	/// <param name="delayTime">�X���[���o�p�x������</param>
	void Update(const Vector3& playerPos, const int delayTime);
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �摜�`�揈��
	/// </summary>
	void SpriteDraw();
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

private: //�����o�֐�
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// �U������
	/// </summary>
	void Attack();

private: //�ÓI�����o�ϐ�

private: //�����o�ϐ�

};

