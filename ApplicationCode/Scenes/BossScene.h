#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "MotionMath.h"
#include "BossScenePlayer.h"
#include "PlayerBullet.h"
#include "Sound.h"
#include "BaseBoss.h"
#include "FirstBoss.h"
#include "Particle2d.h"
#include "LightGroup.h"
#include "TextDraw.h"
#include <fstream>

class BossScenePlayer;
class BaseBoss;
class FirstBoss;

class BossScene : public BaseScene
{
public: //サブクラス
	enum class FaceGraphics {
		OPE_NORMALFACE,
		OPE_SURPRISEFACE,
		OPE_SMILEFACE
	};

public: //メンバ関数

	/// <summary>
	/// 初期化
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
	/// <summary>
	/// プレイヤー弾を追加
	/// </summary>
	void AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet);
	/// <summary>
	/// ボス弾を追加
	/// </summary>
	/// <param name="bossEnemy"></param>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> bosBullet);

	/// <summary>
	/// 会話データの読み込み
	/// </summary>
	/// <param name="fileName"></param>
	void LoadTextMessage(const std::string fileName);

	/// <summary>
	/// 読み込んだテキストデータの更新
	/// </summary>
	void TextMessageUpdate();

	/// <summary>
	/// テキストデータの描画
	/// </summary>
	void TextMessageDraw();

private: //メンバ関数
	/// <summary>
	/// string型をwstring型に変換する(UTF-8)
	/// </summary>
	/// <param name="text">変換したいテキスト</param>
	/// <returns>wstring型のテキスト</returns>
	std::wstring StringToWstring(const std::string& text);

	/// <summary>
	/// シーン切り替え処理
	/// </summary>
	void SceneChange();

private: //静的メンバ変数
	static const int32_t opeAnimeTime = 6;
	static const int32_t closeWindowTime = 120;
	static const int32_t openWindowTime = 120;

private: //メンバ変数

	//ビルリスト
	std::list<std::unique_ptr<Object3d>> buildings_;
	//プレイヤー弾リスト
	std::list<std::unique_ptr<PlayerBullet>> playerBullets_;
	//ボス弾リスト
	std::list<std::unique_ptr<EnemyBullet>> bossBullets_;
	//2Dパーティクルリスト
	std::list<std::unique_ptr<Particle2d>> particles2d_;
	//カメラ
	Camera* camera_ = nullptr;
	//サウンド
	Sound* sound_ = nullptr;
	//プレイヤー
	BossScenePlayer* player_ = nullptr;
	//地面
	Object3d* ground_ = nullptr;
	//天球
	Object3d* celetialSphere_ = nullptr;
	//ポストエフェクト
	PostEffect* postEffect_ = nullptr;
	PostEffect::PostEffectNo postEffectNo_;
	int32_t postEffectTime_;
	//ライト
	LightGroup* light_ = nullptr;
	FaceGraphics faceType_;

	Vector3 groundPos_ = { 0, 0, 0 }; //地面座標
	Vector3 groundScale_ = { 1, 1, 1 }; //地面の大きさ
	Vector3 spherePos_ = { 0, 0, 0 }; //天球座標
	Vector3 sphereScale_ = { 10, 10, 10 };  //天球の大きさ

	Sprite* pause_ = nullptr;
	Sprite* titleBack_ = nullptr;
	Sprite* back_ = nullptr;
	Sprite* scoreText_ = nullptr;
	Sprite* scoreNumber_[6] = {};
	//テキスト用変数
	Sprite* faceWindow_ = nullptr;
	Sprite* textWindow_ = nullptr;
	Sprite* opeNormal_[3] = {};
	Sprite* opeSurprise_[3] = {};
	Sprite* opeSmile_[3] = {};
	Sprite* movieBar_[2] = {};
	DirectX::XMFLOAT2 textWindowSize_;
	DirectX::XMFLOAT2 faceWindowSize_;
	DirectX::XMFLOAT2 operatorSize_;
	DirectX::XMFLOAT2 movieBarPos_[2] = {};

	TextDraw* textDraw_ = nullptr;
	int32_t textSpeed_;
	int32_t textCount_;
	int32_t textAddTimer_;

	int32_t closeWindowTimer_; //ウィンドウ閉鎖時間
	int32_t openWindowTimer_; //ウィンドウ解放時間
	int32_t movieTimer_; //ムービー時間

	Vector3 cameraPos_; //カメラ座標

	bool isMessageWait_; //メッセージデータ読み込み待機フラグ
	bool isTextWindowOpen_; //テキストウィンドウオープンフラグ
	int32_t waitMessageTimer_; //メッセージデータ読み込み待機時間
	bool isTextDraw_; //メッセージデータ出力完了フラグ

	std::stringstream textData_; //メッセージデータ格納用文字列
	std::wstring drawMessage_; //メッセージ内容出力用文字列
	std::wstring message_; //メッセージ内容格納文字列

	int32_t opeAnimeTimer_;
	int32_t opeAnimeCount_;

	//BaseBoss* boss;
	FirstBoss* firstBoss_;

	DirectX::XMFLOAT2 titleBackSize_;
	DirectX::XMFLOAT2 backSize_;
	//スコア
	int32_t score_;

	//ポーズフラグ
	bool isPause_;
	//タイトルバックフラグ
	bool isTitleBack_;
	//死亡フラグ
	bool isDead_;
};