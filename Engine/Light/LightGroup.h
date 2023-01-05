#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "DirectXSetting.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class LightGroup
{
public: //�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

private: //�ÓI�����o�ϐ�
	static const int DirLightNum = 3;
	static const int PointLightNum = 3;
	static const int SpotLightNum = 3;
	static ID3D12Device* device;

public: //�T�u�N���X
	struct ConstBufferData {
		XMFLOAT3 ambientColor;
		float pad1;
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		PointLight::ConstBufferData pointLights[PointLightNum];
		SpotLight::ConstBufferData spotLights[SpotLightNum];
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
	static LightGroup* Create();

public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rootParameterIndex">�w�胋�[�g�p�����[�^</param>
	void Draw(UINT rootParameterIndex);

	/// <summary>
	/// �萔�o�b�t�@�փf�[�^�]��
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// �f�t�H���g���C�g�ݒ�
	/// </summary>
	void DefaultLightSetting();

	/// <summary>
	/// �A���r�G���g�F���Z�b�g
	/// </summary>
	/// <param name="ambientColor">�A���r�G���g�F</param>
	void SetAmbientColor(const XMFLOAT3& ambientColor);

	/// <summary>
	/// ���s�����L����
	/// </summary>
	/// <param name="index">���s�����ԍ�</param>
	/// <param name="isActive">���s�����L�����t���O</param>
	void SetDirLightActive(int index, bool isActive);

	/// <summary>
	/// ���s�������C�g�������Z�b�g
	/// </summary>
	/// <param name="index">���s�����ԍ�</param>
	/// <param name="lightDir">���C�g����</param>
	void SetDirLightDirection(int index, const XMFLOAT3& lightDir);

	/// <summary>
	/// ���s�������C�g�F���Z�b�g
	/// </summary>
	/// <param name="index">���s�����ԍ�</param>
	/// <param name="lightColor">���s�����F</param>
	void SetDirLightColor(int index, const XMFLOAT3& lightColor);

	/// <summary>
	/// �_�����L����
	/// </summary>
	/// <param name="index">�_�����ԍ�</param>
	/// <param name="active">�_�����L�����t���O</param>
	void SetPointLightActive(int index, bool isActive);

	/// <summary>
	/// �_�������W���Z�b�g
	/// </summary>
	/// <param name="index">�_�����ԍ�</param>
	/// <param name="lightPos">�_�������W</param>
	void SetPointLightPos(int index, const XMFLOAT3& lightPos);

	/// <summary>
	/// �_�����F���Z�b�g
	/// </summary>
	/// <param name="index">�_�����ԍ�</param>
	/// <param name="lightColor">�_�����F</param>
	void SetPointLightColor(int index, const XMFLOAT3& lightColor);

	/// <summary>
	/// ���������W��(�_�����p)���Z�b�g
	/// </summary>
	/// <param name="index">�_�����ԍ�</param>
	/// <param name="lightAtten">���������W��(�_�����p)</param>
	void SetPointLightAtten(int index, const XMFLOAT3& lightAtten);

	/// <summary>
	/// �X�|�b�g���C�g�L����
	/// </summary>
	/// <param name="index">�X�|�b�g���C�g�ԍ�</param>
	/// <param name="isActive">�X�|�b�g���C�g�L�����t���O</param>
	void SetSpotLightActive(int index, bool isActive);

	/// <summary>
	/// �X�|�b�g���C�g�������Z�b�g
	/// </summary>
	/// <param name="index">�X�|�b�g���C�g�ԍ�</param>
	/// <param name="lightDir">�X�|�b�g���C�g����</param>
	void SetSpotLightDirection(int index, const XMVECTOR& lightDir);

	/// <summary>
	/// �X�|�b�g���C�g���W���Z�b�g
	/// </summary>
	/// <param name="index">�X�|�b�g���C�g�ԍ�</param>
	/// <param name="lightPos">�X�|�b�g���C�g���W</param>
	void SetSpotLightPos(int index, const XMFLOAT3& lightPos);

	/// <summary>
	/// �X�|�b�g���C�g�F���Z�b�g
	/// </summary>
	/// <param name="index">�X�|�b�g���C�g�ԍ�</param>
	/// <param name="lightColor">�X�|�b�g���C�g�F</param>
	void SetSpotLightColor(int index, const XMFLOAT3& lightColor);

	/// <summary>
	/// �X�|�b�g���C�g���������W�����Z�b�g
	/// </summary>
	/// <param name="index">�X�|�b�g���C�g�ԍ�</param>
	/// <param name="lightAtten">�X�|�b�g���C�g���������W��</param>
	void SetSpotLightAtten(int index, const XMFLOAT3& lightAtten);

	/// <summary>
	/// �X�|�b�g���C�g�����p�x���Z�b�g
	/// </summary>
	/// <param name="index">�X�|�b�g���C�g�ԍ�</param>
	/// <param name="lightAngle">�X�|�b�g���C�g�����p�x</param>
	void SetSpotLightAngle(int index, const XMFLOAT2& lightAngle);

private: //�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	//����
	XMFLOAT3 ambientColor;
	//���s�����z��
	DirectionalLight dirLights[DirLightNum];
	//�_�����z��
	PointLight pointLights[PointLightNum];
	//�X�|�b�g���C�g�z��
	SpotLight spotLights[SpotLightNum];
	//�_�[�e�B�t���O
	bool isDirty;
};

