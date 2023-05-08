#pragma once
#include <DirectXMath.h>

class PointLight
{
private: //�G�C���A�X
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: //�T�u�N���X
	struct ConstBufferData {
		XMFLOAT3 lightPos_;
		float pad1_;
		XMFLOAT3 lightColor_;
		float pad2_;
		XMFLOAT3 lightAtten_;
		unsigned int isActive_;
	};

public: //�����o�֐�
	/// <summary>
	/// ���C�g���W���Z�b�g
	/// </summary>
	/// <param name="lightPos">���C�g���W</param>
	inline void SetLightPos(const XMFLOAT3& lightPos) { lightPos_ = lightPos; }

	/// <summary>
	/// ���C�g���W���擾
	/// </summary>
	/// <returns>���C�g���W</returns>
	inline const XMFLOAT3& GetLightPos() { return lightPos_; }

	/// <summary>
	/// ���C�g�F���Z�b�g
	/// </summary>
	/// <param name="lightColor">���C�g�F</param>
	inline void SetLightColor(const XMFLOAT3& lightColor) { lightColor_ = lightColor; }

	/// <summary>
	/// ���C�g�F���擾
	/// </summary>
	/// <returns>���C�g�F</returns>
	inline const XMFLOAT3& GetLightColor() { return lightColor_; }

	/// <summary>
	/// ���C�g���������W�����Z�b�g
	/// </summary>
	/// <param name="lightAtten">���C�g���������W��</param>
	inline void SetLightAtten(const XMFLOAT3& lightAtten) { lightAtten_ = lightAtten; }

	/// <summary>
	/// ���C�g���������W�����擾
	/// </summary>
	/// <returns>���C�g���������W��</returns>
	inline const XMFLOAT3& GetLightAtten() { return lightAtten_; }

	/// <summary>
	/// �_�����L����
	/// </summary>
	/// <param name="isActive">�L�����t���O</param>
	inline void SetActive(bool isActive) { isActive_ = isActive; }

	/// <summary>
	/// �_�����L�����t���O���擾
	/// </summary>
	/// <returns>�L�����t���O</returns>
	inline bool GetIsActive() { return isActive_; }

private: //�����o�ϐ�
	//���C�g���W
	XMFLOAT3 lightPos_ = { 0, 0, 0 };
	//���C�g�F
	XMFLOAT3 lightColor_ = { 1, 1, 1 };
	//���C�g���������W��
	XMFLOAT3 lightAtten_ = { 1.0f, 1.0f, 1.0f };
	//�L�����t���O
	bool isActive_ = false;
};