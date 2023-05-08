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

public: //�\����
	
	//�ړ�����|�C���g
	struct MovePoints {
		std::vector<Vector3> points_; //�X�v���C����ԗp�̊e�|�C���g
		std::vector<Vector3> cameraRot_; //�J�����p�x
		std::vector<float> moveTime_; //�|�C���g�Ɉړ����鎞��
	};

public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="eye">�J�����̃��[���h���W</param>
	/// <param name="rot">��]�p</param>
	/// <param name="points">�X�v���C����Ԏ��ɒʂ�e�|�C���g</param>
	void Initialize(const Vector3& eye, const Vector3& rot, const MovePoints& movePoints, bool isRoop = false);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �_���[�W�G�t�F�N�g�����p�t���O�𗧂Ă�
	/// </summary>
	void SetIsDamage() { isDamage_ = true; }

	/// <summary>
	/// ���[���h�s��擾
	/// </summary>
	/// <returns></returns>
	XMMATRIX GetMatWorld() { return matWorld_; }

	/// <summary>
	/// �I�_�t���O�擾
	/// </summary>
	/// <returns>�I�_�t���O</returns>
	bool GetIsEnd() { return isEnd_; }

private: //�����o�֐�

	/// <summary>
	/// �X�v���C�����
	/// </summary>
	/// <param name="points">�ʂ�|�C���g</param>
	/// <param name="startIndex">�|�C���g��ʂ������̃J�E���g</param>
	/// <param name="t">����</param>
	/// <returns>���W</returns>
	Vector3 Spline(const std::vector<Vector3>& points, int32_t startIndex, float t);

	/// <summary>
	/// �X�v���C����Ԃ̈ړ�
	/// </summary>
	void SplineMove();

	/// <summary>
	/// ���[���h�s����
	/// </summary>
	void UpdateMatWorld();

private: //�ÓI�����o�ϐ�

private: //�����o�ϐ�
	Vector3 eye_; //���[���h���W
	Vector3 rot_; //��]�p
	Vector3 target_; //�^�[�Q�b�g
	XMMATRIX matWorld_; //���[���h�s��
	MovePoints movePoints_; //�ړ�����e�|�C���g�i�[�R���e�i

	long long nowCount_; //���ݎ���
	long long elapsedCount_; //�o�ߎ��� 

	float timeRate_; //�ړ��������Ԃ�0~1�ŕ]��
	int32_t startIndex_ = 1; //�ړ������|�C���g���J�E���g

	Vector3 initPos_; //�������W
	Vector3 initRot_; //������]

	bool isStop_ = false; //�f�o�b�O�p�J������~�t���O
	bool isDamage_ = false; //�_���[�W���󂯂����̃t���O
	bool isRoop_ = false; //���[�v�p�t���O
	bool isEnd_ = false; //�I�_�t���O
	float delayCount_ = 0;
};
