#pragma once
#include "BaseEnemy.h"
#include "RailScene.h"

class HomingEnemy : public BaseEnemy
{
public:
	HomingEnemy() = default;

	~HomingEnemy();

public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="modelKey">���f���̃L�[</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	void Initialize(const std::string modelKey, const Vector3& pos, const Vector3& rot) override;
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="playerPos">�v���C���[�̍��W</param>
	/// <param name="delayTime">�X���[���o�p�x������</param>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;
	/// <summary>
	/// �摜�`�揈��
	/// </summary>
	void SpriteDraw() override;
	/// <summary>
	/// ���S����
	/// </summary>
	void DeadPerformance() override;

private: //�����o�֐�

	/// <summary>
	/// �U������
	/// </summary>
	void Attack() override;

private: //�ÓI�����o�ϐ�

private: //�����o�ϐ�
};

