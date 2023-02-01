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
public: //メンバ関数
	/// <summary>
	/// 初期化関数
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

private: //メンバ関数

private: //静的メンバ変数
	static const int32_t titleOutTime = 40;
	static const int32_t stage1ComeTime = 150;
	static const int32_t stage2ComeTime = 160;
	static const int32_t manualComeTime = 170;
	static const int32_t manualOpenTime = 60;
	static const int32_t startTime = 60;
	static const int32_t manualSlideTime = 60;

private: //メンバ変数
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
	DebugText debugText; //デバッグテキスト表示用クラス

	TextDraw* textDraw = nullptr;

	FBXObject3d* test;
	//ポストエフェクト番号
	PostEffect::PostEffectNo postEffectNo;

	DirectX::XMFLOAT2 titlePos;
	DirectX::XMFLOAT2 startButtonPos;
	DirectX::XMFLOAT2 startButtonSize;
	DirectX::XMFLOAT2 stage1Pos;
	DirectX::XMFLOAT2 stage1Size;
	DirectX::XMFLOAT2 stage2Pos;
	DirectX::XMFLOAT2 stage2Size;
	DirectX::XMFLOAT2 manualButtonPos;
	DirectX::XMFLOAT2 manualButtonSize;
	DirectX::XMFLOAT2 manualSize;
	DirectX::XMFLOAT2 manualMaxSize;
	DirectX::XMFLOAT2 manualPos;
	DirectX::XMFLOAT2 allowPos;
	DirectX::XMFLOAT2 allowSize;
	DirectX::XMFLOAT2 closePos;
	DirectX::XMFLOAT2 closeSize;
	DirectX::XMFLOAT2 mousePos;

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

