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
	const XMFLOAT3 GetPlayerPos() { return aim3d->GetPosition(); }

	/// <summary>
	/// �����擾
	/// </summary>
	/// <returns>����</returns>
	const XMFLOAT3 GetPlayerRot() { return posFarMath; }

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

private: //�����o�ϐ�
	Vector3 playerPos = { 0, 0, 0 };
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
	XMVECTOR posNear;
	XMVECTOR posFar;
	Vector3 posNearMath;
	Vector3 posFarMath;
	XMVECTOR positionRaticle;
	XMMATRIX matViewPort;
	XMMATRIX matViewProjection;
	XMFLOAT3 aimPosMath;

	//XMMATRIX matVPV;
	//XMMATRIX matInverseVPV;
	//Vector3 mouseDirection;
	XMVECTOR mouseDirection;
	Vector3 aimPos3d;
	Camera* camera;
};

