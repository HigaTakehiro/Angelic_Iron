#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "KeyInput.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "MouseInput.h"
#include "Object3d.h"
#include "Vector3.h"
#include "Camera.h"

class TitleScene : public BaseScene
{
public: //�����o�֐�
	/// <summary>
	/// �������֐�
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
	const XMFLOAT2 initSize = { 1, 1 };

	Sprite* title = nullptr;
	Sprite* startButton = nullptr;
	Sprite* stage1 = nullptr;
	Sprite* stage2 = nullptr;
	Sprite* manualButton = nullptr;
	Sprite* manual = nullptr;
	Sprite* close = nullptr;

	XMFLOAT2 titlePos;
	XMFLOAT2 startButtonPos;
	XMFLOAT2 startButtonSize;
	XMFLOAT2 stage1Pos;
	XMFLOAT2 stage1Size;
	XMFLOAT2 stage2Pos;
	XMFLOAT2 stage2Size;
	XMFLOAT2 manualButtonPos;
	XMFLOAT2 manualButtonSize;
	XMFLOAT2 manualSize;
	XMFLOAT2 closePos;
	XMFLOAT2 closeSize;

	PostEffect* postEffect = nullptr;
	Object3d* titlePlayer = nullptr;
	Object3d* ground = nullptr;
	Camera* camera = nullptr;

	Vector3 playerRot;
	Vector3 playerPos;
	Vector3 playerScale;

	Vector3 groundPos;
	Vector3 groundScale;


};

