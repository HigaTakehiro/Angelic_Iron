#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class MatCalc final
{
private:
	/// <summary>
    /// �R���X�g���N�^
    /// </summary>
	MatCalc() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MatCalc() = default;

	/// <summary>
	/// �R�s�[�R���X�g���N�^���֎~
	/// </summary>
	MatCalc(const MatCalc & obj) = delete;

	/// <summary>
	/// ������Z�q���֎~
	/// </summary>
	MatCalc& operator=(const MatCalc & obj) = delete;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X���擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static MatCalc* GetIns();

public: //�����o�֐�

	/// <summary>
	/// ���W�ɍs����|���čŌ��w���Z����
	/// </summary>
	/// <param name="vec">���W</param>
	/// <param name="mat">�s��</param>
	/// <returns>�v�Z����</returns>
	XMVECTOR WDivided(const XMVECTOR& pos, const XMMATRIX& mat);

	/// <summary>
	/// ���W��w���Z����
	/// </summary>
	/// <param name="pos">���W</param>
	/// <returns>�v�Z����</returns>
	XMVECTOR WDivision(const XMVECTOR& pos);

	/// <summary>
	/// �x�N�g���ƍs��̊|���Z
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	/// <param name="mat">�s��</param>
	/// <returns>�v�Z����</returns>
	XMVECTOR VecDivided(const XMVECTOR& vec, const XMMATRIX& mat);

	/// <summary>
	/// ���W�ƍs��̊|���Z
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="mat">�s��</param>
	/// <param name="isWSlide">z�̒l��w�ɂ��炷��</param>
	/// <returns>�v�Z����</returns>
	XMVECTOR PosDivided(const XMVECTOR& pos, const XMMATRIX& mat, const bool isWSlide = false);

	/// <summary>
	/// �s�񂩂�t�s������߂�
	/// </summary>
	/// <param name="mat">�s��</param>
	/// <returns>�t�s��</returns>
	XMMATRIX InverseMatrix(const XMMATRIX& mat);

};

