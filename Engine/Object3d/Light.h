#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "DirectXSetting.h"

class Light
{
private: // �G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	Light() = default;

	~Light() = default;

public: //�T�u�N���X
	struct ConstBufferData {
		XMVECTOR lightVec; //���C�g�ւ̕�����\���x�N�g��
		XMFLOAT3 lightColor; //���C�g�̐F
	};

public: //�ÓI�����o�֐�

	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static Light* Create();

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

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �萔�o�b�t�@�փf�[�^�]��
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// ���C�g�������Z�b�g
	/// </summary>
	/// <param name="lightDir">���C�g����</param>
	void SetLightDir(const XMVECTOR& lightDir);

	/// <summary>
	/// ���C�g�F���Z�b�g
	/// </summary>
	/// <param name="lightColor">���C�g�F</param>
	void SetLightColor(const XMFLOAT3& lightColor);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rootParameter">�w�胋�[�g�p�����[�^</param>
	void Draw(UINT rootParameter);

private: //�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device;
	//���C�g���W
	static XMFLOAT3 pos;

private: //�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	//���C�g��������
	XMVECTOR lightDir = { 1, 0, 0, 0 };
	//���C�g�F
	XMFLOAT3 lightColor = { 1, 1, 1 };
	//�_�[�e�B�t���O
	bool isDirty = false;
};