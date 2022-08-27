#pragma once
#include "KeyInput.h"
#include "Object3d.h"
#include "Model.h"
#include "MouseInput.h"
#include "PadInput.h"
#include "Sprite.h"
#include "Vector3.h"
#include "Camera.h"
#include "DebugText.h"
#include "WinApp.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class Player
{
public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(Camera* camera);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	/// <summary>
	/// �X�v���C�g�`�揈��
	/// </summary>
	void SpriteDraw();

	/// <summary>
	/// 3D�I�u�W�F�N�g�`�揈��
	/// </summary>
	void ObjectDraw();

	/// <summary>
	/// �ʒu�擾
	/// </summary>
	/// <returns>�ʒu</returns>
	const XMFLOAT3 GetPlayerPos() { return aimPos3d; }

	/// <summary>
	/// �����擾
	/// </summary>
	/// <returns>����</returns>
	//const XMFLOAT3 GetPlayerRot() { return  }

	/// <summary>
	/// �v���C���[�I�u�W�F�N�g�̎擾
	/// </summary>
	/// <returns>�v���C���[�I�u�W�F�N�g</returns>
	Object3d* GetPlayerObject() { return player; }

	/// <summary>
	/// �e�I�u�W�F�N�g�̎擾
	/// </summary>
	/// <returns>�e�I�u�W�F�N�g</returns>
	Object3d* GetShotObject() { return shot; }

	/// <summary>
	/// ���Z�b�g����
	/// </summary>
	void Reset();

private: //�����o�֐�
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// �ʏ�U������
	/// </summary>
	void Shot();

	/// <summary>
	/// 3d���e�B�N���X�V����
	/// </summary>
	void AimUpdate();

	/// <summary>
	/// ���W�ɍs����|���čŌ��w���Z����
	/// </summary>
	/// <param name="vec">���W</param>
	/// <param name="mat">�s��</param>
	/// <returns>�v�Z����</returns>
	XMVECTOR Wdivided(XMVECTOR vec, XMMATRIX mat);

private: //�����o�ϐ�
	Vector3 playerLPos = { 0, 0, 0 };
	Vector3 playerWPos = { 0, 0, 0 };
	Vector3 playerRot = { 0, 0, 0 };
	Vector3 playerScale = { 0, 0, 0 };
	Vector3 shotPos = { 0, 0, 0 };
	Vector3 shotRot = { 0, 0, 0 };
	Vector3 shotScale = { 0, 0, 0 };

	Model* playerModel = nullptr;
	Model* shotModel = nullptr;
	Object3d* player = nullptr;
	Object3d* shot = nullptr;
	Object3d* aim3d = nullptr;
	Sprite* aim = nullptr;

	bool isShot = false;
	//�Q�[���V�[���p�ϐ�
	XMFLOAT2 aimPos;
	Vector3 oldShotPos;
	Vector3 targetAimPos;
	XMVECTOR positionRaticle;
	XMMATRIX matViewPort;
	XMMATRIX matViewProjection;
	XMFLOAT3 aimPosMath;

	Vector3 aimPos3d;
	Camera* camera;
};

