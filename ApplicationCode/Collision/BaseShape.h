#pragma once

//�`��
enum class ShapeType {
	Sphere,

	Num
};

class BaseShape
{
public: //�����o�֐�
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~BaseShape() {}

	/// <summary>
	/// �����蔻��`��擾
	/// </summary>
	/// <returns>�����蔻��`��</returns>
	virtual ShapeType GetShapeType() = 0;
};

