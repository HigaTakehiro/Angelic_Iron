#pragma once
#include "BaseShape.h"
#include "Vector3.h"

class BaseCollision {
public: //�����o�֐�
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~BaseCollision() {};

	/// <summary>
	/// �������Ă��邩�`�F�b�N
	/// </summary>
	/// <param name="shape1">���肵�����I�u�W�F�N�g1</param>
	/// <param name="shape2">���肵�����I�u�W�F�N�g2</param>
	/// <returns>�������Ă���</returns>
	virtual bool CollisionCheck(const BaseShape& shape1, const BaseShape& shape2) = 0;
};