#pragma once
#include "BaseBoss.h"
#include "BossScene.h"
#include "BossScenePlayer.h"
#include "BulletManager.h"

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
	void Update(const Vector3& playerPos, const int32_t delayTime = 0);
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �摜�`�揈��
	/// </summary>
	void SpriteDraw();
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
	bool GetIsLeftHandDead() { return isLeftHandDead_; }
	/// <summary>
	/// �E�莀�S�t���O�擾
	/// </summary>
	/// <returns></returns>
	bool GetIsRightHandDead() { return isRightHandDead_; }
	/// <summary>
	/// �G�t�F�N�g�^�C�~���O�t���O�擾
	/// </summary>
	/// <returns></returns>
	bool GetIsMovieEffectTiming() override { return isMoviePoint_2_; }
	/// <summary>
	/// ����I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>����I�u�W�F�N�g</returns>
	Object3d* GetLeftHandObj() { return leftHand_; }
	/// <summary>
	/// �E��I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�E��I�u�W�F�N�g</returns>
	Object3d* GetRightHandObj() { return rightHand_; }

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
	/// <summary>
	/// HP�o�[���W�X�V
	/// </summary>
	void HPBarUpdate();

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
	Object3d* leftHand_;
	Object3d* leftHandShadow_;
	Sprite* leftHpBar_;
	Sprite* leftHpRedBar_;
	//�E��
	Object3d* rightHand_;
	Object3d* rightHandShadow_;
	Sprite* rightHpBar_;
	Sprite* rightHpRedBar_;
	//����֘A�ϐ�
	Vector3 leftHandPos_;
	Vector3 leftHandScale_;
	Vector3 leftHandRot_;
	int32_t leftHandHP_;
	bool isLeftHandDamage_;
	bool isLeftHandDead_;
	int32_t leftHandDamageTimer_;
	int32_t leftHandDeadTimer_;
	float leftHandAngle_;
	Vector3 leftHandShadowPos_;
	//�E��֘A�ϐ�
	Vector3 rightHandPos_;
	Vector3 rightHandScale_;
	Vector3 rightHandRot_;
	int32_t rightHandHP_;
	bool isRightHandDamage_;
	bool isRightHandDead_;
	int32_t rightHandDamageTimer_;
	int32_t rightHandDeadTimer_;
	float rightHandAngle_;
	Vector3 rightHandShadowPos_;

	//���[�r�[�֘A�ϐ�
	int32_t movieTimer_;
	bool isMoviePoint_1_ = false;
	bool isMoviePoint_2_ = false;
	bool isMoviePoint_3_ = false;

	//�U���֘A�ϐ�
	int32_t rollingShotTimer_;
	int32_t guardTimer_;
	int32_t stompTimer_;
	int32_t punchTimer_;
	int32_t actionPreTimer_;
	int32_t actionPostTimer_;
	bool isActionPos_;
	bool isActionPost_;
};

