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
#include "Shapes.h"
#include "ParticleManager.h"
#include "LightGroup.h"
#include "DebugText.h"
#include "TextDraw.h"
#include "MotionMath.h"

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

private: //�ÓI�����o�ϐ�
	static const int32_t titleOutTime = 40;
	static const int32_t stage1ComeTime = 150;
	static const int32_t stage2ComeTime = 160;
	static const int32_t manualComeTime = 170;
	static const int32_t manualOpenTime = 60;
	static const int32_t startTime = 60;
	static const int32_t manualSlideTime = 60;

private: //�����o�ϐ�
	const float selectAlpha = 0.5f;
	const float initAlpha = 1.0f;

	Sprite* title = nullptr;
	Sprite* startButton = nullptr;
	Sprite* stage1 = nullptr;
	Sprite* stage2 = nullptr;
	Sprite* manualButton = nullptr;
	Sprite* manual = nullptr;
	Sprite* manual2 = nullptr;
	Sprite* close = nullptr;
	Sprite* aim = nullptr;
	Sprite* allow = nullptr;
	DebugText debugText; //�f�o�b�O�e�L�X�g�\���p�N���X

	TextDraw* textDraw = nullptr;

	FBXObject3d* test;
	//�|�X�g�G�t�F�N�g�ԍ�
	PostEffect::PostEffectNo postEffectNo;

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
	XMFLOAT2 manualPos;
	XMFLOAT2 allowPos;
	XMFLOAT2 allowSize;
	XMFLOAT2 closePos;
	XMFLOAT2 closeSize;
	XMFLOAT2 mousePos;

	int32_t stageSelectTimer;
	int32_t manualTimer;
	int32_t startTimer;
	int32_t manualSlideTimer;

	PostEffect* postEffect = nullptr;
	Object3d* titlePlayer = nullptr;
	Object3d* wave = nullptr;
	Object3d* celetialSphere = nullptr;
	Object3d* aircraft_Carrier = nullptr;
	Model* testSquareModel = nullptr;
	Object3d* testSquare = nullptr;
	Camera* camera = nullptr;
	LightGroup* light = nullptr;
	ParticleManager* particle = nullptr;

	Vector3 playerRot;
	Vector3 playerPos;
	Vector3 playerScale;

	Vector3 wavePos;
	Vector3 waveScale;

	Vector3 cameraPos;
	Vector3 cameraTargetPos;

	Vector3 sphereRot;

	int pageNumber;
	int prePageNumber;

	bool isStageSelect;
	bool isStageChoice;
	bool isManual;
	bool isStage1;
	bool isStage2;
	bool isNextPage;
	bool isPrevPage;
};
