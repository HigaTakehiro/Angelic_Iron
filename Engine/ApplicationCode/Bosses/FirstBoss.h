#pragma once
#include "BaseBoss.h"
#include "BossScene.h"
#include "BossScenePlayer.h"

class FirstBoss : public BaseBoss
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	FirstBoss() = default;
	/// <summary>
	///	�f�X�g���N�^
	/// </summary>
	~FirstBoss() = default;

public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(const std::string modelKey, const Vector3& pos);
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(const Vector3& playerPos, const int delayTime = 0);
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();
	/// <summary>
	/// �s��
	/// </summary>
	void Action();
	/// <summary>
	/// ���[�r�[���o�s��
	/// </summary>
	void MovieAction();
	/// <summary>
	/// ����q�b�g���R�[���o�b�N�֐�
	/// </summary>
	void LeftHandOnCollision();
	/// <summary>
	/// �E��q�b�g���R�[���o�b�N�֐�
	/// </summary>
	void RightHandOnCollision();
	/// <summary>
	/// ����_���[�W���A�N�V����
	/// </summary>
	void LeftHandDamageReaction();
	/// <summary>
	/// �E��_���[�W���A�N�V����
	/// </summary>
	void RightHandDamageReaction();
	/// <summary>
	/// ���莀�S�t���O�擾
	/// </summary>
	/// <returns></returns>
	bool GetIsLeftHandDead() { return isLeftHandDead; }
	/// <summary>
	/// �E�莀�S�t���O�擾
	/// </summary>
	/// <returns></returns>
	bool GetIsRightHandDead() { return isRightHandDead; }
	/// <summary>
	/// �G�t�F�N�g�^�C�~���O�t���O�擾
	/// </summary>
	/// <returns></returns>
	bool GetIsMovieEffectTiming() { return isMoviePoint_2; }
	/// <summary>
	/// �J�����ړ��^�C�~���O�t���O�擾
	/// </summary>
	/// <returns></returns>
	bool GetIsCameraMoveTiming() { return isCameraMoveTiming; }
	/// <summary>
	/// ����I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>����I�u�W�F�N�g</returns>
	Object3d* GetLeftHandObj() { return leftHand; }
	/// <summary>
	/// �E��I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�E��I�u�W�F�N�g</returns>
	Object3d* GetRightHandObj() { return rightHand; }

private: //�����o�֐�
	/// <summary>
	/// �h��
	/// </summary>
	void Guard(const int32_t actionPreTime);
	/// <summary>
	/// ��]�U��
	/// </summary>
	void RollingShot(const int32_t actionPreTime);
	/// <summary>
	/// �����Ԃ��U��
	/// </summary>
	void Stomp();
	/// <summary>
	/// �����A�b�g�U��
	/// </summary>
	void Lariat();
	/// <summary>
	/// ���S���o
	/// </summary>
	void DeadReaction();
	/// <summary>
	/// ���莀�S���o
	/// </summary>
	void LeftHandDeadReaction();
	/// <summary>
	/// �E�莀�S���o
	/// </summary>
	void RightHandDeadReaction();

private: //�ÓI�����o�ϐ�

	const int32_t FirstBoss::rotationTime = 15;
	const int32_t FirstBoss::actionCoolTime = 60;
	const int32_t FirstBoss::rollingShotTime = 180;
	const int32_t FirstBoss::deadTime = 180;
	const int32_t FirstBoss::leftHandDeadTime = 180;
	const int32_t FirstBoss::rightHandDeadTime = 180;
	const int32_t FirstBoss::guardTime = 90;
	const int32_t FirstBoss::stompTime = 100;
	const int32_t FirstBoss::punchTime = 180;

private: //�����o�ϐ�
	// ����
	Object3d* leftHand;
	Object3d* leftHandShadow;
	Sprite* leftHpBar;
	Sprite* leftHpRedBar;
	//�E��
	Object3d* rightHand;
	Object3d* rightHandShadow;
	Sprite* rightHpBar;
	Sprite* rightHpRedBar;
	//����֘A�ϐ�
	Vector3 leftHandPos;
	Vector3 leftHandScale;
	Vector3 leftHandRot;
	int leftHandHP;
	bool isLeftHandDamage;
	bool isLeftHandDead;
	int32_t leftHandDamageTimer;
	int32_t leftHandDeadTimer;
	float leftHandAngle;
	Vector3 leftHandShadowPos;
	XMFLOAT2 leftHpBarPos;
	//�E��֘A�ϐ�
	Vector3 rightHandPos;
	Vector3 rightHandScale;
	Vector3 rightHandRot;
	int rightHandHP;
	bool isRightHandDamage;
	bool isRightHandDead;
	int32_t rightHandDamageTimer;
	int32_t rightHandDeadTimer;
	float rightHandAngle;
	Vector3 rightHandShadowPos;
	XMFLOAT2 rightHpBarPos;

	//���[�r�[�֘A�ϐ�
	int32_t movieTimer;
	bool isMoviePoint_1 = false;
	bool isMoviePoint_2 = false;
	bool isMoviePoint_3 = false;
	bool isCameraMoveTiming = false;

	//�U���֘A�ϐ�
	int32_t rollingShotTimer;
	int32_t guardTimer;
	int32_t stompTimer;
	int32_t punchTimer;
	int32_t actionPreTimer;
	int32_t actionPostTimer;
	bool isActionPos;
	bool isActionPost;
};

