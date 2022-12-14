#pragma once
#include "BaseEnemy.h"
#include "RailScene.h"

class StraightEnemy : public BaseEnemy
{
public:
	StraightEnemy() = default;

	~StraightEnemy();

public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="modelName">���f����</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	void Initialize(const ModelManager::ModelName modelName, const Vector3& pos, const Vector3& rot) override;
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="playerPos">�v���C���[�̍��W</param>
	/// <param name="delayTime">�X���[���o�p�x������</param>
	void Update(const int delayTime) override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;
	/// <summary>
	/// �摜�`�揈��
	/// </summary>
	void SpriteDraw() override;

private: //�����o�֐�
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move() override;
	/// <summary>
	/// �U������
	/// </summary>
	void Attack() override;

private: //�ÓI�����o�ϐ�

private: //�����o�ϐ�

};

