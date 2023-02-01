#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ImageManager.h"
#include "Easing.h"
#include "LightGroup.h"

class ResultScene : public BaseScene
{
public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dxCommon"></param>
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

	PostEffect* postEffect = nullptr; //�|�X�g�G�t�F�N�g�N���X
	Sprite* score = nullptr; //�X�R�A�摜
	Sprite* scoreNumbers[6] = {}; ///�X�R�A�p�A�Ԑ����摜
	Sprite* titleBack = nullptr;

	LightGroup* light = nullptr;

	DirectX::XMFLOAT2 mousePos;
	DirectX::XMFLOAT2 titleBackSize;
	float titleBackAlpha;

	PostEffect::PostEffectNo postEffectNo; //�|�X�g�G�t�F�N�g�ԍ�

	float scoreRollTimer;
	DirectX::XMFLOAT2 scoreRollPos[6] = {};

	Object3d* resultPlayer = nullptr;
	Object3d* ground = nullptr;
	Object3d* celetialSphere = nullptr;
	Object3d* gun = nullptr;
	Camera* camera = nullptr;

	Vector3 playerRot;
	Vector3 playerPos;
	Vector3 playerScale;

	Vector3 groundPos;
	Vector3 groundScale;

	Vector3 cameraPos;
	Vector3 cameraTargetPos;
};

