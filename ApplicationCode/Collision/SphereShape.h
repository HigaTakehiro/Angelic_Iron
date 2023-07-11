#pragma once
#include "BaseShape.h"
#include "Vector3.h"

class SphereShape : public BaseShape
{
public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="radius">���a</param>
	SphereShape(const Vector3& pos, float radius);

	/// <summary>
	/// �`��^�C�v�擾
	/// </summary>
	/// <returns>���^�C�v</returns>
	ShapeType GetShapeType() { return ShapeType::Sphere; }

	/// <summary>
	/// ���W�擾
	/// </summary>
	/// <returns>���W</returns>
	Vector3 GetPos() const { return pos_; }

	/// <summary>
	/// ���a�擾
	/// </summary>
	/// <returns>���a</returns>
	float GetRadius() const { return radius_; }

private: //�����o�ϐ�
	//���W
	Vector3 pos_;
	//���a
	float radius_;
};

