#pragma once
#include <DirectXMath.h>

class CircleShadow {
private: //�G�C���A�X
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	struct ConstBufferData {
		XMVECTOR dir_;
		XMFLOAT3 casterPos_;
		float distanceCasterLight_;
		XMFLOAT3 atten_;
		float pad3_;
		XMFLOAT2 cosAngle_;
		unsigned int isActive_;
		float pad4_;
	};

public: //�����o�֐�
	/// <summary>
	/// �������Z�b�g
	/// </summary>
	/// <param name="dir">����</param>
	void SetDir(const XMVECTOR& dir) { dir_ = DirectX::XMVector3Normalize(dir); }

	/// <summary>
	/// �L���X�^�[���W���Z�b�g
	/// </summary>
	/// <param name="casterPos">��Q��</param>
	void SetCasterPos(const XMFLOAT3& casterPos) { casterPos_ = casterPos; }

	/// <summary>
	/// �L���X�^�[�ƃ��C�g�̋���
	/// </summary>
	/// <param name="distanceCasterLight"></param>
	void SetDistanceCasterLight(float distanceCasterLight) { distanceCasterLight_ = distanceCasterLight; }

	/// <summary>
	/// ���������W�����Z�b�g
	/// </summary>
	/// <param name="atten">���������W��</param>
	void SetAtten(const XMFLOAT3& atten) { atten_ = atten; }

	/// <summary>
	/// �����p�x���Z�b�g
	/// </summary>
	/// <param name="cosAngle">�����p�x</param>
	void SetAngle(const XMFLOAT2& cosAngle) {
		cosAngle_.x = cosf(DirectX::XMConvertToRadians(cosAngle.x));
		cosAngle_.y = cosf(DirectX::XMConvertToRadians(cosAngle.y));
	}

	/// <summary>
	/// �ۉe�L����
	/// </summary>
	/// <param name="isActive">�L�����t���O</param>
	void SetIsActive(bool isActive) { isActive_ = isActive; }

	/// <summary>
	/// �L�����t���O���擾
	/// </summary>
	/// <returns>�L�����t���O</returns>
	bool GetIsActive() { return isActive_; }

	/// <summary>
	/// �������擾
	/// </summary>
	/// <returns>����</returns>
	const XMVECTOR& GetDir() { return dir_; }

	/// <summary>
	/// �L���X�^�[���W���擾
	/// </summary>
	/// <returns>�L���X�^�[���W</returns>
	const XMFLOAT3& GetCasterPos() { return casterPos_; }

	/// <summary>
	/// �L���X�^�[�ƃ��C�g�̋������擾
	/// </summary>
	/// <returns>�L���X�^�[�ƃ��C�g�̋���</returns>
	float GetDistanceCasterLight() { return distanceCasterLight_; }

	/// <summary>
	/// ���������W�����擾
	/// </summary>
	/// <returns>���������W��</returns>
	const XMFLOAT3& GetAtten() { return atten_; }

	/// <summary>
	/// �����p�x���擾
	/// </summary>
	/// <returns>�����p�x</returns>
	const XMFLOAT2& GetAngle() { return cosAngle_; }

private: //�����o�ϐ�
	XMVECTOR dir_ = { 1, 0, 0, 0 };
	float distanceCasterLight_ = 100.0f;
	XMFLOAT3 casterPos_ = { 0, 0, 0 };
	XMFLOAT3 atten_ = { 0.5f, 0.6f, 0.0f };
	XMFLOAT2 cosAngle_ = { 0.2f, 0.5f };
	bool isActive_ = false;
};