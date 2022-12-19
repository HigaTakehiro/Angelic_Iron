#pragma once
#include "Object3d.h"
#include "Model.h"

class Shapes
{
public:

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X���擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static Shapes* GetIns();

	/// <summary>
	/// ���ʂ̎O�p�`�𐶐�
	/// </summary>
	/// <param name="vertices_1">���_1</param>
	/// <param name="vertices_2">���_2</param>
	/// <param name="vertices_3">���_3</param>
	/// <returns>���ʂ̎O�p�`</returns>
	static Object3d* CreateTriangle(XMFLOAT3 vertices_1, XMFLOAT3 vertices_2, XMFLOAT3 vertices_3);

	/// <summary>
	/// ���ʂ̎l�p�`�𐶐�
	/// </summary>
	/// <param name="upperLeft">������W</param>
	/// <param name="lowerBottom">�E�����W</param>
	/// <returns>���ʂ̎l�p�`</returns>
	static Object3d* CreateSquare(XMFLOAT2 upperLeft, XMFLOAT2 lowerBottom);

public: //�����o�֐�
};

