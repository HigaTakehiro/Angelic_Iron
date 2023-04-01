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
#include "MotionMath.h"
#include "JsonLoader.h"

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
	/// <summary>
	/// シーン切り替え処理
	/// </summary>
	void SceneChange();

private: //静的メンバ変数
	//タイトルが画面外に出る時間
	static const int32_t titleOutTime = 40;
	//ステージ1ボタン表示時間
	static const int32_t stage1ComeTime = 150;
	//マニュアルボタン表示時間
	static const int32_t manualComeTime = 170;
	//マニュアル開く時間
	static const int32_t manualOpenTime = 60;
	//ステージ開始時間
	static const int32_t startTime = 60;
	//マニュアルスライド時間
	static const int32_t manualSlideTime = 60;

private: //メンバ変数
	//ボタンが選択されているときのアルファ値
	const float selectAlpha = 0.5f;
	//ボタン初期アルファ値
	const float initAlpha = 1.0f;

	//スプライト
	//タイトル
	std::unique_ptr<Sprite> title = nullptr;
	//スタートボタン
	std::unique_ptr<Sprite> startButton = nullptr;
	//ステージ1ボタン
	std::unique_ptr<Sprite> stage1 = nullptr;
	//マニュアルボタン
	std::unique_ptr<Sprite> manualButton = nullptr;
	//操作説明1
	std::unique_ptr<Sprite> manual = nullptr;
	//操作説明2
	std::unique_ptr<Sprite> manual2 = nullptr;
	//マニュアル閉じボタン
	std::unique_ptr<Sprite> close = nullptr;
	//マニュアルページ変更ボタン
	std::unique_ptr<Sprite> allow = nullptr;
	//デバッグテキスト表示用クラス
	DebugText debugText;
	//ポストエフェクト番号
	PostEffect::PostEffectNo postEffectNo;

	//スプライト用変数
	//タイトル座標
	DirectX::XMFLOAT2 titlePos;
	//スタートボタン座標
	DirectX::XMFLOAT2 startButtonPos;
	//スタートボタンサイズ
	DirectX::XMFLOAT2 startButtonSize;
	//ステージ1座標
	DirectX::XMFLOAT2 stage1Pos;
	//ステージ1サイズ
	DirectX::XMFLOAT2 stage1Size;
	//マニュアルボタン座標
	DirectX::XMFLOAT2 manualButtonPos;
	//マニュアルボタンサイズ
	DirectX::XMFLOAT2 manualButtonSize;
	//操作説明サイズ
	DirectX::XMFLOAT2 manualSize;
	//操作説明最大サイズ
	DirectX::XMFLOAT2 manualMaxSize;
	//操作説明座標
	DirectX::XMFLOAT2 manualPos;
	//マニュアルページ変更ボタン座標
	DirectX::XMFLOAT2 allowPos;
	//マニュアルページ変更ボタンサイズ
	DirectX::XMFLOAT2 allowSize;
	//マニュアル閉じるボタン座標
	DirectX::XMFLOAT2 closePos;
	//マニュアル閉じるボタンサイズ
	DirectX::XMFLOAT2 closeSize;
	//マウス座標
	DirectX::XMFLOAT2 mousePos;
	//ステージ選択演出用タイマー
	int32_t stageSelectTimer;
	//マニュアル開閉演出用タイマー
	int32_t manualTimer;
	//ステージ開始演出時間
	int32_t startTimer;
	//マニュアルページ変更時間
	int32_t manualSlideTimer;

	//ポストエフェクト
	std::unique_ptr<PostEffect> postEffect = nullptr;
	//タイトル画面プレイヤー
	std::unique_ptr<Object3d> titlePlayer = nullptr;
	//カメラ
	std::unique_ptr<Camera> camera = nullptr;
	//ライト
	std::unique_ptr<LightGroup> light = nullptr;
	//パーティクル
	std::unique_ptr<ParticleManager> particle = nullptr;
	//jsonローダー
	std::unique_ptr<JsonLoader> jsonLoader = nullptr;
	//プレイヤー回転角
	Vector3 playerRot;
	//プレイヤー座標
	Vector3 playerPos;
	//プレイヤーサイズ
	Vector3 playerScale;
	//カメラ座標
	Vector3 cameraPos;
	//カメラ注視点
	Vector3 cameraTargetPos;
	//ページ番号
	int pageNumber;
	//前ページ番号
	int prePageNumber;
	//ステージ選択画面フラグ
	bool isStageSelectMenu;
	//ステージ選択フラグ
	bool isStageChoice;
	//マニュアル表示フラグ
	bool isManual;
	//ステージ1選択フラグ
	bool isStage1;
	//ページ変更フラグ(次のページ)
	bool isNextPage;
	//ページ変更フラグ(前のページ)
	bool isPrevPage;
};