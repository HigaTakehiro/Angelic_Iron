#pragma once

#include <DirectXMath.h>

class SpotLight {
private: //�G�C���A�X
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: //�T�u�N���X
	struct ConstBufferData {
		XMVECTOR lightVec_;
		XMFLOAT3 lightPos_;
		float pad1_;
		XMFLOAT3 lightColor_;
		float pad2_;
		XMFLOAT3 lightAtten_;
		float pad3_;
		XMFLOAT2 lightCosAngle_;
		unsigned int isActive_;
		float pad4_;
	};

public: //�����o�֐�

	/// <summary>
	/// ���C�g�������擾
	/// </summary>
	/// <returns>���C�g����</returns>
	const XMVECTOR& GetLightVec() { return lightVec_; }

	/// <summary>
	/// ���C�g���W���擾
	/// </summary>
	/// <returns>���C�g���W</returns>
	const XMFLOAT3& GetLightPos() { return lightPos_; }

	/// <summary>
	/// ���C�g�F���擾
	/// </summary>
	/// <returns>���C�g�F</returns>
	const XMFLOAT3& GetLightColor() { return lightColor_; }

	/// <summary>
	/// ���C�g���������W�����擾
	/// </summary>
	/// <returns>���C�g���������W��</returns>
	const XMFLOAT3& GetLightAtten() { return lightAtten_; }

	/// <summary>
	/// ���C�g�����p�x(�J�n�p�x�A�I���p�x)
	/// </summary>
	/// <returns>���C�g�����p�x</returns>
	const XMFLOAT2& GetLightCosAngle() { return lightCosAngle_; }

	/// <summary>
	/// �L�����t���O���擾
	/// </summary>
	/// <returns>�L�����t���O</returns>
	bool GetIsActive() { return isActive_; }

	/// <summary>
	/// �X�|�b�g���C�g�L����
	/// </summary>
	/// <param name="isActive">�L�����t���O</param>
	void SetIsActive(bool isActive) { isActive_ = isActive; }

	/// <summary>
	/// ���C�g�������Z�b�g
	/// </summary>
	/// <param name="lightVec">���C�g����</param>
	void SetLightVec(const XMVECTOR& lightVec) { lightVec_ = DirectX::XMVector3Normalize(lightVec); }

	/// <summary>
	/// ���C�g���W���Z�b�g
	/// </summary>
	/// <param name="lightPos">���C�g���W</param>
	void SetLightPos(const XMFLOAT3& lightPos) { lightPos_ = lightPos; }

	/// <summary>
	/// ���C�g�F���Z�b�g
	/// </summary>
	/// <param name="lightColor">���C�g�F</param>
	void SetLightColor(const XMFLOAT3& lightColor) { lightColor_ = lightColor; }

	/// <summary>
	/// ���C�g���������W�����Z�b�g
	/// </summary>
	/// <param name="lightAtten">���C�g���������W��</param>
	void SetLightAtten(const XMFLOAT3& lightAtten) { lightAtten_ = lightAtten; }

	/// <summary>
	/// ���C�g�����p�x���Z�b�g
	/// </summary>
	/// <param name="lightCosAngle">���C�g�����p�x</param>
	void SetLightCosAngle(const XMFLOAT2& lightCosAngle) { 
		this->lightCosAngle_.x = cosf(DirectX::XMConvertToRadians(lightCosAngle.x));
		this->lightCosAngle_.y = cosf(DirectX::XMConvertToRadians(lightCosAngle.y));
	}

private: //�����o�ϐ�
	XMVECTOR lightVec_ = { 1, 0, 0, 0 };
	XMFLOAT3 lightPos_ = { 0, 0, 0 };
	XMFLOAT3 lightColor_ = { 1, 1, 1 };
	XMFLOAT3 lightAtten_ = { 1.0f, 1.0f, 1.0f };
	XMFLOAT2 lightCosAngle_ = { 0.5f, 0.2f };
	bool isActive_ = false;
};