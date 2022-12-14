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
	void Initialize(const ModelManager::ModelName model, const Vector3& pos);
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
	void Guard();
	/// <summary>
	/// ��]�U��
	/// </summary>
	void RollingShot();
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
	static const int32_t rollingShotTime;
	static const int32_t leftHandDeadTime;
	static const int32_t rightHandDeadTime;
	static const int32_t guardTime;
	static const int32_t stompTime;
	static const int32_t punchTime;

private: //�����o�ϐ�
	// ����
	Object3d* leftHand;
	Object3d* leftHandShadow;
	//�E��
	Object3d* rightHand;
	Object3d* rightHandShadow;
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

	//�U���֘A�ϐ�
	int32_t rollingShotTimer;
	int32_t guardTimer;
	int32_t stompTimer;
	int32_t punchTimer;
};

