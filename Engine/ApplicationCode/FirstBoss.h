#pragma once
#include "BaseBoss.h"

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

private: //�ÓI�����o�ϐ�

private: //�����o�ϐ�
	
};

