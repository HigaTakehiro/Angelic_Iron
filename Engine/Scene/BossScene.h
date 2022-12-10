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

	//�r�����X�g
	std::list<std::unique_ptr<Object3d>> buildings;
	//�J����
	Camera* camera = nullptr;
	//�n��
	Object3d* ground = nullptr;
	//�V��
	Object3d* celetialSphere = nullptr;
	//�e�X�g�I�u�W�F�N�g
	Object3d* test = nullptr;
	//�|�X�g�G�t�F�N�g
	PostEffect* postEffect = nullptr;
	PostEffect::PostEffectNo postEffectNo;

	Vector3 groundPos = { 0, 0, 0 }; //�n�ʍ��W
	Vector3 groundScale = { 1, 1, 1 }; //�n�ʂ̑傫��
	Vector3 spherePos = { 0, 0, 0 }; //�V�����W
	Vector3 sphereScale = { 10, 10, 10 };  //�V���̑傫��
	Vector3 cameraPos = { 0, -50.0f, 0 };
	float cameraAngle;
};

