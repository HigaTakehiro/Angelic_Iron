#pragma once
#include "camera.h"
#include "Vector3.h"
#include "MatCalc.h"
#include <DirectXMath.h>
#include <vector>
#include "KeyInput.h"

class RailCamera
{
private: //�G�C���A�X
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="eye">�J�����̃��[���h���W</param>
	/// <param name="rot">��]�p</param>
	/// <param name="points">�X�v���C����Ԏ��ɒʂ�e�|�C���g</param>
	void Initialize(const Vector3& eye, const Vector3& rot, const std::vector<Vector3>& points, const float& maxTime);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();


	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset();

private: //�����o�֐�

	/// <summary>
	/// �X�v���C�����
	/// </summary>
	/// <param name="points">�ʂ�|�C���g</param>
	/// <param name="startIndex">�|�C���g��ʂ������̃J�E���g</param>
	/// <param name="t">����</param>
	/// <returns>���W</returns>
	Vector3 Spline(const std::vector<Vector3>& points, const int& startIndex, const float& t);

	/// <summary>
	/// �X�v���C����Ԃ̈ړ�
	/// </summary>
	void SplineMove();

	/// <summary>
	/// ���[���h�s����
	/// </summary>
	void UpdateMatWorld();

private: //�����o�ϐ�
	Vector3 eye; //���[���h���W
	Vector3 rot; //��]�p
	Vector3 target; //�^�[�Q�b�g
	XMMATRIX matWorld; //���[���h�s��
	std::vector<Vector3> points; //�X�v���C����ԗp�̊e�|�C���g

	long long startTime; //�J�n����
	long long nowCount; //���ݎ���
	long long elapsedCount; //�o�ߎ��� 

	float maxTime; //�|�C���g�Ԃ��ړ����鎞��
	float timeRate; //�ړ��������Ԃ�0~1�ŕ]��
	int startIndex; //�ړ������|�C���g���J�E���g

	Vector3 initPos;
	Vector3 initRot;

	bool isStop = true;
};

