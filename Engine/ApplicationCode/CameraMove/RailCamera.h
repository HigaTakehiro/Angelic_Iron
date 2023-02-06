#pragma once
#include "camera.h"
#include "Vector3.h"
#include <DirectXMath.h>
#include <vector>
#include "KeyInput.h"
#include <chrono>
#include <thread>

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
	void Initialize(const Vector3& eye, const Vector3& rot, const std::vector<Vector3>& points, float maxTime, bool isRoop = false);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(float delayCount = 60.0f);

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset(std::vector<Vector3>& points);

	/// <summary>
	/// �J�n���Ԃ̃Z�b�g
	/// </summary>
	void SetStartTime(long long startTime) { this->startTime = startTime; }

	/// <summary>
	/// �_���[�W�G�t�F�N�g�����p�t���O�𗧂Ă�
	/// </summary>
	void SetIsDamage() { isDamage = true; }

	/// <summary>
	/// ���[���h�s��擾
	/// </summary>
	/// <returns></returns>
	XMMATRIX GetMatWorld() { return matWorld; }

	/// <summary>
	/// �I�_�t���O�擾
	/// </summary>
	/// <returns>�I�_�t���O</returns>
	bool GetIsEnd() { return isEnd; }

private: //�����o�֐�

	/// <summary>
	/// �X�v���C�����
	/// </summary>
	/// <param name="points">�ʂ�|�C���g</param>
	/// <param name="startIndex">�|�C���g��ʂ������̃J�E���g</param>
	/// <param name="t">����</param>
	/// <returns>���W</returns>
	Vector3 Spline(const std::vector<Vector3>& points, int startIndex, float t);

	/// <summary>
	/// �X�v���C����Ԃ̈ړ�
	/// </summary>
	void SplineMove();

	/// <summary>
	/// ���[���h�s����
	/// </summary>
	void UpdateMatWorld();

	/// <summary>
    /// �_���[�W���󂯂����̃J�������o
    /// </summary>
	void DamageCameraEffect();

private: //�ÓI�����o�ϐ�
	//�_���[�W�G�t�F�N�g��������
	static const int damageEffectTime = 20;

private: //�����o�ϐ�
	Vector3 eye; //���[���h���W
	Vector3 rot; //��]�p
	Vector3 target; //�^�[�Q�b�g
	XMMATRIX matWorld; //���[���h�s��
	std::vector<Vector3> points; //�X�v���C����ԗp�̊e�|�C���g

	long long startTime; //�J�n����
	long long nowCount; //���ݎ���
	long long elapsedCount; //�o�ߎ��� 
	std::chrono::steady_clock::time_point reference;

	float maxTime; //�|�C���g�Ԃ��ړ����鎞��
	float timeRate; //�ړ��������Ԃ�0~1�ŕ]��
	int startIndex = 1; //�ړ������|�C���g���J�E���g

	Vector3 initPos; //�������W
	Vector3 initRot; //������]

	bool isStop = false; //�f�o�b�O�p�J������~�t���O
	bool isDamage = false; //�_���[�W���󂯂����̃t���O
	bool isRoop = false; //���[�v�p�t���O
	bool isEnd = false; //�I�_�t���O
	float delayCount = 0;

	int  damageEffectTimer; //�_���[�W���o�p�^�C�}�[
};

