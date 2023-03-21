#pragma once
#include <DirectXMath.h>

class ShadowMap {
private: //�G�C���A�X
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//�萔�o�b�t�@�f�[�^
	struct ConstBufferData {
		XMVECTOR lightDir;
		bool isActive;
	};

public: //�����o�֐�
	/// <summary>
	/// ���C�g�������Z�b�g
	/// </summary>
	/// <param name="lightDir"></param>
	void SetDir(XMVECTOR lightDir) { this->lightDir = lightDir; }
	/// <summary>
	/// �V���h�E�}�b�v��L����
	/// </summary>
	/// <param name="isActive"></param>
	void SetIsActive(bool isActive) { this->isActive = isActive; }

	/// <summary>
	/// ���C�g�������擾
	/// </summary>
	XMVECTOR GetDir() { return lightDir; }
	/// <summary>
	/// �L�����t���O���擾
	/// </summary>
	/// <returns></returns>
	bool GetIsActive() { return isActive; }

private: //�����o�ϐ�
	//���C�g����
	XMVECTOR lightDir = { 1, 0, 0, 0 };
	//�L�����t���O
	bool isActive = false;
};