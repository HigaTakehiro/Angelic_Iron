#pragma once
#include "Object3d.h"
#include "ModelManager.h"
#include "Vector3.h"
#include "Camera.h"
#include "Sprite.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "MotionMath.h"
#include "SafeDelete.h"
#include "Easing.h"

class BossScenePlayer
{
public:
	BossScenePlayer() = default;
	~BossScenePlayer() = default;

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="camera">�J����</param>
	void Initialize(Camera* camera);
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �X�v���C�g�`��
	/// </summary>
	void SpriteDraw();
	/// <summary>
	/// �v���C���[�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns></returns>
	Object3d* GetPlayerObj() { return player; }
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

private: //�����o�֐�
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// �_�b�V��
	/// </summary>
	void Dash();
	/// <summary>
	/// �W�����v
	/// </summary>
	void Jump();

private: //�ÓI�����o�ϐ�
	static const int32_t rotationTime;
	static const int32_t dashTime;
	static const float gravity;

private: //�����o�ϐ�
	//�v���C���[
	Object3d* player;
	//�J����
	Camera* camera;
	//���[�J�����W
	Vector3 pos;
	//��]�p
	Vector3 rot;
	//�傫��
	Vector3 scale;
	//�J�����A���O��
	float cameraAngle;
	//�J�������W
	Vector3 cameraPos;
	//��]����
	int32_t rotationTimer;
	//�_�b�V���t���O
	bool isDash;
	bool isLeftDash;
	bool isRightDash;
	//�_�b�V������
	int32_t dashTimer;
	//�_�b�V���p�����A���O���ۑ�
	float initAngle;
	//�W�����v�㏸���x
	float jumpPower;
	//�W�����v�t���O
	bool isJump;
};