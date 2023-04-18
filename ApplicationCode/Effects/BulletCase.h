#pragma once
#include "Model.h"
#include "ModelManager.h"
#include "Object3d.h"
#include "SafeDelete.h"
#include "Vector3.h"

class BulletCase
{
public: //�R���X�g���N�^&�f�X�g���N�^
	BulletCase() = default;
	~BulletCase();

public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pos">�������W</param>
	/// <param name="velocity">���x�x�N�g��</param>
	/// <param name="rot">����</param>
	void Initialize(const Vector3& pos, const Vector3& velocity, const Vector3& rot);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// ��䰂̏�Ԃ��擾
	/// </summary>
	/// <returns>�e�̏��</returns>
	bool IsDead() const { return isDead; }

private: //�ÓI�����o�ϐ�
	static const int32_t lifeTime = 60 * 2;

private: //�����o�ϐ�
	Object3d* bulletCase;
	Vector3 pos;
	bool isDead;
	int32_t lifeTimer = lifeTime;
	Vector3 velocity;
};
