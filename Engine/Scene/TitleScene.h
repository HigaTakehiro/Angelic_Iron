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
#include "MouseInput.h"
#include "Easing.h"

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

private: //�����o�֐�
	/// <summary>
	/// �}�E�X���X�v���C�g�ɐG��Ă��邩
	/// </summary>
	/// <param name="mousePos">�}�E�X�̈ʒu</param>
	/// <param name="spritePos">�X�v���C�g�̈ʒu</param>
	/// <param name="spriteWidth">�X�v���C�g����</param>
	/// <param name="spriteHeight">�X�v���C�g�c��</param>
	/// <returns>�}�E�X���X�v���C�g��G��Ă���</returns>
	bool IsMouseHitSprite(XMFLOAT2 mousePos, XMFLOAT2 spritePos, float spriteWidth, float spriteHeight);

private: //�ÓI�����o�ϐ�
	static const int32_t titleOutTime = 40;
	static const int32_t stage1ComeTime = 150;
	static const int32_t stage2ComeTime = 155;
	static const int32_t manualComeTime = 160;
	static const int32_t manualOpenTime = 60;

private: //�����o�ϐ�
	const float selectAlpha = 0.5f;
	const float initAlpha = 1.0f;

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
	XMFLOAT2 manualMaxSize;
	XMFLOAT2 closePos;
	XMFLOAT2 closeSize;
	XMFLOAT2 mousePos;

	int32_t stageSelectTimer;
	int32_t manualTimer;

	PostEffect* postEffect = nullptr;
	Object3d* titlePlayer = nullptr;
	Object3d* ground = nullptr;
	Camera* camera = nullptr;

	Vector3 playerRot;
	Vector3 playerPos;
	Vector3 playerScale;

	Vector3 groundPos;
	Vector3 groundScale;

	bool isStageSelect;
	bool isManual;
	bool isStage1;
	bool isStage2;
};

