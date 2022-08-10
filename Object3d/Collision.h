#pragma once
#include "Object3d.h"
#include "Vector3.h"
#include "DirectXMath.h"

class Collision final
{
private:
	Collision() = default;
	~Collision() = default;
	Collision(const Collision& obj) = delete;
	Collision& operator=(const Collision& obj) = delete;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�擾�p�֐�
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static Collision* GetIns();

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���Ƌ��̓����蔻��
	/// </summary>
	/// <param name="object1">���肵�����I�u�W�F�N�g1</param>
	/// <param name="object2">���肵�����I�u�W�F�N�g2</param>
	/// <returns>��������</returns>
	bool SphereCollision(Object3d* object1, Object3d* object2);

private: //�����o�ϐ�
	Vector3 object1Pos = { 0, 0, 0 };
	Vector3 object2Pos = { 0, 0, 0 };

	Vector3 object1Scale = { 0, 0, 0 };
	Vector3 object2Scale = { 0, 0, 0 };

	float objectPosTotal = 0;
	float objectScaleTotal = 0;
};
