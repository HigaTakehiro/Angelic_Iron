#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "MotionMath.h"

class BossScene : public BaseScene
{
public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

private: //�����o�ϐ�


};

