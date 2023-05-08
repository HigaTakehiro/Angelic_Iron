#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "DirectXSetting.h"

class DirectionalLight
{
private: // �G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: //�T�u�N���X
	struct ConstBufferData {
		XMVECTOR lightVec_; //���C�g�ւ̕�����\���x�N�g��
		XMFLOAT3 lightColor_; //���C�g�̐F
		unsigned int isActive_;
	};

public: //�����o�֐�

	/// <summary>
	/// ���C�g�������Z�b�g
	/// </summary>
	/// <param name="lightDir">���C�g����</param>
	inline void SetLightDir(const XMVECTOR& lightDir) { lightDir_ = DirectX::XMVector3Normalize(lightDir); }

	/// <summary>
	/// ���C�g�F���Z�b�g
	/// </summary>
	/// <param name="lightColor">���C�g�F</param>
	inline void SetLightColor(const XMFLOAT3& lightColor) { lightColor_ = lightColor; }

	/// <summary>
	/// ���s������L����
	/// </summary>
	/// <param name="isActive">�L�����t���O</param>
	inline void SetIsActive(bool isActive) { isActive_ = isActive; }

	/// <summary>
	/// �L�����t���O�擾
	/// </summary>
	inline bool GetIsActive() { return isActive_; }

	/// <summary>
	/// ���C�g�������擾
	/// </summary>
	/// <returns>���C�g����</returns>
	inline const XMVECTOR& GetLightDir() { return lightDir_; }

	/// <summary>
	/// ���C�g�F���擾
	/// </summary>
	/// <returns>���C�g�F</returns>
	inline const XMFLOAT3& GetLightColor() { return lightColor_; }

private: //�����o�ϐ�
	//���C�g��������
	XMVECTOR lightDir_ = { 1, 0, 0, 0 };
	//���C�g�F
	XMFLOAT3 lightColor_ = { 1, 1, 1 };
	//�L�����t���O
	bool isActive_ = false;
};