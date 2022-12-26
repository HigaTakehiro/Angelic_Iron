#pragma once
#include "DirectXMath.h"

class Light
{
private: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	Light() = default;

	~Light() = default;

public: //�ÓI�����o�֐�

	/// <summary>
	/// ���C�g���W���Z�b�g
	/// </summary>
	/// <param name="light"></param>
	static void SetLightPos(XMFLOAT3 pos);

	/// <summary>
	/// ���C�g���W���擾
	/// </summary>
	/// <returns>���C�g���W</returns>
	static XMFLOAT3 GetLightPos() { return pos; }

private: //�����o�ϐ�
	//���C�g���W
	static XMFLOAT3 pos;
};