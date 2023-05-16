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
#include "ShadowMap.h"

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
	std::unique_ptr<Sprite> title_ = nullptr;
	//スタートボタン
	std::unique_ptr<Sprite> startButton_ = nullptr;
	//ステージ1ボタン
	std::unique_ptr<Sprite> stage1_ = nullptr;
	//マニュアルボタン
	std::unique_ptr<Sprite> manualButton_ = nullptr;
	//操作説明1
	std::unique_ptr<Sprite> manual_ = nullptr;
	//操作説明2
	std::unique_ptr<Sprite> manual2_ = nullptr;
	//マニュアル閉じボタン
	std::unique_ptr<Sprite> close_ = nullptr;
	//マニュアルページ変更ボタン
	std::unique_ptr<Sprite> allow_ = nullptr;
	//デバッグテキスト表示用クラス
	DebugText debugText_;
	//ポストエフェクト番号
	PostEffect::PostEffectNo postEffectNo_;

	//スプライト用変数
	//タイトル座標
	DirectX::XMFLOAT2 titlePos_;
	//スタートボタン座標
	DirectX::XMFLOAT2 startButtonPos_;
	//スタートボタンサイズ
	DirectX::XMFLOAT2 startButtonSize_;
	//ステージ1座標
	DirectX::XMFLOAT2 stage1Pos_;
	//ステージ1サイズ
	DirectX::XMFLOAT2 stage1Size_;
	//マニュアルボタン座標
	DirectX::XMFLOAT2 manualButtonPos_;
	//マニュアルボタンサイズ
	DirectX::XMFLOAT2 manualButtonSize_;
	//操作説明サイズ
	DirectX::XMFLOAT2 manualSize_;
	//操作説明最大サイズ
	DirectX::XMFLOAT2 manualMaxSize_;
	//操作説明座標
	DirectX::XMFLOAT2 manualPos_;
	//マニュアルページ変更ボタン座標
	DirectX::XMFLOAT2 allowPos_;
	//マニュアルページ変更ボタンサイズ
	DirectX::XMFLOAT2 allowSize_;
	//マニュアル閉じるボタン座標
	DirectX::XMFLOAT2 closePos_;
	//マニュアル閉じるボタンサイズ
	DirectX::XMFLOAT2 closeSize_;
	//マウス座標
	DirectX::XMFLOAT2 mousePos_;
	//ステージ選択演出用タイマー
	int32_t stageSelectTimer_;
	//マニュアル開閉演出用タイマー
	int32_t manualTimer_;
	//ステージ開始演出時間
	int32_t startTimer_;
	//マニュアルページ変更時間
	int32_t manualSlideTimer_;

	//ポストエフェクト
	std::unique_ptr<PostEffect> postEffect_ = nullptr;
	//タイトル画面プレイヤー
	std::unique_ptr<Object3d> titlePlayer_ = nullptr;
	//カメラ
	std::unique_ptr<Camera> camera_ = nullptr;
	//ライト
	std::unique_ptr<LightGroup> light_ = nullptr;
	//パーティクル
	std::unique_ptr<ParticleManager> particle_ = nullptr;
	//jsonローダー
	std::unique_ptr<JsonLoader> jsonLoader_ = nullptr;
	//プレイヤー回転角
	Vector3 playerRot_;
	//プレイヤー座標
	Vector3 playerPos_;
	//プレイヤーサイズ
	Vector3 playerScale_;
	//カメラ座標
	Vector3 cameraPos_;
	//カメラ注視点
	Vector3 cameraTargetPos_;
	//ページ番号
	int32_t pageNumber_;
	//前ページ番号
	int32_t prePageNumber_;
	//ステージ選択画面フラグ
	bool isStageSelectMenu_;
	//ステージ選択フラグ
	bool isStageChoice_;
	//マニュアル表示フラグ
	bool isManual_;
	//ステージ1選択フラグ
	bool isStage1_;
	//ページ変更フラグ(次のページ)
	bool isNextPage_;
	//ページ変更フラグ(前のページ)
	bool isPrevPage_;

	ShadowMap* shadow_;

};